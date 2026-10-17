#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COMPONENT_TESTS_DISTINCTMETAPAGEBUILDER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COMPONENT_TESTS_DISTINCTMETAPAGEBUILDER_CLASS_H

#include <memory>
#include <string>

#include "src/beasthttp/pages/PageBuilder.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

/**
 * @brief The page builder whose keywords and description differ, so a test
 * tells the meta tags carrying them apart.
 */
class DistinctMetaPageBuilder : public beasthttp::pages::PageBuilder
{
 public:
  inline static const std::string keywords = "the-page-keywords";
  inline static const std::string description = "the-page-description";

 protected:
  std::string build_page_keywords(
      std::shared_ptr<beasthttp::rhandlers::HTTPSessionContext> /*sctx*/)
      override
  {
    return keywords;
  }

  std::string build_page_description(
      std::shared_ptr<beasthttp::rhandlers::HTTPSessionContext> /*sctx*/)
      override
  {
    return description;
  }
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_COMPONENT_TESTS_DISTINCTMETAPAGEBUILDER_CLASS_H
