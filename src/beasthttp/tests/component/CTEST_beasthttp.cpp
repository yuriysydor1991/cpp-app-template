#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <memory>
#include <set>
#include <string>
#include <thread>

#include "HTTPHelper.h"
#include "LimitedController.h"
#include "project-global-decls.h"
#include "src/app/ApplicationContext.h"
#include "src/beasthttp/HttpController.h"

using namespace app;
using namespace testing;
using namespace beasthttp;

class CTEST_beasthttp : public Test, virtual public HTTPHelper
{
 public:
  inline static const unsigned int tests_reps = 1000U;

  /// @brief The time the stopped server may take to return. Covers a few
  /// stop flag check periods of the sanitized build.
  inline static const std::chrono::seconds stop_deadline{2};

  ~CTEST_beasthttp() override { stop_server(); }

  /**
   * @brief Starts the given controller in a thread of it's own on a port the
   * OS chooses, so no two tests ever compete for the same one.
   *
   * @return Returns the port the started server listens on.
   */
  unsigned short start_server(std::shared_ptr<HttpController> controller)
  {
    actx->set_http_address(tests_address);
    actx->set_http_port(0U);

    server = std::thread{
        [this, controller]() { served.store(controller->serve(actx)); }};

    const auto deadline =
        std::chrono::steady_clock::now() + std::chrono::seconds(10);

    while (controller->bound_port() == 0U &&
           std::chrono::steady_clock::now() < deadline) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    EXPECT_NE(controller->bound_port(), 0U);

    return controller->bound_port();
  }

  /**
   * @brief Raises the stop flag with no request sent afterwards and waits for
   * the server to return.
   *
   * @return Returns the time the server took to return.
   */
  std::chrono::steady_clock::duration stop_server()
  {
    const auto start = std::chrono::steady_clock::now();

    actx->set_stop(true);

    if (server.joinable()) {
      server.join();
    }

    return std::chrono::steady_clock::now() - start;
  }

  /**
   * @brief Serves the given raw request by a limited controller and gives
   * back whatever the request is answered with.
   */
  std::string serve_once(const std::string& request)
  {
    const auto response = raw_request(
        start_server(std::make_shared<LimitedController>()), request);

    stop_server();

    EXPECT_TRUE(served);

    return response;
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> actx{
      std::make_shared<ApplicationContext>(argc, argv)};
  std::shared_ptr<HttpController> http{HttpController::create()};

  std::thread server;
  std::atomic_bool served{false};
};

TEST_F(CTEST_beasthttp, invalid_context_pointer_failure)
{
  EXPECT_FALSE(http->serve({}));
}

TEST_F(CTEST_beasthttp, bootstrap_success)
{
  actx->set_http_address(tests_address);
  actx->set_stop(true);

  EXPECT_TRUE(http->serve(actx));
}

TEST_F(CTEST_beasthttp, a_raised_stop_flag_ends_the_waiting_server)
{
  start_server(http);

  EXPECT_LT(stop_server(), stop_deadline);
  EXPECT_TRUE(served);
}

TEST_F(CTEST_beasthttp, accept_wait_success)
{
  const auto port = start_server(http);

  auto response = http_request(port);

  EXPECT_FALSE(response.empty());
  EXPECT_EQ(response, expected_standard_response);

  EXPECT_LT(stop_server(), stop_deadline);
  EXPECT_TRUE(served);
}

TEST_F(CTEST_beasthttp, multithread_accept_wait_success)
{
  // The clients stay within the half of the connections the server serves at
  // once, since a finished session is released a bit after it's client has
  // got the answer already and may connect again.
  static const unsigned int expected_threads =
      std::max(1U, std::min(std::thread::hardware_concurrency() * 2U,
                            project_decls::PROJECT_HTTP_MAX_CONNECTIONS / 2U));

  const auto port = start_server(http);

  std::set<std::shared_ptr<std::thread>> requestersThs;

  for (auto iter = 0U; iter < expected_threads; ++iter) {
    auto th = std::make_shared<std::thread>([port]() {
      auto response =
          http_request_repeat(port, tests_reps, expected_standard_response);
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

  EXPECT_LT(stop_server(), stop_deadline);
  EXPECT_TRUE(served);
}

TEST_F(CTEST_beasthttp, an_oversized_request_body_is_refused)
{
  static const std::string body(LimitedController::body_limit * 2U, 'a');
  static const std::string request =
      "POST / HTTP/1.1\r\nHost: " + tests_address +
      "\r\nContent-Length: " + std::to_string(body.size()) + "\r\n\r\n" + body;

  EXPECT_TRUE(serve_once(request).empty());
}

TEST_F(CTEST_beasthttp, oversized_request_headers_are_refused)
{
  static const std::string request =
      "GET / HTTP/1.1\r\nHost: " + tests_address +
      "\r\nX-Big: " + std::string(LimitedController::header_limit * 2U, 'b') +
      "\r\n\r\n";

  EXPECT_TRUE(serve_once(request).empty());
}

TEST_F(CTEST_beasthttp, an_unfinished_request_times_out)
{
  // The terminating empty line is missing on purpose, so the server waits for
  // the rest of the request that never arrives.
  static const std::string request =
      "GET / HTTP/1.1\r\nHost: " + tests_address + "\r\n";

  EXPECT_TRUE(serve_once(request).empty());
}

TEST_F(CTEST_beasthttp, a_request_within_the_limits_is_answered)
{
  static const std::string request =
      "GET / HTTP/1.1\r\nHost: " + tests_address + "\r\n\r\n";

  const auto response = serve_once(request);

  EXPECT_THAT(response, HasSubstr("200 OK"));
  EXPECT_THAT(response, HasSubstr(expected_standard_response));
}

TEST_F(CTEST_beasthttp, a_query_string_keeps_the_root_page)
{
  static const std::string request =
      "GET /?lang=en HTTP/1.1\r\nHost: " + tests_address + "\r\n\r\n";

  const auto response = serve_once(request);

  EXPECT_THAT(response, HasSubstr("200 OK"));
  EXPECT_THAT(response, HasSubstr(expected_standard_response));
}

TEST_F(CTEST_beasthttp, a_head_request_gets_the_headers_alone)
{
  static const std::string request =
      "HEAD / HTTP/1.1\r\nHost: " + tests_address + "\r\n\r\n";

  const auto response = serve_once(request);

  EXPECT_THAT(response, HasSubstr("200 OK"));
  EXPECT_THAT(response,
              HasSubstr("Content-Length: " +
                        std::to_string(expected_standard_response.size())));
  EXPECT_THAT(response, Not(HasSubstr("<!DOCTYPE html>")));
}

TEST_F(CTEST_beasthttp, an_unsupported_method_is_not_allowed)
{
  static const std::string request =
      "DELETE / HTTP/1.1\r\nHost: " + tests_address + "\r\n\r\n";

  const auto response = serve_once(request);

  EXPECT_THAT(response, HasSubstr("405 Method Not Allowed"));
  EXPECT_THAT(response, HasSubstr("Allow: GET, HEAD"));
  EXPECT_THAT(response, Not(HasSubstr("<!DOCTYPE html>")));
}

TEST_F(CTEST_beasthttp, an_unknown_path_is_not_found)
{
  static const std::string request =
      "GET /missing HTTP/1.1\r\nHost: " + tests_address + "\r\n\r\n";

  const auto response = serve_once(request);

  EXPECT_THAT(response, HasSubstr("404 Not Found"));
  EXPECT_THAT(response, Not(HasSubstr("<!DOCTYPE html>")));
}
