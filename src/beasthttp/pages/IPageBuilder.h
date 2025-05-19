#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IPAGEBUILDER_ABSTRACT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IPAGEBUILDER_ABSTRACT_CLASS_H

#include <memory>

#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

/**
 * @brief The namespace for all the pages builders infrastructure.
 */
namespace beasthttp::pages
{

class IPageBuilder
{
 public:
  virtual ~IPageBuilder() = default;
  IPageBuilder() = default;

  virtual bool build_request_page(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx) = 0;
};

}  // namespace beasthttp::pages

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IPAGEBUILDER_ABSTRACT_CLASS_H
