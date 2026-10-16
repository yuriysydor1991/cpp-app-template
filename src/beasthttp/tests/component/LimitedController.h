#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COMPONENT_TESTS_LIMITEDCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COMPONENT_TESTS_LIMITEDCONTROLLER_CLASS_H

#include <chrono>
#include <cstdint>
#include <memory>

#include "src/beasthttp/HttpController.h"

/**
 * @brief The controller handing every session the hardening constraints the
 * test needs, so no oversized request and no timeout of a real deployment
 * size has to be produced to check them.
 */
class LimitedController : public beasthttp::HttpController
{
 public:
  inline static constexpr const std::uint64_t body_limit = 1024U;
  inline static constexpr const std::uint32_t header_limit = 256U;
  inline static const std::chrono::seconds request_timeout{1};

 protected:
  virtual std::shared_ptr<beasthttp::rhandlers::HTTPSessionContext>
  create_http_session_context() override
  {
    auto sctx = HttpController::create_http_session_context();

    sctx->maxBodyBytes = body_limit;
    sctx->maxHeaderBytes = header_limit;
    sctx->requestTimeout = request_timeout;

    return sctx;
  }
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_COMPONENT_TESTS_LIMITEDCONTROLLER_CLASS_H
