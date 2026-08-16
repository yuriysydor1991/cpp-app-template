#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GLOBAL_DECLS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GLOBAL_DECLS_H

#include <string>

/// @brief Global compile-time declarations of the project parameters
namespace project_decls {

/// @brief Global project' binary name
const std::string PROJECT_NAME = "TemplateApp" ;
/// @brief Global project' build version
const std::string PROJECT_BUILD_VERSION = "0.0.0" ;
/// @brief Global project' configure git commit hash
const std::string PROJECT_BUILD_COMMIT = "0000000" ;
/// @brief Global project' configure date
const std::string PROJECT_CONFIGURE_DATE = "1970-01-01" ;
/// @brief Global project' default HTTP listen address
const std::string PROJECT_HTTP_LISTEN_ADDRESS = "PROJECT_HTTP_LISTEN_ADDRESS" ;
/// @brief Global project' default HTTP listen address
constexpr const unsigned short PROJECT_HTTP_LISTEN_PORT = 0;

} // namespace project_decls

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_GLOBAL_DECLS_H
