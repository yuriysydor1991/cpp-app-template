## Meson extra features

The `appMeson` branch ships with a Meson-based equivalent of the CMake feature set that the `app` branch has. Each feature is gated by a boolean `meson_options.txt` flag and can be turned on at configure time with `meson setup -D<OPTION>=true`.

### Optional 3rd-party libraries

All four optional libraries are probed through Meson's `dependency()` (pkg-config first, CMake fallback). They are OFF by default - flip them on if the project actually uses the library.

| Option | Effect | System package (Debian/Ubuntu) |
|---|---|---|
| `-DENABLE_LIBCURL=true` | adds `libcurl` to the main binary and to `applib` | `libcurl4-openssl-dev` |
| `-DENABLE_LIBXML2=true` | adds `libxml-2.0` | `libxml2-dev` |
| `-DENABLE_NLOHMANN_JSON=true` | adds the header-only `nlohmann_json` | `nlohmann-json3-dev` |
| `-DENABLE_OPENCV=true` | adds OpenCV (`opencv4`) | `libopencv-dev opencv-data` |

The wiring is centralised through the `template_project_extra_deps` Meson variable that is appended to by every enabler under `meson/template-project-<lib>-enabler/meson.build`.

### Analyzers and dynamic checks

| Option | Effect | Required tool |
|---|---|---|
| `-DENABLE_CPPCHECK=true` | adds the `cppcheck` Meson target | `cppcheck` |
| `-DENABLE_CLANGFORMAT=true` | adds the `clang-format` target | `clang-format` |
| `-DENABLE_CLANG_TIDY=true` | adds the `clang-tidy` target driven by the project's `misc/.clang-tidy` | `clang-tidy` |
| `-DENABLE_VALGRIND=true` | adds a `valgrind` memory-check target on the main binary | `valgrind` |

Run any of them with `meson compile -C build <target-name>` (e.g. `meson compile -C build cppcheck`).

### Sanitizers and profilers

| Option | Effect |
|---|---|
| `-DENABLE_SANITIZERS=true` | rebuilds the main binary with `-fsanitize=address,leak,undefined` |
| `-DENABLE_SANITIZERS_THREADS=true` | rebuilds the main binary with `-fsanitize=thread` (mutually exclusive with the previous one) |
| `-DENABLE_GPROF=true` | instruments the build with `-pg -fprofile-generate` and adds the `gprof-analyze` target |
| `-DENABLE_CALLGRIND=true` | adds a `callgrind` Meson target that runs `valgrind --tool=callgrind` on the binary |

The profilers require `--buildtype=debug`. Sanitisers can be combined with any build type.

### Tests

| Option | Effect |
|---|---|
| `-DENABLE_UNIT_TESTS=true` | builds the `UTEST_*` executables under `src/app/tests/unit/...` |
| `-DENABLE_COMPONENT_TESTS=true` | builds the `CTEST_app` executable under `src/app/tests/component/` |

Both feed into `meson test -C build` and into the Meson-managed `test()` registrations.

### Packagers

Each packager is a `custom_target` that internally runs `meson install` into a staging directory and then invokes the underlying native packaging tool. None of them depend on a third-party CMake/CPack wrapper.

| Option | Output | Native tool that is shelled-out internally |
|---|---|---|
| `-DENABLE_FLATPAK=true` | `<project>-<version>.flatpak` | `flatpak-builder`, `flatpak` |
| `-DENABLE_SNAP=true` | `<project>_<version>_<arch>.snap` | `snapcraft` |
| `-DENABLE_DEB=true` | `<project>-<version>_<arch>.deb` | `dpkg-deb` |
| `-DENABLE_RPM=true` | `<project>-<version>-1.<arch>.rpm` | `rpmbuild` |
| `-DENABLE_FREEBSD_PKG=true` | `<project>-<version>.pkg` | `pkg(8)` (FreeBSD-only) |
| `-DENABLE_APPIMAGE=true` | `<project>-<version>-<arch>.AppImage` | `meson install` + built-in `tar` |
| `-DENABLE_WIX=true` | `<project>-<version>-win-<arch>.msi` | WiX Toolset (`candle.exe` / `light.exe`) (Windows only) |
| `-DENABLE_DOCKER=true` | container build and run | `docker` |

For DEB / RPM / FreeBSD pkg / WIX the per-package metadata is configured through `meson_options.txt` options `PROJECT_MAINTAINER` and `PROJECT_MAINTAINER_EMAIL`. For example:

```
meson setup build -DENABLE_DEB=true \
  -DPROJECT_MAINTAINER='Your Name' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
meson compile -C build deb
```

The resulting artefact lands in the build directory.

### Doxygen

`-DENABLE_DOC_DOXYGEN=true` keeps its previous behaviour - building the Doxygen documentation under `doc/`. `-DDOXYGEN_DO_INSTALL=true` installs the generated documentation alongside the binary.
