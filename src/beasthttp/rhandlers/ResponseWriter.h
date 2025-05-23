#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEWRITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEWRITER_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::rhandlers
{

/**
 * @brief The ResponseWrite class is responsible for writing
 * the builded and filled response object available in the given
 * single HTTP session object into it's available socket object.
 */
class ResponseWriter
{
 public:
  virtual ~ResponseWriter() = default;
  ResponseWriter() = default;

  /**
   * @brief Writes available build and filled response object into
   * given socket. All objects are used from the given single
   * HTTP session context instance.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information.
   *
   * @return Returns a true boolean value in case of the success and false
   * otherwise.
   */
  virtual bool write_response(std::shared_ptr<HTTPSessionContext> sctx);
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RESPONSEWRITER_CLASS_H
