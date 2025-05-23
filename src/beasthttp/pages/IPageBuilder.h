#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IPAGEBUILDER_ABSTRACT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IPAGEBUILDER_ABSTRACT_CLASS_H

#include <memory>

#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

/**
 * @brief The namespace for all the pages builders infrastructure.
 */
namespace beasthttp::pages
{

/**
 * @brief The response builder abstract class to determine
 * the interface for each response builder descendant.
 */
class IPageBuilder
{
 public:
  virtual ~IPageBuilder() = default;
  IPageBuilder() = default;

  /**
   * @brief The descendant implementation should check for
   * the requested URI provided in the HTTP request object
   * and build appropriate HTML response for the given
   * single HTTP session context instance.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual bool build_request_page(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx) = 0;
};

}  // namespace beasthttp::pages

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IPAGEBUILDER_ABSTRACT_CLASS_H
