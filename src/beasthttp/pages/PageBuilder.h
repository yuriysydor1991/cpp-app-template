#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PAGEBUILDER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PAGEBUILDER_CLASS_H

#include <memory>

#include "src/beasthttp/pages/IPageBuilder.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::pages
{

class PageBuilder : public IPageBuilder
{
 public:
  virtual ~PageBuilder() = default;
  PageBuilder() = default;

  virtual bool build_request_page(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx) override;

 protected:
  virtual bool build_page_header(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);
  virtual bool prepend_page_headers(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  virtual bool build_page_body(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);
  virtual bool build_page_footer(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  virtual std::string get_page_lang(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  virtual const std::string& get_page_theme_color(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  virtual std::string build_page_title(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  virtual std::string build_page_keywords(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  virtual std::string build_page_description(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  virtual bool build_default_page(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);
};

}  // namespace beasthttp::pages

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PAGEBUILDER_CLASS_H
