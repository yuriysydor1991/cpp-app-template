#include "src/beasthttp/rhandlers/DefaultHandler.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/beasthttp/beast-includes.h"
#include "src/beasthttp/pages/PageBuilder.h"
#include "src/beasthttp/rhandlers/HTTPSessionContext.h"
#include "src/beasthttp/rhandlers/IRequestHandler.h"
#include "src/log/log.h"

namespace beasthttp::rhandlers
{

bool DefaultHandler::handle_session(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);
  assert(sctx->socket != nullptr);

  if (sctx == nullptr) {
    LOGE("Invalid context pointer provided");
    return false;
  }

  try {
    if (!read_single_request(sctx)) {
      LOGE("Fail to read request");
      return false;
    }

    if (!build_response(sctx)) {
      LOGE("Fail to build response object");
      return false;
    }

    if (!build_request_response(sctx)) {
      LOGE("Fail to build request's response");
      return false;
    }

    if (!write_response(sctx)) {
      LOGD("Fail to write response");
      return false;
    }
  }
  catch (const std::exception& e) {
    LOGE("Session error: " << e.what());
    return false;
  }

  return true;
}

std::shared_ptr<pages::IPageBuilder>
DefaultHandler::create_request_response_builder(
    std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  if (sctx == nullptr) {
    LOGE("Invalid context pointer provided");
    return {};
  }

  return std::make_shared<pages::PageBuilder>();
}

bool DefaultHandler::build_request_response(
    std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  if (sctx == nullptr) {
    LOGE("Invalid context pointer provided");
    return false;
  }

  auto responseBuilder = create_request_response_builder(sctx);

  return responseBuilder->build_request_page(sctx);
}

std::shared_ptr<rhandlers::RequestReader> DefaultHandler::create_request_reader(
    [[maybe_unused]] std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  return std::make_shared<rhandlers::RequestReader>();
}

bool DefaultHandler::read_single_request(
    std::shared_ptr<rhandlers::HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  auto rreader = create_request_reader(sctx);

  return rreader->read_request(sctx);
}

std::shared_ptr<ResponseBuilder> DefaultHandler::create_response_builder(
    [[maybe_unused]] std::shared_ptr<HTTPSessionContext> sctx)
{
  return std::make_shared<ResponseBuilder>();
}

std::shared_ptr<ResponseWriter> DefaultHandler::create_response_writer(
    std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  return std::make_shared<ResponseWriter>();
}

bool DefaultHandler::build_response(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  auto rbuilder = create_response_builder(sctx);

  assert(rbuilder != nullptr);

  return rbuilder->build_response(sctx);
}

bool DefaultHandler::write_response(std::shared_ptr<HTTPSessionContext> sctx)
{
  assert(sctx != nullptr);

  auto writer = create_response_writer(sctx);

  return writer->write_response(sctx);
}

}  // namespace beasthttp::rhandlers
