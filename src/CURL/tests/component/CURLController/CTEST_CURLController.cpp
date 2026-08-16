#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <vector>

#include "src/CURL/CURLController.h"

using namespace curli;
using namespace testing;

/**
 * @brief Component test of the CURLController driving the real libcurl.
 *
 * The transfers go over the file protocol against the files the test writes
 * into it's own build directory, so the whole suite stays deterministic and
 * needs no network at all. The HTTP specific paths are checked against a
 * loopback port nothing listens on, where the expectations hold no matter
 * whether the connection gets refused, dropped or answered by a proxy.
 */
class CTEST_CURLController : public Test
{
 public:
  CTEST_CURLController() : controller{CURLController::create()} {}

  /// @brief Composes the file protocol URL of the given path. The leading
  /// slash is the one that the drive letter platforms lack.
  static std::string file_url(const std::string& path)
  {
    if (!path.empty() && path.front() == '/') {
      return "file://" + path;
    }

    return "file:///" + path;
  }

  /// @brief Writes the given contents into the named test data file and gives
  /// it's file protocol URL back.
  static std::string file_url_with(const std::string& name,
                                   const std::string& contents)
  {
    const std::string path = std::string{data_dir} + "/" + name;

    std::ofstream file{path.c_str(), std::ofstream::out |
                                         std::ofstream::binary |
                                         std::ofstream::trunc};

    file << contents;
    file.close();

    return file_url(path);
  }

  /// @brief The URL of a test data file that never gets written.
  static std::string absent_file_url()
  {
    return file_url(std::string{data_dir} + "/an-absent-file.data");
  }

  static std::string as_string(const CURLController::download_buffer& buff)
  {
    return {buff.cbegin(), buff.cend()};
  }

  inline static constexpr const char* const data_dir =
      CTEST_CURLController_DATA_DIR;

  /// @brief A loopback URL of a privileged port that no service listens on,
  /// so the HTTP request fails with no external communication.
  inline static constexpr const char* const deadURL = "http://127.0.0.1:1/";

  CURLControllerPtr controller;
};

TEST_F(CTEST_CURLController, downloads_the_file_contents)
{
  static const std::string contents{"The contents of a downloaded file."};

  EXPECT_EQ(as_string(controller->download(
                file_url_with("downloaded.data", contents))),
            contents);
}

TEST_F(CTEST_CURLController, a_large_file_arrives_completely)
{
  // way above the buffer reserve, so the receive callback has to grow the
  // buffer during the transfer.
  static const std::string contents(1024U * 1024U, 'z');

  EXPECT_EQ(
      as_string(controller->download(file_url_with("large.data", contents))),
      contents);
}

TEST_F(CTEST_CURLController, the_additional_headers_break_no_transfer)
{
  static const std::string contents{"The contents of a file."};

  EXPECT_EQ(as_string(controller->download(
                file_url_with("with-headers.data", contents),
                {"X-Some-Header: a value", "X-Another-Header: another value"})),
            contents);
}

TEST_F(CTEST_CURLController, an_absent_file_gives_no_data)
{
  EXPECT_TRUE(controller->download(absent_file_url()).empty());
}

TEST_F(CTEST_CURLController, a_protocol_with_no_statuses_reports_no_status)
{
  EXPECT_FALSE(
      controller->download(file_url_with("status.data", "The contents."))
          .empty());

  EXPECT_EQ(controller->last_response_code(), 0L);
}

TEST_F(CTEST_CURLController, every_request_drops_the_previous_data)
{
  static const std::string first{"The contents of the first file."};
  static const std::string second{"The second one."};

  ASSERT_EQ(as_string(controller->download(file_url_with("first.data", first))),
            first);

  EXPECT_TRUE(controller->download(absent_file_url()).empty());

  EXPECT_EQ(
      as_string(controller->download(file_url_with("second.data", second))),
      second);
}

TEST_F(CTEST_CURLController, an_existing_file_is_alive)
{
  EXPECT_TRUE(
      controller->is_url_alive(file_url_with("alive.data", "The contents.")));

  // the HEAD request asks for the headers only, so no body arrives.
  EXPECT_TRUE(controller->get().empty());
}

TEST_F(CTEST_CURLController, an_absent_file_is_not_alive)
{
  EXPECT_FALSE(controller->is_url_alive(absent_file_url()));
}

TEST_F(CTEST_CURLController, an_unreachable_url_is_not_alive)
{
  EXPECT_FALSE(controller->is_url_alive(deadURL));
}

TEST_F(CTEST_CURLController, the_request_kind_leaks_into_no_next_request)
{
  static const std::string contents{"The contents of a downloaded file."};

  // whatever the unreachable host answers with is of no interest here, the
  // post is performed for it's options to be left behind only.
  controller->post(deadURL, "a request body", {"Content-Type: text/plain"});

  // the download after the post must carry neither it's method, nor it's body
  // and headers, so the plain file transfer succeeds.
  EXPECT_EQ(as_string(controller->download(
                file_url_with("after-post.data", contents))),
            contents);
}
