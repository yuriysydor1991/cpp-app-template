#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <csignal>
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

  actx->http_address = tests_address;
  actx->http_port = used_http_port;

  EXPECT_CALL(*actx, stop()).Times(1).WillOnce(Return(true));

  std::thread httpThread{[this, actx]() { EXPECT_TRUE(http->serve(actx)); }};

  httpThread.join();
}

TEST_F(CTEST_beasthttp, accept_wait_success)
{
  static constexpr const unsigned short used_http_port = 10000U;

  int argc{0};
  char** argv{nullptr};

  auto actx = std::make_shared<ApplicationContext>(argc, argv);

  actx->http_address = tests_address;
  actx->http_port = used_http_port;

  EXPECT_CALL(*actx, stop()).Times(1).WillOnce(Invoke([&]() -> bool {
    EXPECT_CALL(*actx, stop()).Times(1).WillOnce(Return(true));
    signal_ready();
    return false;
  }));
  EXPECT_CALL(*actx, stop(_)).Times(0);

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

  actx->http_address = tests_address;
  actx->http_port = used_http_port;

  EXPECT_CALL(*actx, stop())
      .Times(expected_reps)
      .WillRepeatedly(Invoke([&]() -> bool {
        signal_ready();
        return false;
      }));
  EXPECT_CALL(*actx, stop(_)).Times(0);

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

  EXPECT_CALL(*actx, stop()).Times(1).WillRepeatedly(Return(true));

  auto response = http_request(used_http_port);

  EXPECT_FALSE(response.empty());
  EXPECT_EQ(response, expected_standard_response);

  httpThread.join();
}
