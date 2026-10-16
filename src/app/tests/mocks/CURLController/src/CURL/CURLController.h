#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CURLCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CURLCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>
#include <string>
#include <vector>

namespace curli
{

class CURLController
{
 public:
  using download_buffer = std::vector<char>;
  using CURLControllerPtr = std::shared_ptr<CURLController>;

  virtual ~CURLController() = default;
  CURLController() = default;

  MOCK_METHOD(download_buffer, download, (const std::string& url));

  MOCK_METHOD(download_buffer, download,
              (const std::string& url,
               const std::vector<std::string>& headers));

  MOCK_METHOD(download_buffer, post,
              (const std::string& url, const std::string& body,
               const std::vector<std::string>& headers));

  MOCK_METHOD(bool, is_url_alive, (const std::string& url));

  MOCK_METHOD(bool, last_response_successful, (), (const));

  MOCK_METHOD(long, last_response_code, (), (const));

  MOCK_METHOD(download_buffer, get, ());

  /// @brief The instance handed out by the create method, so a test may set
  /// it's expectations before the tested code asks for a controller.
  inline static CURLControllerPtr instance{};

  inline static CURLControllerPtr create()
  {
    if (instance == nullptr) {
      instance = std::make_shared<CURLController>();
    }

    return instance;
  }
};

using CURLControllerPtr = CURLController::CURLControllerPtr;

}  // namespace curli

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CURLCONTROLLER_CLASS_H
