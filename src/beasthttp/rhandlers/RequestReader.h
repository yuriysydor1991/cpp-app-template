#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_REQUESTREADER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_REQUESTREADER_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::rhandlers
{

/**
 * @brief The request reader class for provided socket object in the
 * single HTTP session instance.
 */
class RequestReader
{
 public:
  virtual ~RequestReader() = default;
  RequestReader() = default;

  /**
   * @brief The socket's request reader routine. Reads single HTTP request
   * from the provided socket.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information. The receiver of read data.
   *
   * @return Returns a true boolean value in case of success and false
   * otherwise.
   */
  virtual bool read_request(std::shared_ptr<HTTPSessionContext> sctx);
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_REQUESTREADER_CLASS_H
