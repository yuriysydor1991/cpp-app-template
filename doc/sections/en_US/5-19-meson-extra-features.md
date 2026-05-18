## Meson extra features

The `appMeson` branch ships with a Meson-based equivalent of the CMake feature set that the `app` branch has. Each feature is gated by a boolean `meson_options.txt` flag and can be turned on at configure time with `meson setup -D<OPTION>=true`. The wiring is centralised through the `template_project_extra_deps`, `template_project_extra_cpp_args` and `template_project_extra_link_args` Meson variables that are appended to by each enabler under `meson/template-project-<feature>-*/meson.build`.

The matrix below maps each option to a dedicated subsection so commands, install hints and target descriptions live next to the feature they enable.

### Optional 3rd-party libraries

| Option | Subsection |
|---|---|
| `-DENABLE_LIBCURL=true` | [Enabling the libcurl](/doc/sections/en_US/5-14-enabling-libcurl.md) |
| `-DENABLE_LIBXML2=true` | [Enabling the libxml2](/doc/sections/en_US/5-20-enabling-libxml2.md) |
| `-DENABLE_NLOHMANN_JSON=true` | [Enabling the nlohmann JSON library](/doc/sections/en_US/5-18-enabling-the-nlohmann-json-library.md) |
| `-DENABLE_OPENCV=true` | [Enabling the OpenCV](/doc/sections/en_US/5-21-enabling-OpenCV.md) |

### Analyzers and dynamic checks

| Option | Subsection |
|---|---|
| `-DENABLE_CPPCHECK=true` | [Enabling the static code analyzer target with cppcheck](/doc/sections/en_US/5-7-enabling-the-static-code-analyzer-target-with-cppcheck.md) |
| `-DENABLE_CLANGFORMAT=true` | [Enabling and performing code formatting target](/doc/sections/en_US/5-6-enabling-and-performing-code-formatting-target.md) |
| `-DENABLE_CLANG_TIDY=true` | [Enabling the static code analyzer with clang-tidy](/doc/sections/en_US/5-8-enabling-static-code-analyzer-with-clang-tidy.md) |
| `-DENABLE_VALGRIND=true` | [Enabling the dynamic memory check target with valgrind](/doc/sections/en_US/5-9-enabling-the-dynamic-memory-check-target-with-valgrind.md) |

### Sanitizers and profilers

| Option | Subsection |
|---|---|
| `-DENABLE_SANITIZERS=true` | [Enabling sanitizers](/doc/sections/en_US/5-13-enabling-sanitizers.md) |
| `-DENABLE_SANITIZERS_THREADS=true` | [Enabling sanitizers](/doc/sections/en_US/5-13-enabling-sanitizers.md) |
| `-DENABLE_GPROF=true` | [Enabling gprof profiler analysis](/doc/sections/en_US/5-15-enabling-gprof-profiler-analysis.md) |
| `-DENABLE_CALLGRIND=true` | [Enabling vagrind's callgrind profiler analysis](/doc/sections/en_US/5-16-enabling-valgrinds-callgrind-profiler-analysis.md) |

### Tests

| Option | Subsection |
|---|---|
| `-DENABLE_UNIT_TESTS=true` | [Enabling unit testing](/doc/sections/en_US/5-3-1-enabling-unit-testing.md) |
| `-DENABLE_COMPONENT_TESTS=true` | [Enabling component testing](/doc/sections/en_US/5-3-3-enabling-component-testing.md) |

### Packagers

Each packager is a `custom_target` that internally runs `meson install` into a staging directory and then invokes the underlying native packaging tool. None of them depend on a third-party CMake/CPack wrapper.

| Option | Output | Subsection |
|---|---|---|
| `-DENABLE_FLATPAK=true` | `<project>-<version>.flatpak` | [Enabling the flatpak package generation support](/doc/sections/en_US/5-11-enabling-the-flatpak-package-generation-support.md) |
| `-DENABLE_SNAP=true` | `<project>_<version>_<arch>.snap` | [Enabling the snap package generation support](/doc/sections/en_US/5-22-enabling-snap-package-generation.md) |
| `-DENABLE_DEB=true` | `<project>-<version>_<arch>.deb` | [Enabling the DEB package generation support](/doc/sections/en_US/5-23-enabling-deb-package-generation.md) |
| `-DENABLE_RPM=true` | `<project>-<version>-1.<arch>.rpm` | [Enabling the RPM package generation support](/doc/sections/en_US/5-24-enabling-rpm-package-generation.md) |
| `-DENABLE_FREEBSD_PKG=true` | `<project>-<version>.pkg` | [Enabling the FreeBSD pkg package generation support](/doc/sections/en_US/5-25-enabling-freebsd-pkg-package-generation.md) |
| `-DENABLE_APPIMAGE=true` | `<project>-<version>-<arch>.AppImage` | [Enabling the AppImage bundle generation support](/doc/sections/en_US/5-26-enabling-the-AppImage-bundle-generation.md) |
| `-DENABLE_WIX=true` | `<project>-<version>-win-<arch>.msi` | [Enabling the WIX MSI installer generation support](/doc/sections/en_US/5-27-enabling-the-WIX-MSI-installer-generation.md) |
| `-DENABLE_DOCKER=true` | container build and run | [Enabling the Docker container build and run](/doc/sections/en_US/5-12-enabling-the-docker-container-build-and-run.md) |

The DEB / RPM / FreeBSD pkg / WIX packagers share the `PROJECT_MAINTAINER` / `PROJECT_MAINTAINER_EMAIL` options - see [Project maintainer options](/doc/sections/en_US/5-28-project-maintainer-options.md).

### Doxygen

| Option | Subsection |
|---|---|
| `-DENABLE_DOC_DOXYGEN=true` | [Documentation build](/doc/sections/en_US/5-4-documentation-build.md) |
| `-DDOXYGEN_DO_INSTALL=true` | [Configuring the documentation install support](/doc/sections/en_US/5-5-configuring-the-documentation-install-support.md) |
