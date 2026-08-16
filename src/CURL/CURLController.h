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

  /**
   * @brief Sends the given body to the given URL with the HTTP POST method.
   *
   * @param url The URL to send the request to.
   * @param body The request body to send.
   * @param headers The additional HTTP headers, each one in the
   * "Name: value" form.
   *
   * @return Returns the response body buffer, which is empty in case of any
   * error. Check the last_response_code for the HTTP status of the answer.
   */
  virtual download_buffer& post(const std::string& url, const std::string& body,
                                const std::vector<std::string>& headers);

  /**
   * @brief Tells whether the last performed request has been answered with a
   * success status.
   *
   * Preferred over comparing the last_response_code value with a status of
   * it's own, so the calling code keeps no HTTP status constants at all.
   *
   * @return Returns true when the answer carries a success status or arrives
   * over a protocol that carries no statuses (the file one, for example),
   * false when the request has failed or the status reports anything but a
   * success, a redirect included.
   */
  virtual bool last_response_successfull() const;

  /**
   * @brief Gives the HTTP status code of the last performed request.
   *
   * @return Returns the HTTP status code or zero when no response has been
   * received at all or the protocol used carries no statuses (the file one,
   * for example).
   */
  virtual long last_response_code() const;

  virtual download_buffer& get();

  static CURLControllerPtr create();

 private:
  /**
   * @brief Clears the buffer and applies the options that are common for
   * every request kind.
   *
   * @param url The URL of the request to come.
   *
   * @return Returns true when the handle is ready for the perform call.
   */
  bool prepare(const std::string& url);

  /**
   * @brief Performs the prepared request and stores it's HTTP status code.
   *
   * @return Returns the response body buffer.
   */
  download_buffer& perform();

  inline static constexpr const download_buffer::size_type
      DEFAULT_BUFF_RESERVE = 10240U;
  inline static unsigned long long DEFAULT_TIMEOUT = 30L;
  inline static unsigned long long DEFAULT_CONNECTTIMEOUT = 10L;
  inline static unsigned long long DEFAULT_LOWSPEEDSECS = 10L;
  inline static unsigned long long DEFAULT_LOWSPEEDLIMIT = 1L;

  /// @brief A POST request may wait way longer than a plain download, because
  /// a server generating an answer keeps the connection silent meanwhile.
  inline static unsigned long long DEFAULT_POST_TIMEOUT = 300L;

  /// @brief The HTTP status codes range that reports a successfully answered
  /// request, so a redirect stays out of it.
  inline static constexpr const long HTTP_FIRST_SUCCESS_STATUS = 200L;
  inline static constexpr const long HTTP_LAST_SUCCESS_STATUS = 299L;

  download_buffer cbuff;
  CURL* curl{nullptr};
  long responseCode{0L};

  /// @brief Tells whether the last request has been performed at all, which
  /// separates the zero code of a protocol carrying no statuses from the one
  /// of a request that never reached a server.
  bool responseReceived{false};
};

using CURLControllerPtr = CURLController::CURLControllerPtr;

}  // namespace curli

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CURLCONTROLLER_CLASS_H
