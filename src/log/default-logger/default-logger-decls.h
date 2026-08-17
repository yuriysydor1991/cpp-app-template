#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DEFAULT_LOGGER_DECLS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DEFAULT_LOGGER_DECLS_H

#ifndef TEMPLATE_DEFAULT_LOG_NAMESPACE
/**
 * @brief The default logger implementation C++ namespace name.
 *
 * CMake derives it from the top level project name through the
 * PROJECT_DEFAULT_LOG_NAMESPACE variable and hands it over as a compile
 * definition, so every project derived from this template owns a unique one.
 * A derived library carries an own copy of the whole logging subsystem, and two
 * libraries sharing this namespace share the real logger instance holder too:
 * the loader then binds the logging calls of both of them into whichever
 * library it resolved first, so the logger instance adopted by one library
 * silently serves the other one as well.
 *
 * The fallback below keeps the logging subsystem sources buildable inside a
 * project which declares no library of its own and therefore passes no
 * definition, so the very same files stay usable across the template branches.
 */
#define TEMPLATE_DEFAULT_LOG_NAMESPACE default_logger
#endif  // TEMPLATE_DEFAULT_LOG_NAMESPACE

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DEFAULT_LOGGER_DECLS_H
