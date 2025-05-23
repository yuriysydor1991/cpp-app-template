#include "src/beasthttp/pages/PageBuilder.h"

#include <cassert>
#include <memory>

#include "project-global-decls.h"
#include "src/beasthttp/pages/IPageBuilder.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::pages
{

bool PageBuilder::build_request_page(
    std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  if (sctx == nullptr) {
    return false;
  }

  return build_default_page(sctx);
}

bool PageBuilder::build_default_page(
    std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  return build_page_header(sctx) && build_page_body(sctx) &&
         build_page_footer(sctx);
  ;
}

bool PageBuilder::build_page_header(
    std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  sctx->response.body() += "<!DOCTYPE html>";
  sctx->response.body() += "<html lang=\"" + get_page_lang(sctx) + "\">";

  sctx->response.body() += "<head>";

  sctx->response.body() +=
      "<meta name=\"viewport\" content=\"width=device-width, "
      "initial-scale=1.0\" />";
  sctx->response.body() +=
      "<meta name=\"robots\" content=\"noindex, nofollow\" />";
  sctx->response.body() += "<meta name=\"theme-color\" content=\"" +
                           get_page_theme_color(sctx) + "\" />";

  sctx->response.body() += "<title>";
  sctx->response.body() += build_page_title(sctx);
  sctx->response.body() += "</title>";

  sctx->response.body() += "<meta name=\"description\" content=\"" +
                           build_page_keywords(sctx) + "\" />";
  sctx->response.body() += "<meta name=\"keywords\" content=\"" +
                           build_page_description(sctx) + "\" />";

  if (!prepend_page_headers(sctx)) {
    return false;
  }

  sctx->response.body() += "</head>";

  sctx->response.body() += "<body>";

  return true;
}

bool PageBuilder::prepend_page_headers(
    [[maybe_unused]] std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  return true;
}

bool PageBuilder::build_page_footer(
    std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  sctx->response.body() += "</body>";
  sctx->response.body() += "</html>";

  return true;
}

std::string PageBuilder::get_page_lang(
    [[maybe_unused]] std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  static const std::string lang_en = "en";

  assert(sctx != nullptr);

  return lang_en;
}

const std::string& PageBuilder::get_page_theme_color(
    [[maybe_unused]] std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  static const std::string page_theme_color = "#000";

  assert(sctx != nullptr);

  return page_theme_color;
}

std::string PageBuilder::build_page_title(
    [[maybe_unused]] std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  return project_decls::PROJECT_NAME;
}

std::string PageBuilder::build_page_keywords(
    [[maybe_unused]] std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  return project_decls::PROJECT_NAME;
}

std::string PageBuilder::build_page_description(
    [[maybe_unused]] std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  return project_decls::PROJECT_NAME;
}

bool PageBuilder::build_page_body(
    std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  sctx->response.body() +=
      "<h1>Hello from C++ template project Boost.Beast!</h1>";

  return true;
}

}  // namespace beasthttp::pages
