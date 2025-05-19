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

  virtual bool handle_session(
      std::shared_ptr<HTTPSessionContext> sctx) override;

 protected:
  virtual std::shared_ptr<rhandlers::RequestReader> create_request_reader(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);

  virtual bool read_single_request(
      std::shared_ptr<rhandlers::HTTPSessionContext> sctx);
  virtual std::shared_ptr<ResponseBuilder> create_response_builder(
      std::shared_ptr<HTTPSessionContext> sctx);
  virtual bool build_response(std::shared_ptr<HTTPSessionContext> sctx);
  virtual std::shared_ptr<ResponseWriter> create_response_writer(
      std::shared_ptr<HTTPSessionContext> sctx);
  virtual bool write_response(std::shared_ptr<HTTPSessionContext> sctx);
  virtual std::shared_ptr<pages::IPageBuilder> create_request_response_builder(
      std::shared_ptr<HTTPSessionContext> sctx);
  virtual bool build_request_response(std::shared_ptr<HTTPSessionContext> sctx);
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DEFAULTHANDLER_CLASS_H
