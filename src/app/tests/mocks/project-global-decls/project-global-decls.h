#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GLOBAL_DECLS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GLOBAL_DECLS_H

#include <string>

namespace project_decls
{

const std::string PROJECT_NAME = "CppAppTemplate";
const std::string PROJECT_BUILD_VERSION = "0.2.0";
const std::string PROJECT_BUILD_COMMIT =
    "848bea167db708811563e941cefb6b7787879599";
const std::string PROJECT_CONFIGURE_DATE = "2025-03-05 12:39:11 EET";
const std::string PROJECT_HTTP_LISTEN_ADDRESS = "127.0.0.1";
constexpr const unsigned short PROJECT_HTTP_LISTEN_PORT = 8080;
constexpr const unsigned long long PROJECT_HTTP_MAX_REQUEST_BODY_BYTES =
    8388608;
constexpr const unsigned long PROJECT_HTTP_MAX_REQUEST_HEADER_BYTES = 8192;
constexpr const unsigned int PROJECT_HTTP_REQUEST_TIMEOUT_SECONDS = 30;
constexpr const unsigned int PROJECT_HTTP_RESPONSE_TIMEOUT_SECONDS = 30;
constexpr const unsigned int PROJECT_HTTP_MAX_CONNECTIONS = 128;
constexpr const int PROJECT_HTTP_LISTEN_BACKLOG = 128;

}  // namespace project_decls

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GLOBAL_DECLS_H
