#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <future>
#include <memory>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include "TestHttpClient.h"
#include "src/app/ApplicationContext.h"
#include "src/app/applications/IApplication.h"
#include "src/wt4/Wt4Server.h"

using namespace wt4server;
using namespace testing;
using namespace std::chrono_literals;

class CTEST_Wt4Server : public Test
{
 public:
  /// @brief Builds the command line the context hands over to the server.
  void command_line(std::vector<std::string> nargs)
  {
    args = std::move(nargs);
    argv.clear();

    for (auto& arg : args) {
      argv.push_back(arg.data());
    }

    argc = static_cast<int>(argv.size());
    argvp = argv.data();
  }

  /// @brief Waits for the server to answer the root path request.
  std::string wait_for_root() const
  {
    std::string response;

    for (auto waited = 0ms; response.empty() && waited < 10s; waited += 50ms) {
      std::this_thread::sleep_for(50ms);
      response = TestHttpClient::get(port, "/");
    }

    return response;
  }

  /// @brief Requests the plain HTML page of the session the bootstrap page
  /// of the Wt started.
  std::string get_plain_page(const std::string& bootstrap) const
  {
    static const std::regex sessionLink{"\\?wtd=([A-Za-z0-9]+)&amp;js=no"};

    std::smatch match;

    if (!std::regex_search(bootstrap, match, sessionLink)) {
      return {};
    }

    return TestHttpClient::get(port, "/?wtd=" + match[1].str() + "&js=no");
  }

  const int port{TestHttpClient::free_port()};
  const std::string listen{"127.0.0.1:" + std::to_string(port)};

  std::vector<std::string> args;
  std::vector<char*> argv;
  int argc{0};
  char** argvp{nullptr};

  std::shared_ptr<app::ApplicationContext> appCtx{
      std::make_shared<app::ApplicationContext>(argc, argvp)};
};

TEST_F(CTEST_Wt4Server, serves_and_stops_on_the_stop_flag)
{
  // the application own -l parameter must not reach the Wt server
  command_line({"CTEST_Wt4Server", "-l", "CTEST_Wt4Server.log", "--docroot",
                ".", "--http-listen", listen});

  auto status = std::async(std::launch::async,
                           [this]() { return Wt4Server::run(appCtx); });

  const std::string bootstrap = wait_for_root();

  EXPECT_THAT(bootstrap, StartsWith("HTTP/1.0 200 OK"));

  // the widgets factory fills the session root with the guest::Root widget
  EXPECT_THAT(get_plain_page(bootstrap), HasSubstr("Hello from guest::Root!"));

  appCtx->set_stop(true);

  ASSERT_EQ(status.wait_for(2s), std::future_status::ready);
  EXPECT_EQ(status.get(), 0);
}

TEST_F(CTEST_Wt4Server, invalid_wt_configuration)
{
  // no --docroot given
  command_line({"CTEST_Wt4Server", "--http-listen", listen});

  auto status = std::async(std::launch::async,
                           [this]() { return Wt4Server::run(appCtx); });

  ASSERT_EQ(status.wait_for(5s), std::future_status::ready);
  EXPECT_EQ(status.get(), app::IApplication::INVALID);
}

TEST_F(CTEST_Wt4Server, no_command_line)
{
  EXPECT_EQ(Wt4Server::run(appCtx), app::IApplication::INVALID);
}
