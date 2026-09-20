#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_REQUESTREADER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_REQUESTREADER_CLASS_H

#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

namespace beasthttp::rhandlers
{

/**
 * @brief The request reader class for provided stream object in the
 * single HTTP session instance.
 */
class RequestReader
{
 public:
  virtual ~RequestReader() = default;
  RequestReader() = default;

  /**
   * @brief The stream's request reader routine. Reads single HTTP request
   * from the provided stream, refusing the one whose headers or body exceed
   * the size the given context allows.
   *
   * @param sctx The single HTTP session context object to hold available
   * relevant information. The receiver of read data.
   *
   * @return Returns a true boolean value in case of success and false
   * otherwise.
   */
  virtual bool read_request(std::shared_ptr<HTTPSessionContext> sctx);

 protected:
  /**
   * @brief Reads the request into the given parser, giving the read no more
   * time than the given context allows. Override it in the descendant to
   * change class instance behavior.
   *
   * @param sctx The single HTTP session context object pointer.
   * @param parser The parser holding the size constraints of the request.
   *
   * @return Returns a true boolean value in case of success and false
   * otherwise.
   */
  virtual bool read_into(std::shared_ptr<HTTPSessionContext> sctx,
                         http::request_parser<http::string_body>& parser);
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_REQUESTREADER_CLASS_H
