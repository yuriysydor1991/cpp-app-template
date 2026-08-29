## Changing the project and library name

Change the project name in the root [meson.build](/meson.build) by editing the first positional argument to `project(...)`. The library name derives automatically from this value and the project's major and minor versions: it is computed by `meson/template-project-misc-variables-declare/meson.build` as `<project_name>-<major_version>.<minor_version>` and exposed as `PROJECT_LIBRARY_NAME` (for example, `CppAppTemplate-0.12` when the project name is `CppAppTemplate` and the version is `0.12.0`).

Because the library name is derived, all downstream-facing artefacts will follow your new name automatically:

- the shared library file (`lib<PROJECT_LIBRARY_NAME>.so.<version>` on GNU/Linux),
- the public header install subdir (`<prefix>/include/<PROJECT_LIBRARY_NAME>/`),
- the pkg-config file (`<PROJECT_LIBRARY_NAME>.pc`),
- the CMake package-config directory (`<libdir>/cmake/<PROJECT_LIBRARY_NAME>/`).

The C++ namespaces of the library are **not** derived from the project name: rename them by hand as described by the [The library's installable public include header files](/doc/sections/en_US/4-8-the-librarys-installable-include-header-files.md) section. An application which depends on two libraries derived from this template needs every one of those names to differ.

Bumping the major version (the first segment of the `version:` argument in `project(...)`) is the supported way to break the ABI - it changes the library name, the soversion, and the include subdir together, so old consumers keep linking against the previous installed major.
