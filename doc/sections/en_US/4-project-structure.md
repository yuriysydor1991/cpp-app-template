## Implement code straight away!

To proceed the application implementation right away look for the `main.cpp` file which is designed to accept initial code of the application. Specifically, new code may be placed into the `int main(int argc, char** argv)` free function.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `main.cpp` file implementation, rather than put all the code inside the `main` function itself.

## Changing the project and executable name

Change the name of the project in the project's root `CMakeLists.txt` file by introducing a new value for the the `PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable which is located at `cmake/template-project-misc-variables-declare.cmake`. It is recommended to do so the executable will represent your new application name instead of templated default one - the `CppAppTemplate`.

## Version tracking and other project parameters

The project's `CMakeLists.txt` files are tracking of a current project git repository commit, project name, configure date and projects version that are forwarded into the projects's configure header file located at `src/app/project-global-decls.h.in`. The `project-global-decls.h.in` will be compiled into the build directory as `project-global-decls.h`. The `ApplicationVersionPrinter` class includes this project's configure file and uses the information provided to print appropriate version info. Usually, this code is executed by calling generated executable with a `-v` or `--version` command line flag. After the version is printed, the default implementation cause the application's `ApplicationVersionPrinter` instance to return zero value and cause the executable to stop it's execution.

## Project tests

Project already contains some simple test samples. Based on them you may implement full test of the introduced code. 

See the [Project build](#project-build) subsection to enable unit testing with CMake.

### Google Test

Currently test samples are based on the GTest framework. GTest framework by itself becomes available by the `FetchContent_Declare`/`FetchContent_MakeAvailable` CMake-commands if no system GTest is available. 

Of course, the project's CMakeLists.txt files are probing the GTest only if tests are enabled by `ENABLE_UNIT_TESTS` CMake variable. System GTest probe may be turned OFF by setting appropriate value to the `GTEST_TRY_SYSTEM_PROBE` CMake variable.

Look for a `cmake/template-project-GTest-enabler.cmake` to see details or change GTest version etc.

## Extensions

There will be introduced some other standard project features in the future.