## Choosing the library type

The `LIB_TYPE` option builds the project library either as a shared or as a static one:

| Option | Default | Effect |
|---|---|---|
| `-DLIB_TYPE=SHARED` | `SHARED` | Builds the `lib<NAME>.so` shared library |
| `-DLIB_TYPE=STATIC` | | Builds the `lib<NAME>.a` static library |

Without the `LIB_TYPE` given, the `-DBUILD_SHARED_LIBS=OFF` (the one the vcpkg and the Conan package managers pass) selects the static library too.

A static library build and install:

```
# inside the project root directory

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DLIB_TYPE=STATIC
cmake --build build
cmake --install build --prefix /usr/local
```

A downstream CMake project consumes both types the same way, see [Installing the library development files](/doc/sections/en_US/5-project-build/5-37-installing-the-library-development-files.md). What differs for the static library:

- The executable of the project carries the code of the static library itself: it needs no RUNPATH, shares a single logging subsystem copy with the library, and the `-DLIB_INSTALL_DEV_FILES=OFF` installation of it is the executable alone.
- The `<libdir>/lib<NAME>.a` is a development file as a whole, so the `-DLIB_INSTALL_DEV_FILES=OFF` runtime only installation installs no library at all.
- The library hands the `TEMPLATE_LIB_STATIC` definition over to its users through the CMake package, which drops the MS Windows `__declspec` pair of the `TEMPLATE_LIB_API` macro in [LibraryAPI.h](/src/lib/facade/public/LibraryAPI.h). Define it by hand when linking the library without the CMake package on the MS Windows.
- The third-party libraries the enablers link into the library (the libcurl, the libxml2, the nlohmann json, the OpenCV and the OpenSSL ones) become link dependencies of every library user. Find them in the [TemplateLibraryConfig.cmake.in](/src/lib/cmake/TemplateLibraryConfig.cmake.in) before its `include()` line, e.g. `include(CMakeFindDependencyMacro)` followed by `find_dependency(CURL)` for the libcurl.
- The objects of a static library join the binary which links it, so the hidden symbol visibility no longer keeps the logging subsystem copies of two derived libraries apart - they silently share a single logger. Rename the `default_logger` namespace too, see [Renaming the library namespaces](/doc/sections/en_US/4-project-structure/4-9-the-librarys-installable-include-header-files.md#renaming-the-library-namespaces).

The option is declared in [cmake/template-project-misc-variables-declare.cmake](/cmake/template-project-misc-variables-declare.cmake) and consumed by [src/lib/CMakeLists.txt](/src/lib/CMakeLists.txt).
