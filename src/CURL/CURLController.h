#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CURLCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CURLCONTROLLER_CLASS_H

#include <curl/curl.h>

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "project-global-decls.h"

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

  /**
   * @brief Downloads the data of the given URL with the HTTP GET method.
   *
   * @param url The URL to download the data from.
   *
   * @return Returns the response body buffer, which is empty in case of any
   * error. Check the last_response_code for the HTTP status of the answer.
   */
  virtual download_buffer& download(const std::string& url);

  /**
   * @brief Downloads the data of the given URL with the HTTP GET method,
   * sending the given additional headers (an authorization one, for example).
   *
   * @param url The URL to download the data from.
   * @param headers The additional HTTP headers, each one in the
   * "Name: value" form.
   *
   * @return Returns the response body buffer, which is empty in case of any
   * error. Check the last_response_code for the HTTP status of the answer.
   */
  virtual download_buffer& download(const std::string& url,
                                    const std::vector<std::string>& headers);

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
   * @brief Checks whether the given URL is reachable by requesting it's
   * headers only with the HTTP HEAD method, so no body gets downloaded.
   *
   * @param url The URL to check.
   *
   * @return Returns true when the request has been performed and the answer
   * carries no error status, false otherwise. A redirect counts as alive and
   * is not followed.
   */
  virtual bool is_url_alive(const std::string& url);

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

  /**
   * @brief Gives the buffer holding the body received by the last request.
   *
   * @note This is the internal buffer accessor and not an HTTP GET request.
   * Use the download call to perform one.
   *
   * @return Returns the response body buffer.
   */
  virtual download_buffer& get();

  /**
   * @brief Appends the received chunk to the response buffer, refusing the
   * one that would grow it over the allowed size.
   *
   * @note Called by the libcurl write callback and not by the using code,
   * which reads the assembled answer through the get method above.
   *
   * @param data The received chunk.
   * @param size The size of the received chunk.
   *
   * @return Returns true when the chunk has been stored and false when the
   * response has outgrown the allowed size, which aborts the transfer.
   */
  virtual bool append(const char* const data, const std::size_t size);

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
   * @return Returns the libcurl code of the performed request.
   */
  CURLcode perform();

  /**
   * @brief Applies the constraints that keep a hostile or a broken answer
   * from exhausting the resources of the calling application. Every one of
   * them is configured by the appropriate PROJECT_CURL_* CMake variable.
   *
   * @return Returns true when every constraint has been applied.
   */
  bool harden();

  inline static constexpr const download_buffer::size_type
      DEFAULT_BUFF_RESERVE = 10240U;
  /// @brief The libcurl reads every option below as a long one, so the
  /// constants carry that very type and no other.
  inline static constexpr const long DEFAULT_TIMEOUT =
      project_decls::PROJECT_CURL_TRANSFER_TIMEOUT_SECONDS;
  inline static constexpr const long DEFAULT_CONNECTTIMEOUT =
      project_decls::PROJECT_CURL_CONNECT_TIMEOUT_SECONDS;
  inline static constexpr const long DEFAULT_LOWSPEEDSECS = 10L;
  inline static constexpr const long DEFAULT_LOWSPEEDLIMIT = 1L;

  /// @brief A POST request may wait way longer than a plain download, because
  /// a server generating an answer keeps the connection silent meanwhile.
  inline static constexpr const long DEFAULT_POST_TIMEOUT =
      project_decls::PROJECT_CURL_POST_TIMEOUT_SECONDS;

  /// @brief The response above this size is refused instead of being
  /// buffered, so a server answering endlessly exhausts no memory.
  inline static constexpr const download_buffer::size_type MAX_RESPONSE_BYTES =
      project_decls::PROJECT_CURL_MAX_RESPONSE_BYTES;

  /// @brief The certificate check of the libcurl: the host name of the
  /// certificate is matched against the one of the URL.
  inline static constexpr const long SSL_VERIFY_HOSTNAME = 2L;

  /// @brief The lowest HTTP status code that reports a failure, so every
  /// status below it means a reachable URL.
  inline static constexpr const long HTTP_FIRST_ERROR_STATUS = 400L;

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
