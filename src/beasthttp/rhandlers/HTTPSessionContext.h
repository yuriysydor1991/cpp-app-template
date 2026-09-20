#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPSESSIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPSESSIONCONTEXT_CLASS_H

#include <chrono>
#include <cstdint>
#include <memory>

#include "project-global-decls.h"
#include "src/beasthttp/beast-includes.h"

namespace beasthttp::rhandlers
{

/**
 * @brief The single HTTP session class. Holds required info
 * with buffers and other objects to handle the single HTTP session.
 *
 * Holds the hardening constraints of the session too. Every one of them
 * starts with the value the appropriate PROJECT_HTTP_* CMake variable has
 * been configured with and may be lowered for a particular session by an
 * overridden HttpController::create_http_session_context method.
 */
class HTTPSessionContext
{
 public:
  virtual ~HTTPSessionContext();
  HTTPSessionContext();

  /**
   * @brief Shuts the connection down and closes it. Called once the session
   * is over, so the connection is released right away and not whenever the
   * context happens to be destroyed.
   */
  void close();

  /// @brief The execution context of the stream below. The session owns it,
  /// so the timeouts of the session are driven by the thread handling it and
  /// by no other one.
  std::shared_ptr<boost::asio::io_context> ioc;

  /// @brief The accepted stream through witch all the requests and responses
  /// will be passed. A Boost.Beast stream and not a plain socket, since the
  /// timeouts below are honored by no blocking socket call.
  std::shared_ptr<boost::beast::tcp_stream> stream;

  /// @brief The boost flat buffer to read the HTTP requests.
  boost::beast::flat_buffer buffer;

  /// @brief The parsed request by the Boost Beast HTTP server.
  http::request<http::string_body> request;

  /// @brief The response object which will contain assembled response page.
  http::response<http::string_body> response;

  /// @brief The Boost Beast error code if any for read and/or write operations.
  boost::beast::error_code ec;

  /// @brief The time the whole request reading may take before the connection
  /// is dropped, which leaves no thread pinned by a client that sends it's
  /// request byte by byte or never finishes it at all.
  std::chrono::seconds requestTimeout{
      project_decls::PROJECT_HTTP_REQUEST_TIMEOUT_SECONDS};

  /// @brief The time the whole response writing may take before the
  /// connection is dropped, which leaves no thread pinned by a client that
  /// stops reading the answer it has asked for.
  std::chrono::seconds responseTimeout{
      project_decls::PROJECT_HTTP_RESPONSE_TIMEOUT_SECONDS};

  /// @brief The maximum size of the request headers, the request line
  /// included. A bigger one is refused by the parser instead of being
  /// buffered.
  std::uint32_t maxHeaderBytes{
      project_decls::PROJECT_HTTP_MAX_REQUEST_HEADER_BYTES};

  /// @brief The maximum size of the request body. A bigger one is refused by
  /// the parser instead of being buffered.
  std::uint64_t maxBodyBytes{
      project_decls::PROJECT_HTTP_MAX_REQUEST_BODY_BYTES};
};

}  // namespace beasthttp::rhandlers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPSESSIONCONTEXT_CLASS_H
