#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COMPONENT_TESTS_HTTPHELPER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COMPONENT_TESTS_HTTPHELPER_CLASS_H

#include <string>

class HTTPHelper
{
 public:
  inline static const std::string tests_address = "127.0.0.1";
  static const std::string expected_standard_response;

  virtual ~HTTPHelper() = default;
  HTTPHelper() = default;

  static std::string http_request(const unsigned short& uiport);
  static std::string http_request_repeat(const unsigned short& uiport,
                                         const unsigned int& reps,
                                         const std::string& expected);

 private:
  static std::string perform_http_request(const unsigned short& uiport);
  static std::string perform_http_request_repeat(const unsigned short& uiport,
                                                 const unsigned int& reps,
                                                 const std::string& expected);
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_COMPONENT_TESTS_HTTPHELPER_CLASS_H