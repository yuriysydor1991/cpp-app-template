## wxWidgets via FetchContent

The wxWidgets library is not assumed to be installed on the build host. The reusable `cmake/enablers/template-project-wxwidgets-enabler.cmake` module first looks for a ready CMake-package wxWidgets and otherwise downloads and builds it from source through the CMake [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) facility (the source build is delegated to the shared `template_project_default_3rdparty_enabler()` helper). Either way it exposes the `wx::core` and `wx::base` targets the component links against.

The behaviour is controlled by the next options and cache variables:

- `ENABLE_WXWIDGETS` (default `ON`) - set to `OFF` to drop the wxWidgets integration entirely.
- `TEMPLATE_APP_WXWIDGETS_GIT` / `TEMPLATE_APP_WXWIDGETS_GIT_TAG` (default `v3.3.2`) - the source repository and the tag (version) of wxWidgets to fetch; bump the tag to build against a newer wxWidgets release.

The probe is a CONFIG-mode `find_package(wxWidgets)`: when a CMake-package wxWidgets that provides the `wx::core` / `wx::base` targets is already available - a system installation, or the dedicated wxWidgets module of the [Flatpak package](/doc/sections/en_US/5-11-enabling-the-flatpak-package-generation-support.md) - it is used as-is and nothing is downloaded; otherwise wxWidgets is fetched and built from source. The CMake-shipped `FindwxWidgets` module (MODULE mode) is intentionally not used for the probe because it only fills `wxWidgets_LIBRARIES` and never defines those imported targets.

On GNU/Linux wxWidgets builds its GTK backend, so the GTK development packages must be present for the FetchContent build (see the [requirements](/doc/sections/en_US/3-1-required-tools-for-the-GNU-Linux-based-OS.md) section). The first configuration clones and builds wxWidgets, which may take a while; subsequent configurations reuse the already populated build directory.
