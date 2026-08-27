#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "src/CURL/CURLController.h"

using namespace curli;
using namespace testing;

/**
 * @brief Unit test of the CURLController.
 *
 * It covers the calls that give up before any transfer starts, so the test
 * itself performs no communication at all. The real transfers are exercised
 * by the CTEST_CURLController component test.
 */
class UTEST_CURLController : public Test
{
 public:
  UTEST_CURLController() : controller{CURLController::create()} {}

  static std::string as_string(const CURLController::download_buffer& buff)
  {
    return {buff.cbegin(), buff.cend()};
  }

  /// @brief A well formed URL of a protocol the libcurl supports in no build,
  /// so the request fails with no name resolution and no connection.
  static constexpr const char* const unsupportedURL =
      "nosuchprotocol://host/path";

  CURLControllerPtr controller;
};

TEST_F(UTEST_CURLController, create_gives_an_instance)
{
  EXPECT_NE(CURLController::create(), nullptr);
}

TEST_F(UTEST_CURLController, no_request_gives_no_data_and_no_status)
{
  EXPECT_TRUE(controller->get().empty());
  EXPECT_EQ(controller->last_response_code(), 0L);
  EXPECT_FALSE(controller->last_response_successfull());
}

TEST_F(UTEST_CURLController, empty_url_downloads_nothing)
{
  EXPECT_TRUE(controller->download({}).empty());
  EXPECT_TRUE(controller->download({}, {"X-Some-Header: a value"}).empty());
  EXPECT_EQ(controller->last_response_code(), 0L);
  EXPECT_FALSE(controller->last_response_successfull());
}

TEST_F(UTEST_CURLController, empty_url_posts_nothing)
{
  EXPECT_TRUE(controller->post({}, "a request body", {}).empty());
  EXPECT_EQ(controller->last_response_code(), 0L);
  EXPECT_FALSE(controller->last_response_successfull());
}

TEST_F(UTEST_CURLController, empty_url_is_not_alive)
{
  EXPECT_FALSE(controller->is_url_alive({}));
}

TEST_F(UTEST_CURLController, unsupported_protocol_downloads_nothing)
{
  EXPECT_TRUE(controller->download(unsupportedURL).empty());
  EXPECT_EQ(controller->last_response_code(), 0L);
  EXPECT_FALSE(controller->last_response_successfull());
}

TEST_F(UTEST_CURLController, unsupported_protocol_posts_nothing)
{
  EXPECT_TRUE(
      controller->post(unsupportedURL, "a request body", {"X-Some: value"})
          .empty());
  EXPECT_EQ(controller->last_response_code(), 0L);
  EXPECT_FALSE(controller->last_response_successfull());
}

TEST_F(UTEST_CURLController, unsupported_protocol_is_not_alive)
{
  EXPECT_FALSE(controller->is_url_alive(unsupportedURL));
}

TEST_F(UTEST_CURLController, the_get_call_gives_the_response_buffer)
{
  EXPECT_EQ(&controller->get(), &controller->download(unsupportedURL));
}

TEST_F(UTEST_CURLController, a_failed_request_drops_the_previous_data)
{
  static const std::string previous{"the data of a previous request"};

  auto& buff = controller->get();

  buff.assign(previous.cbegin(), previous.cend());

  ASSERT_EQ(as_string(controller->get()), previous);

  EXPECT_TRUE(controller->download(unsupportedURL).empty());
  EXPECT_TRUE(controller->get().empty());
}
