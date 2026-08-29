## Changing the project and executable name

Change the name of the project in the project's root `CMakeLists.txt` file by introducing a new value for the the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable which is located at `cmake/template-project-misc-variables-declare.cmake`. It is recommended to do so the executable will represent your new application name instead of templated default one - the `CppAppTemplate`.

The destination library name is derived from that project name and from the project version by the `cmake/template-project-misc-variables-declare.cmake` file and is exposed as the `PROJECT_LIBRARY_NAME` variable - `libCppAppTemplate-0.12` for the untouched template. See the [Customizing the installable library name segments](/doc/sections/en_US/5-project-build/compression/5-23-customizing-library-name-segments.md) section for the options which decide its version segments.

The C++ namespaces of the library are **not** derived from the project name: rename them by hand as described by the [The library's installable include header files](/doc/sections/en_US/4-project-structure/4-9-the-librarys-installable-include-header-files.md) section. An application which depends on two libraries derived from this template needs every one of those names to differ.
