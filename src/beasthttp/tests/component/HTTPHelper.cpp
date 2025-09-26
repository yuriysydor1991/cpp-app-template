#include "HTTPHelper.h"

#include <gtest/gtest.h>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <string>

const std::string HTTPHelper::expected_standard_response =
    "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" "
    "content=\"width=device-width, initial-scale=1.0\" /><meta name=\"robots\" "
    "content=\"noindex, nofollow\" /><meta name=\"theme-color\" "
    "content=\"#000\" /><title>CppAppTemplate</title><meta "
    "name=\"description\" content=\"CppAppTemplate\" /><meta name=\"keywords\" "
    "content=\"CppAppTemplate\" /></head><body><h1>Hello from C++ template "
    "project Boost.Beast!</h1></body></html>";

std::string HTTPHelper::http_request(const unsigned short& uiport)
{
  try {
    return perform_http_request_repeat(uiport, 1U, std::string{});
  }
  catch (std::exception const& e) {
    EXPECT_EQ(e.what(), std::string{});
  }

  return {};
}

std::string HTTPHelper::http_request_repeat(const unsigned short& uiport,
                                            const unsigned int& reps,
                                            const std::string& expected)
{
  try {
    unsigned int creps = reps;
    std::string body;

    while (creps-- > 0) {
      body = perform_http_request_repeat(uiport, 1U, expected);
    }

    return body;
  }
  catch (std::exception const& e) {
    EXPECT_EQ(e.what(), std::string{});
  }

  return {};
}

std::string HTTPHelper::perform_http_request_repeat(
    const unsigned short& uiport, const unsigned int& reps,
    const std::string& expected)
{
  namespace beast = boost::beast;
  namespace http = beast::http;
  namespace net = boost::asio;
  using tcp = net::ip::tcp;

  std::string body;

  std::string host = tests_address;
  std::string port = std::to_string(uiport);
  std::string target = "/";
  int version = 11;  // HTTP/1.1

  net::io_context ioc;

  // Resolve the host
  tcp::resolver resolver(ioc);
  auto const results = resolver.resolve(host, port);

  // Create the socket and connect
  tcp::socket socket(ioc);
  net::connect(socket, results.begin(), results.end());

  // Set up the HTTP GET request
  http::request<http::string_body> req{http::verb::get, target, version};
  req.set(http::field::host, host);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  auto creps = reps;
  while (creps-- > 0) {
    // Send the request
    EXPECT_GE(http::write(socket, req), 0);

    // Prepare buffer and container for the response
    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;

    // Receive the response
    EXPECT_GE(http::read(socket, buffer, res), 0);

    body = boost::beast::buffers_to_string(res.body().data());

    if (!expected.empty()) {
      EXPECT_EQ(body, expected);

      if (body != expected) {
        return body;
      }
    }
  }

  // Gracefully close the socket
  beast::error_code ec;
  socket.shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected) {
    throw beast::system_error{ec};
  }

  return body;
}