## Changing the project and executable name

Change the name of the project in the project's appropriate `meson.build` file by introducing a new value for the the `PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable which is located at `meson/template-project-dockerers/meson.build`. It is recommended to do so the executable will represent your new application name instead of templated default one - the `CppAppTemplate`.

The installable library name is derived from the project name and the project version by `meson/template-project-misc-variables-declare/meson.build` and exposed as `PROJECT_LIBRARY_NAME` - `libCppAppTemplate-0.11` for the untouched template. See the [Customizing the installable library name segments](/doc/sections/en_US/5-29-customizing-library-name-segments.md) section for the options which decide its version segments.

The C++ namespaces of the library are **not** derived from the project name: rename them by hand as described by the [The library's installable public include header files](/doc/sections/en_US/4-9-the-librarys-installable-include-header-files.md) section. An application which depends on two libraries derived from this template needs every one of those names to differ.
