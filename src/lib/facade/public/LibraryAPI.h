#ifndef CPP_APP_TEMPLATE_012_LIBRARYAPI_H
#define CPP_APP_TEMPLATE_012_LIBRARYAPI_H

/**
 * @brief Marks the entities which make up the installable library interface.
 *
 * The library is compiled with the hidden symbol visibility, so that its
 * implementation - the lib0impl factory and library, the default_logger copy
 * and the project_decls constants - stays private to the shared object. That
 * is a correctness requirement and not a size optimisation: every library
 * derived from this template carries those very same names, and an application
 * which loads two of them would otherwise let the dynamic linker bind the calls
 * of one library into the definitions of the other.
 *
 * Mark every newly introduced installable class with it and leave everything
 * else under src unmarked.
 *
 * The build defines the TEMPLATE_LIB_STATIC for a static library and its
 * users, which need no __declspec pair.
 *
 * Current file is a target for the library header installation.
 */
#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef TEMPLATE_LIB_STATIC
#define TEMPLATE_LIB_API
#elif defined(TEMPLATE_LIB_BUILDING)
#define TEMPLATE_LIB_API __declspec(dllexport)
#else
#define TEMPLATE_LIB_API __declspec(dllimport)
#endif  // TEMPLATE_LIB_STATIC
#else
#define TEMPLATE_LIB_API __attribute__((visibility("default")))
#endif  // _WIN32

#endif  // CPP_APP_TEMPLATE_012_LIBRARYAPI_H
