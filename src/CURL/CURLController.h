#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CURLCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CURLCONTROLLER_CLASS_H

#include <curl/curl.h>

#include <memory>
#include <string>
#include <vector>

/**
 * @brief The libcurl adaptor subsystem namespace.
 */
namespace curli
{

/**
 * @brief The libcurl downloader class.
 */
class CURLController
{
 public:
  using download_buffer = std::vector<char>;
  using CURLControllerPtr = std::shared_ptr<CURLController>;

  virtual ~CURLController();
  CURLController();
  CURLController(const CURLController&) = delete;
  CURLController(CURLController&&) = delete;

  virtual download_buffer& download(const std::string& url);

  virtual download_buffer& get();

  static CURLControllerPtr create();

 private:
  inline static constexpr const download_buffer::size_type
      DEFAULT_BUFF_RESERVE = 10240U;
  inline static unsigned long long DEFAULT_TIMEOUT = 30L;
  inline static unsigned long long DEFAULT_CONNECTTIMEOUT = 10L;
  inline static unsigned long long DEFAULT_LOWSPEEDSECS = 10L;
  inline static unsigned long long DEFAULT_LOWSPEEDLIMIT = 1L;

  download_buffer cbuff;
  CURL* curl{nullptr};
};

using CURLControllerPtr = CURLController::CURLControllerPtr;

}  // namespace curli

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CURLCONTROLLER_CLASS_H
