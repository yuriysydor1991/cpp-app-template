#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <csignal>
#include <cstdint>
#include <memory>
#include <set>
#include <string>
#include <thread>

#include "HTTPHelper.h"
#include "src/app/ApplicationContext.h"
#include "src/beasthttp/HttpController.h"

using namespace app;
using namespace testing;
using namespace beasthttp;

/**
 * @brief The controller handing every session the hardening constraints the
 * test needs, so no oversized request and no timeout of a real deployment
 * size has to be produced to check them.
 */
class LimitedController : public HttpController
{
 public:
  inline static constexpr const std::uint64_t body_limit = 1024U;
  inline static constexpr const std::uint32_t header_limit = 256U;
  inline static const std::chrono::seconds request_timeout{1};

 protected:
  virtual std::shared_ptr<rhandlers::HTTPSessionContext>
  create_http_session_context() override
  {
    auto sctx = HttpController::create_http_session_context();

    sctx->maxBodyBytes = body_limit;
    sctx->maxHeaderBytes = header_limit;
    sctx->requestTimeout = request_timeout;

    return sctx;
  }
};

class CTEST_beasthttp : public Test, virtual public HTTPHelper
{
 public:
  inline static const unsigned int tests_reps = 1000U;

  virtual ~CTEST_beasthttp() {}

  CTEST_beasthttp() : http{HttpController::create()}
  {
    EXPECT_NE(http, nullptr);
  }

  void signal_ready()
  {
    {
      std::lock_guard<std::mutex> lock(mtx);
      server_ready.store(true);
    }
    cv.notify_all();
  }

  void wait_server()
  {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&] { return server_ready.load(); });
    std::this_thread::yield();
  }

  /**
   * @brief Serves a single session by the given limited controller and gives
   * back whatever the given raw request is answered with.
   */
  std::string serve_once(std::shared_ptr<LimitedController> limited,
                         const unsigned short port, const std::string& request)
  {
    int argc{0};
    char** argv{nullptr};

    auto actx = std::make_shared<ApplicationContext>(argc, argv);

    actx->set_http_address(tests_address);
    actx->set_http_port(port);

    EXPECT_CALL(*actx, get_stop()).Times(1).WillOnce(Invoke([&]() -> bool {
      EXPECT_CALL(*actx, get_stop()).Times(1).WillOnce(Return(true));
      signal_ready();
      return false;
    }));

    std::thread httpThread{
        [&limited, &actx]() { EXPECT_TRUE(limited->serve(actx)); }};

    wait_server();

    auto response = raw_request(port, request);

    httpThread.join();

    return response;
  }

  std::shared_ptr<HttpController> http;

  std::mutex mtx;
  std::condition_variable cv;
  std::atomic_bool server_ready = false;
};

TEST_F(CTEST_beasthttp, invalid_context_pointer_failure)
{
  EXPECT_FALSE(http->serve({}));
}

TEST_F(CTEST_beasthttp, bootstrap_success)
{
  static constexpr const unsigned short used_http_port = 9999U;

  int argc{0};
  char** argv{nullptr};

  auto actx = std::make_shared<ApplicationContext>(argc, argv);

  actx->set_http_address(tests_address);
  actx->set_http_port(used_http_port);

  EXPECT_CALL(*actx, get_stop()).Times(1).WillOnce(Return(true));

  std::thread httpThread{[this, actx]() { EXPECT_TRUE(http->serve(actx)); }};

  httpThread.join();
}

TEST_F(CTEST_beasthttp, accept_wait_success)
{
  static constexpr const unsigned short used_http_port = 10000U;

  int argc{0};
  char** argv{nullptr};

  auto actx = std::make_shared<ApplicationContext>(argc, argv);

  actx->set_http_address(tests_address);
  actx->set_http_port(used_http_port);

  EXPECT_CALL(*actx, get_stop()).Times(1).WillOnce(Invoke([&]() -> bool {
    EXPECT_CALL(*actx, get_stop()).Times(1).WillOnce(Return(true));
    signal_ready();
    return false;
  }));
  EXPECT_CALL(*actx, set_stop(_)).Times(0);

  std::thread httpThread{[this, actx]() { EXPECT_TRUE(http->serve(actx)); }};

  wait_server();

  auto response = http_request(used_http_port);

  EXPECT_FALSE(response.empty());
  EXPECT_EQ(response, expected_standard_response);

  httpThread.join();
}

TEST_F(CTEST_beasthttp, multithread_accept_wait_success)
{
  static constexpr const unsigned short used_http_port = 10001U;
  static const unsigned int expected_threads =
      std::thread::hardware_concurrency() * 2U;
  static const int expected_reps =
      static_cast<int>(expected_threads) * static_cast<int>(tests_reps) + 1;

  int argc{0};
  char** argv{nullptr};

  auto actx = std::make_shared<ApplicationContext>(argc, argv);

  actx->set_http_address(tests_address);
  actx->set_http_port(used_http_port);

  {
    // The stop answer waits for every requester call, however late it comes.
    InSequence stopSequence;

    EXPECT_CALL(*actx, get_stop())
        .Times(expected_reps)
        .WillRepeatedly(Invoke([&]() -> bool {
          signal_ready();
          return false;
        }));
    EXPECT_CALL(*actx, get_stop()).WillOnce(Return(true));
  }
  EXPECT_CALL(*actx, set_stop(_)).Times(0);

  std::thread httpThread{[this, actx]() { EXPECT_TRUE(http->serve(actx)); }};

  wait_server();

  std::set<std::shared_ptr<std::thread>> requestersThs;

  for (auto iter = 0U; iter < expected_threads; ++iter) {
    auto th = std::make_shared<std::thread>([&]() {
      auto response = http_request_repeat(used_http_port, tests_reps,
                                          expected_standard_response);
      EXPECT_FALSE(response.empty());
      EXPECT_EQ(response, expected_standard_response);
    });
    requestersThs.insert(th);
  }

  for (auto& th : requestersThs) {
    if (th->joinable()) {
      th->join();
    }
  }

  requestersThs.clear();

  auto response = http_request(used_http_port);

  EXPECT_FALSE(response.empty());
  EXPECT_EQ(response, expected_standard_response);

  httpThread.join();
}

TEST_F(CTEST_beasthttp, an_oversized_request_body_is_refused)
{
  static constexpr const unsigned short used_http_port = 10002U;
  static const std::string body(LimitedController::body_limit * 2U, 'a');
  static const std::string request =
      "POST / HTTP/1.1\r\nHost: " + tests_address +
      "\r\nContent-Length: " + std::to_string(body.size()) + "\r\n\r\n" + body;

  EXPECT_TRUE(
      serve_once(std::make_shared<LimitedController>(), used_http_port, request)
          .empty());
}

TEST_F(CTEST_beasthttp, oversized_request_headers_are_refused)
{
  static constexpr const unsigned short used_http_port = 10003U;
  static const std::string request =
      "GET / HTTP/1.1\r\nHost: " + tests_address +
      "\r\nX-Big: " + std::string(LimitedController::header_limit * 2U, 'b') +
      "\r\n\r\n";

  EXPECT_TRUE(
      serve_once(std::make_shared<LimitedController>(), used_http_port, request)
          .empty());
}

TEST_F(CTEST_beasthttp, an_unfinished_request_times_out)
{
  static constexpr const unsigned short used_http_port = 10004U;
  // The terminating empty line is missing on purpose, so the server waits for
  // the rest of the request that never arrives.
  static const std::string request =
      "GET / HTTP/1.1\r\nHost: " + tests_address + "\r\n";

  EXPECT_TRUE(
      serve_once(std::make_shared<LimitedController>(), used_http_port, request)
          .empty());
}

TEST_F(CTEST_beasthttp, a_request_within_the_limits_is_answered)
{
  static constexpr const unsigned short used_http_port = 10005U;
  static const std::string request =
      "GET / HTTP/1.1\r\nHost: " + tests_address + "\r\n\r\n";

  const auto response = serve_once(std::make_shared<LimitedController>(),
                                   used_http_port, request);

  EXPECT_THAT(response, HasSubstr("200 OK"));
  EXPECT_THAT(response, HasSubstr(expected_standard_response));
}
