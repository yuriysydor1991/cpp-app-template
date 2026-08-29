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
 * else under src unmarked - see
 * doc/sections/en_US/4-project-structure/4-8-the-librarys-installable-include-header-files.md
 *
 * Current file is a target for the library header installation.
 */
#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef TEMPLATE_LIB_BUILDING
#define TEMPLATE_LIB_API __declspec(dllexport)
#else
#define TEMPLATE_LIB_API __declspec(dllimport)
#endif  // TEMPLATE_LIB_BUILDING
#else
#define TEMPLATE_LIB_API __attribute__((visibility("default")))
#endif  // _WIN32

#endif  // CPP_APP_TEMPLATE_012_LIBRARYAPI_H
