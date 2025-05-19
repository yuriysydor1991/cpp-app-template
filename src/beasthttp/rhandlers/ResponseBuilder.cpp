#include "src/beasthttp/rhandlers/ResponseBuilder.h"

#include <cassert>
#include <memory>

#include "project-global-decls.h"
#include "src/beasthttp/beast-includes.h"

namespace beasthttp::rhandlers
{

bool ResponseBuilder::build_response(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  if (sctx == nullptr) {
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

  sctx->response.keep_alive(get_keep_alive());
}

const char* const& ResponseBuilder::get_return_type()
{
  static constexpr const char* const text_html = "text/html";

  return text_html;
}

bool ResponseBuilder::get_keep_alive() { return false; }

}  // namespace beasthttp::rhandlers
