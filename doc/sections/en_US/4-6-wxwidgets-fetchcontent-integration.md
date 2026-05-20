## wxWidgets via FetchContent

The wxWidgets library is not assumed to be installed on the build host. The reusable `cmake/enablers/template-project-wxwidgets-enabler.cmake` module therefore downloads and builds wxWidgets from source through the CMake [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) facility and exposes the `wx::core` and `wx::base` targets the component links against.

The behaviour is controlled by the next options and cache variables:

- `ENABLE_WXWIDGETS` (default `ON`) - set to `OFF` to drop the wxWidgets integration entirely.
- `WXWIDGETS_TRY_SYSTEM_PROBE` (default `ON`) - when a CMake-package enabled wxWidgets is already installed it is used as-is and nothing is downloaded.
- `TEMPLATE_APP_WXWIDGETS_GIT` / `TEMPLATE_APP_WXWIDGETS_GIT_TAG` - the source repository and the tag (version) of wxWidgets to fetch; bump the tag to build against a newer wxWidgets release.

On GNU/Linux wxWidgets builds its GTK backend, so the GTK development packages must be present for the FetchContent build (see the [requirements](/doc/sections/en_US/3-1-required-tools-for-the-GNU-Linux-based-OS.md) section). The first configuration clones and builds wxWidgets, which may take a while; subsequent configurations reuse the already populated build directory.
