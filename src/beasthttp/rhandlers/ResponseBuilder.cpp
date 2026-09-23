#include "src/beasthttp/rhandlers/ResponseBuilder.h"

#include <cassert>
#include <memory>

#include "project-global-decls.h"
#include "src/beasthttp/beast-includes.h"
#include "src/log/log.h"

namespace beasthttp::rhandlers
{

bool ResponseBuilder::build_response(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  if (sctx == nullptr) {
    LOGE("Invalid context pointer provided");
    return false;
  }

  sctx->response = http::response<http::string_body>{http::status::ok,
                                                     sctx->request.version()};

  set_defaults(sctx);

  return true;
}

void ResponseBuilder::set_defaults(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  sctx->response.set(http::field::server, project_decls::PROJECT_NAME);
  sctx->response.set(http::field::content_type, get_return_type());

  set_security_headers(sctx);

  sctx->response.keep_alive(get_keep_alive());
}

void ResponseBuilder::set_security_headers(
    std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  // Boost.Beast before 1.90 has no enumerator for the fields named by string.
  sctx->response.set("X-Content-Type-Options", "nosniff");
  sctx->response.set(http::field::x_frame_options, "DENY");
  sctx->response.set("Referrer-Policy", "no-referrer");
  sctx->response.set("Content-Security-Policy", get_content_security_policy());
}

const char* const& ResponseBuilder::get_content_security_policy()
{
  // The default page carries it's whole content inline and loads nothing at
  // all, so everything but the page itself is denied.
  static constexpr const char* const policy =
      "default-src 'none'; frame-ancestors 'none'; base-uri 'none'; "
      "form-action 'none'";

  return policy;
}

const char* const& ResponseBuilder::get_return_type()
{
  static constexpr const char* const text_html = "text/html";

  return text_html;
}

bool ResponseBuilder::get_keep_alive() { return false; }

}  // namespace beasthttp::rhandlers
