#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DEFAULTHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DEFAULTHANDLER_CLASS_H

#include <memory>

#include "src/beasthttp/pages/IPageBuilder.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"
#include "src/beasthttp/rhandlers/IRequestHandler.h"
#include "src/beasthttp/rhandlers/RequestReader.h"
#include "src/beasthttp/rhandlers/ResponseBuilder.h"
#include "src/beasthttp/rhandlers/ResponseWriter.h"

namespace beasthttp::rhandlers
{

/**
 * @brief The default HTTP session handler.
 * Shows a single simple web page with small message.
 */
class DefaultHandler : public IRequestHandler
{
 public:
  virtual ~DefaultHandler() = default;
  DefaultHandler() = default;

  /**
   * @brief Routine to handle all the requests from the connected client.
   *
   * @param sctx The filled HTTPSessionContext object to hold all relevant
   * information for the single HTTP session.
   */
  virtual bool handle_session(
      std::shared_ptr<HTTPSessionContext> sctx) override;

 protected:
  /**
   * @brief Creates instance of the appropriate RequestReader class or it's
   * descendant. Override it in the descendant to change class
   * instance behavior.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns appropriate HTTP request reader object.
   */
  virtual std::shared_ptr<rhandlers::RequestReader> create_request_reader(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief Reads the single HTTP request through the socket contained
   * in the given HTTP session context. Fills fields of the
   * rhandlers::HTTPSessionContext class for the available HTTP request.
   * Override it in the descendant to change class instance behavior.
   *
   * @param sctx The single HTTP session context object pointer.
   *
   * @return Returns a true boolean value in case of success and false
   * otherwise.
   */
  virtual bool read_single_request(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  /**
   * @brief Creates the instance of the appropriate response object builder.
   * Override it in the descendant to change class
   * instance behavior.
   *
   * @param sctx The single HTTP session context object pointer.
   *
   * @return Returns the appropriate response builder object in case of success.
   */
  virtual std::shared_ptr<ResponseBuilder> create_response_builder(
      std::shared_ptr<HTTPSessionContext> sctx);

  /**
   * @brief Creates the appropriate response builder and calls it's
   * build_response method. Override it in the descendant to change class
   * instance behavior.
   *
   * @param sctx The single HTTP session context object pointer.
   *
   * @return Returns a true boolean value in case of success and false
   * otherwise.
   */
  virtual bool build_response(std::shared_ptr<HTTPSessionContext> sctx);

  /**
   * @param Creates the appropriate HTTP response writer into the given context'
   * socket. Override it in the descendant to change class
   * instance behavior.
   */
  virtual std::shared_ptr<ResponseWriter> create_response_writer(
      std::shared_ptr<HTTPSessionContext> sctx);

  /**
   * @brief Writes response into given context' socket object. Override it in
   * the descendant to change class instance behavior.
   *
   * @param sctx The single HTTP session context object pointer.
   *
   * @return Returns a true boolean value in case of success and false
   * otherwise.
   */
  virtual bool write_response(std::shared_ptr<HTTPSessionContext> sctx);

  /**
   * @brief Creates the appropriate response builder (the HTML-page builder
   * supposedly) object which will assemble the response for the current HTTP
   * request. Override it in the descendant to change class instance behavior.
   */
  virtual std::shared_ptr<pages::IPageBuilder> create_request_response_builder(
      std::shared_ptr<HTTPSessionContext> sctx);

  /**
   * @brief Creates the appropriate HTTP-response builder and builds
   * the current available HTTP request response with calling to
   * builder's build_request_page method.
   *
   * @param sctx The single HTTP session context object pointer.
   *
   * @return Returns a true boolean value in case of success and false
   * otherwise.
   */
  virtual bool build_request_response(std::shared_ptr<HTTPSessionContext> sctx);
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DEFAULTHANDLER_CLASS_H
