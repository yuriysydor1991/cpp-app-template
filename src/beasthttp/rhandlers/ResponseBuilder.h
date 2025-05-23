#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEBUILDER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEBUILDER_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::rhandlers
{

/**
 * @brief The Boost.Beast response object builder class.
 * Creates the appropriate response object into given single HTTP session
 * context and fills it with some HTTP header fields values.
 */
class ResponseBuilder
{
 public:
  virtual ~ResponseBuilder() = default;
  ResponseBuilder() = default;

  /**
   * @brief Creates and assembles the boost response object. Stores it
   * in the provided single HTTP session context instance. Override it in the
   * descendant to change class instance behavior.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of success and false
   * otherwise.
   */
  virtual bool build_response(std::shared_ptr<HTTPSessionContext> sctx);

 protected:
  /**
   * @brief Sets the default values to the response object available in
   * the provided single HTTP session context. Override it in the descendant to
   * change class instance behavior.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   */
  virtual void set_defaults(std::shared_ptr<HTTPSessionContext> sctx);

  /**
   * @brief Method should return current class HTTP return type
   * stored in the response object. Override it in the descendant to change
   * class instance behavior.
   *
   * @return Returns the HTTP response return MIME-type
   */
  virtual const char* const& get_return_type();

  /**
   * @brief Returns the keep alive HTTP connection field value. Override it in
   * the descendant to change class instance behavior.
   *
   * @return Returns a true value that indicates if HTTP connection should be
   * kept alive or false of connection will be closed after the response is
   * given.
   */
  virtual bool get_keep_alive();
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEBUILDER_CLASS_H
