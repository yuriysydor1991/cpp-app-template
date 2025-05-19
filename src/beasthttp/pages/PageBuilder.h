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
};

}  // namespace beasthttp::pages

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PAGEBUILDER_CLASS_H
