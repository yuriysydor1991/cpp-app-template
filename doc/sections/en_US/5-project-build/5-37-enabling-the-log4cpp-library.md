## Enabling the log4cpp library

The [log4cpp](https://log4cpp.sourceforge.net/) library carries the whole logging of the `appLog4Cpp5` branch, so the `ENABLE_LOG4CPP` CMake variable is an `ON` one by default and the build needs no extra parameter for it:

```
# Inside the source root directory

cmake -S . -B build
cmake --build build --target all
```

The [cmake/enablers/template-project-log4cpp-enabler.cmake](/cmake/enablers/template-project-log4cpp-enabler.cmake) module probes the system installation with `pkg-config`, since the autotools build of the log4cpp ships a `log4cpp.pc` file alone. When no system installation is found the sources of the `TEMPLATE_APP_LOG4CPP_GIT_TAG` tag get fetched from the `TEMPLATE_APP_LOG4CPP_GIT` repository instead, so a host with no [log4cpp development package](/doc/sections/en_US/3-requirements/3-11-required-packages-for-the-log4cpp.md) installed still configures and builds.

The CMake build of the fetched sources gets completed by the enabler with the `log4cpp/config.h` header of the POSIX values, with the include directories of the library and with the threading library to link, since the autotools configure step is the one writing all of that. The static library and the headers of such a build land into the project install as well, while a system installation is linked and left alone.

Both of the paths provide the very same `LOG4CPP::log4cpp` target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} LOG4CPP::log4cpp)
```

The [src/log/CMakeLists.txt](/src/log/CMakeLists.txt) module links it to the project executable and the [src/log/log4cpp5-init/CMakeLists.txt](/src/log/log4cpp5-init/CMakeLists.txt) one links it to the `TemplateLog4Cpp5ControllerObj` object library, so the `log4cpp5i::Log4Cpp5Init` sources see the headers of both of the paths.

An `OFF` value leaves the branch with no logging library to link at all, so set it only along with the replacement of the log4cpp5 logger by an own one.
