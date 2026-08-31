## Quick build scripts

The [scripts/build](/scripts/build) directory holds the shell scripts which perform the CMake configure, build and install steps of the project, so a whole `Release` or `Debug` cycle takes a single command instead of the separate CMake calls described in the [Command line build](/doc/sections/en_US/5-project-build/5-2-command-line-build.md) section.

Every script keeps its build tree under the project `build` directory: the `Release` one at `build/release` and the `Debug` one at `build/debug`.

### Entry point scripts

Each of the scripts below performs the configure, the build and the install steps in a row. The `Debug` ones which build the whole project perform the test step as well, in between of the build and the install ones:

| Script | Performs |
| --- | --- |
| [release.sh](/scripts/build/release.sh) | the `Release` build |
| [debug.sh](/scripts/build/debug.sh) | the `Debug` build with the tests, the documentation, the `cppcheck`, the `valgrind` and the `callgrind` enabled |
| [debug-cppcheck.sh](/scripts/build/debug-cppcheck.sh) | the `Debug` build of the `cppcheck` target |
| [debug-valgrind.sh](/scripts/build/debug-valgrind.sh) | the `Debug` build of the `valgrind` target |
| [debug-callgrind.sh](/scripts/build/debug-callgrind.sh) | the `Debug` build of the `callgrind` target |
| [debug-clang-tidy.sh](/scripts/build/debug-clang-tidy.sh) | the `Debug` build with the `ENABLE_CLANG_TIDY` option |
| [debug-sanitizers.sh](/scripts/build/debug-sanitizers.sh) | the `Debug` build with the `ENABLE_SANITIZERS` option |
| [debug-sanitizers-threads.sh](/scripts/build/debug-sanitizers-threads.sh) | the `Debug` build with the `ENABLE_SANITIZERS_THREADS` option |
| [debug-compiler-analyzer.sh](/scripts/build/debug-compiler-analyzer.sh) | the `Debug` build with the `ENABLE_COMPILER_CODE_ANALYZER` option |

The [debug-cppcheck.sh](/scripts/build/debug-cppcheck.sh), the [debug-valgrind.sh](/scripts/build/debug-valgrind.sh) and the [debug-callgrind.sh](/scripts/build/debug-callgrind.sh) scripts build a single CMake target which the test executables are not a part of, so those three perform no test step at all.

A complete `Release` build takes the single command:

```
# inside the project root directory

scripts/build/release.sh
```

### Packager scripts

Each of the scripts below performs the `Release` configure step with a single packager option enabled and then builds the target which produces the package. There is no separate build step: each of those targets builds whatever it needs on its own, so nothing unused is built into the `build/release` directory beforehand. They accept the parameters of the entry point scripts above, and the produced package lands there:

| Script | Produces | The `--install` installs it with |
| --- | --- | --- |
| [build-appimage.sh](/scripts/build/build-appimage.sh) | the AppImage package - the `ENABLE_APPIMAGE` option and the `appimage` target | `install` into the `${HOME}/.local/bin` |
| [build-deb.sh](/scripts/build/build-deb.sh) | the DEB package - the `ENABLE_DEB` option and the `package` target | `sudo apt-get install` |
| [build-flatpak.sh](/scripts/build/build-flatpak.sh) | the flatpak bundle - the `ENABLE_FLATPAK` option and the `flatpak` target | `flatpak install --user` |
| [build-freebsd-pkg.sh](/scripts/build/build-freebsd-pkg.sh) | the FreeBSD pkg package - the `ENABLE_FREEBSD_PKG` option and the `package` target | `sudo pkg add` |
| [build-rpm.sh](/scripts/build/build-rpm.sh) | the RPM package - the `ENABLE_RPM` option and the `package` target | `sudo dnf install` |
| [build-snap.sh](/scripts/build/build-snap.sh) | the snap package - the `ENABLE_SNAP` option and the `snap` target | `sudo snap install --dangerous` |
| [build-wix.sh](/scripts/build/build-wix.sh) | the WIX MSI installer - the `ENABLE_WIX` option and the `package` target | `msiexec //i` |

An own `-D<variable>=<value>` argument is forwarded to the configure step after the packager option, so it overrides that option and every other project setting:

```
# inside the project root directory

scripts/build/build-deb.sh -DPROJECT_MAINTAINER_EMAIL=me@example.org
```

The packager options themselves, the tools they need and their own settings are described by the packager subsections of the [Project build](/doc/sections/en_US/5-project-build/5-project-build.md) section.

### Stage scripts

Every entry point script above is a chain of the stage scripts below, which may be started on their own when a single step is needed:

| Script | Performs |
| --- | --- |
| [release-configure.sh](/scripts/build/release-configure.sh), [debug-configure.sh](/scripts/build/debug-configure.sh) | the `cmake -B <build dir> -S .` configure step |
| [release-build.sh](/scripts/build/release-build.sh), [debug-build.sh](/scripts/build/debug-build.sh) | the `cmake --build <build dir>` build step |
| [debug-test.sh](/scripts/build/debug-test.sh) | the `ctest` test step inside the `Debug` build directory |
| [release-install.sh](/scripts/build/release-install.sh), [debug-install.sh](/scripts/build/debug-install.sh) | the `sudo cmake --install <build dir>` install step |

### Accepted parameters

The scripts accept the next parameters of their own, which are never passed to the CMake:

| Parameter | Effect |
| --- | --- |
| `--no-reconfigure` | Keeps the existing build directory and skips the configure step entirely. Without the parameter the configure step **erases** the build directory before configuring the project anew. |
| `--test` | Performs the test step, which starts the `ctest` command inside the `Debug` build directory. Without the parameter the test step is skipped. The parameter belongs to the `Debug` scripts alone, as the tests are enabled by their configure step only. |
| `--install` | Performs the install step. Without the parameter the install step is skipped, so no `sudo` password is ever asked for a plain build. The packager scripts install the package they have just produced instead, with the tool of that packager. |

Any `-D<variable>=<value>` argument is passed to the configure step, which makes every CMake option of this documentation available to the scripts:

```
# inside the project root directory

# the Release build with the DEB package generation enabled
scripts/build/release.sh -DENABLE_DEB=ON

# the same build reusing the already configured build directory,
# followed by the installation into the /usr prefix
scripts/build/release.sh --no-reconfigure --install

# the Debug build with the whole test suite performed right after it
scripts/build/debug.sh --test
```

The rest of the arguments are passed to the build, the test and the install steps, so an option which belongs to a single step is to be given to that stage script rather than to an entry point script:

```
# inside the project root directory

# builds a single target inside the already configured Debug build directory
scripts/build/debug-build.sh --target cppcheck

# runs a part of the test suite inside the already built Debug build directory
scripts/build/debug-test.sh --test -R "CTEST_log\."
```

The `cmake -B` configure call accepts neither the `--target` nor the `--verbose` option, so passing such an argument to an entry point script fails the configure step.
