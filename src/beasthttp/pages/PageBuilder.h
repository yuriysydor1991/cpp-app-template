#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PAGEBUILDER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PAGEBUILDER_CLASS_H

#include <memory>

#include "src/beasthttp/pages/IPageBuilder.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::pages
{

/**
 * @brief The default HTTP response builder class.
 * Assembles the simple demo HTML-page. Change it's implementation
 * or subclass and override it's method in order to
 * implement particular Web-site.
 */
class PageBuilder : public IPageBuilder
{
 public:
  virtual ~PageBuilder() = default;
  PageBuilder() = default;

  /**
   * @brief The default HTTP response HTML page builder.
   * By default assembles the simple demo HTML-page.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual bool build_request_page(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx) override;

 protected:
  /**
   * @brief Method would build the response HTML-page header
   * and puts it into the available HTTP response object provided
   * in the rhandlers::HTTPSessionContext instance.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual bool build_page_header(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief This method is intended to introduce some additional
   * HTML-page headers like script or link etc. to be introduced
   * after the main headers were introduced into the available
   * HTTP response object inside rhandlers::HTTPSessionContext instance.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual bool prepend_page_headers(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief The web page build method. Should build the entire
   * HTML page which will be contained between the <body></body> tags.
   * By default assembles a simple HTML demo page with basic greetings.
   * Should be re-implemented or overriden in subclasses in order to
   * implement some usefull web-page.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual bool build_page_body(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief Assembles the page footer tags into available response
   * object so it is finalized.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual bool build_page_footer(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief Should return the language string of the page which
   * will be included into the <html> starter tag. By the default
   * returns an "en" string.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual std::string get_page_lang(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief Should return the page theme color which will
   * be inserted into the page header tags.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual const std::string& get_page_theme_color(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief Should assemble and return the current HTML page title
   * tag value.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual std::string build_page_title(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief Should return the keywords string which will be inserted
   * into the HTML-page header tags like <meta>.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual std::string build_page_keywords(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief Should return the description string which will be inserted
   * into the HTML-page header tags like <meta>.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual std::string build_page_description(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief Assembles the default HTML page using methods like
   * build_page_description, build_page_keywords, build_page_title,
   * get_page_theme_color, get_page_lang, build_page_footer, build_page_body,
   * prepend_page_headers and build_page_header. Override any of the specified
   * methods or edit their implementation in order to implement the real and
   * usefull HTML page.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual bool build_default_page(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);
};

}  // namespace beasthttp::pages

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PAGEBUILDER_CLASS_H
