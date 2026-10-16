#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_TESTHTTPCLIENT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_TESTHTTPCLIENT_CLASS_H

#include <string>

/**
 * @brief The minimal plain HTTP/1.0 client of the loopback interface for the
 * component tests.
 */
class TestHttpClient
{
 public:
  virtual ~TestHttpClient() = default;
  TestHttpClient() = default;

  /// @brief Returns a loopback TCP port number nobody listens to right now.
  static int free_port();

  /**
   * @brief Requests the path at the loopback port.
   *
   * @return Returns the whole response or an empty string on any failure.
   */
  static std::string get(int port, const std::string& path);
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_TESTHTTPCLIENT_CLASS_H
