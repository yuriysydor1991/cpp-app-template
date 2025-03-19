**Your C++ library template project**

# Goal of the template project

Project is designed to increase the speed of the library creation process at the project startup by providing templated library structure. So developer may just jump straight into implementing a particular library with no or minimum project start structure set up.

**Just fork it and implement your library straight away!**

Examine available branches to find your most applicable variant of the template:
- `master` branch at [project root page](https://github.com/yuriysydor1991/cpp-app-template) with just general application related classes to generate a single binary executable.
- `applib` branch at [applib](https://github.com/yuriysydor1991/cpp-app-template/tree/applib) for the application binary with additional separate library binary and header files (available for the installation) in order to provide library's code reusability across multiple applications.
- `lib` branch at [lib](https://github.com/yuriysydor1991/cpp-app-template/tree/lib) (**current**) for the library with the headers include files (and documentation) without target binary.
- `appQt6` branch at [appQt6](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6) for the application general classes with additional defined structure for the Qt6 QML window application development.
- `appGtkmm3` branch at [appGtkmm3](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3) for the application general classes with additional defined structure for the Gtkmm-3.0 with C++ window application development.
- `appGtkmm3Glade` branch at [appGtkmm3Glade](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3Glade) for the application general classes with additional defined structure for the C++ application development with Gtkmm-3.0 and [Glade](https://en.wikipedia.org/wiki/Glade_Interface_Designer) application with XML UI creation.
- `appFreeGlut` branch at [appFreeGlut](https://github.com/yuriysydor1991/cpp-app-template/tree/appFreeGlut) with just general application related classes to generate a single binary executable with a FreeGlut library for the OpenGL 3D development.
- `appSDL2` branch at [appSDL2](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDL2) with just general application related classes to generate a single binary executable with a [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) library for the OpenGL 3D development and more!

Alter current `README.md` and a `CHANGELOG.md` files to match your implementation introduced into the template project. Examine the `doc` directory for possible translations of a current md document:
- `uk_UA` at [doc/README.uk_UA.md](doc/README.uk_UA.md)

See more at the [kytok.org.ua](http://www.kytok.org.ua/)

# Cloning the C++ template project

In order to fast-start implementing a new library clone this project into your local directory by executing next command in the terminal (GNU/Linux based):

```
git clone https://github.com/yuriysydor1991/cpp-app-template.git
```

After this command executes you should find a directory named `cpp-app-template` inside your current one. So enter it by calling `cd cpp-app-template`.

# Forking and replacing the origin

In order to copy all the template project into your new clean repository (**clean repository with no** `README.md`, `.gitignore`, `LICENCE` or any other files) clone the current cpp-app-template project into your local directory and perform origin replacement command from inside the project root directory:

```
# REPLACE next URL with yours
git remote set-url origin https://github.com/yuriysydor1991/cpp-app-template.git
```

Replace the `https://github.com/yuriysydor1991/cpp-app-template.git` URL with one of your newly created project repository URL.

To verify successful repository remote URL (where all the changes will be pushed) replacement execute next command:

```
git remote -v
```

Which should show your new project repository.

Finally push your repository to a new location by executing next command:

```
git push
```

Forking may be performed in git Web interface panel.

# Requirements

This section contains list of required packages and/or tools that must be present in the system in order to build templated project.

## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

## Required tools for the MS Windows based OS

In order to build project binaries download the install tool for the developer tools from the MSVC download page [https://visualstudio.microsoft.com/downloads/](https://visualstudio.microsoft.com/downloads/) and search and enable for the Native C++ application development section.

Separately each project may be downloaded and installed from different sources (**may require additional tools download and install**): 
- The Git versioning system at [https://git-scm.com/downloads/win](https://git-scm.com/downloads/win)
- The CMake build system at [https://cmake.org/download/](https://cmake.org/download/)
- The Windows 10 SDK at [https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/)

## Optional for the tests

If necessary to build and execute available tests install GTest or ensure available Internet access in order to project make it available by itself (GNU/Linux based):

```
sudo apt install -y googletest
```

Examine the [Project tests](#project-tests) for more info.

## Optional for the documentation

If necessary to generate the Doxygen documentation from the sources comments install doc generation system also (GNU/Linux based):

```
sudo apt install -y doxygen graphviz
```

Examine the [Documentation build](#documentation-build) section on how to enable documentation enable/build/install.

## Optional for the code formatting

To auto format code using available `clang-format` target the `clang-format` code formatter must be installed (GNU/Linux based):

```
sudo apt install -y clang-format
```

Examine configuring details in the [Enabling and performing code formatting target](#enabling-and-performing-code-formatting-target) subsection.

## Optional for the code analyzer (cppcheck)

In order to perform a static code analysis with the `cppcheck` command install it with next command (GNU/linux based):

```
sudo apt install -y cppcheck
```

## Optional for the code analyzer with clang-tidy

In order to perform a static code analysis with the `clang-tidy` command install it with next command (GNU/linux based):

```
sudo apt install -y clang-tidy
```

Examine the [Enabling the static code analyzer with clang-tidy](#enabling-the-static-code-analyzer-with-clang-tidy) section on how to enable the `cppcheck` target.

# Project structure

## Implement code straight away!

To proceed the library implementation right away look for the `LibMain` class' `LibMain.cpp` file which is designed to accept initial code of the library. Specifically, new code may be placed into the `bool LibMain::libcall(std::shared_ptr<LibraryContext> ctx)` method. 

The `LibMain` class will be compiled into destination target library in order to make it's implementation available for other external applications to reuse it.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the library and include them into the `LibMain` class implementation, rather than put all the code inside the `LibMain` class itself (thats may be ok for a trivial library).

## Changing the project and executable name

Change the name of the project in the project's root `CMakeLists.txt` file by introducing a new value for the the `PROJECT_NAME`. It is recommended to do so the executable will represent your new library name instead of templated default one - the `libCppAppTemplateLib` (the `lib` prefix is adding automatically).

To change the destination library name change the `PROJECT_LIBRARY_NAME` variable value located at the `cmake/template-project-misc-variables-declare.cmake` file. It's default value will take the `PROJECT_NAME` value and appends the `Lib` string into it. For example, if name of the project is not changed yet the library will have the `libCppAppTemplateLib` name.

## Version tracking and other project parameters

The project's `CMakeLists.txt` files are tracking of a current project git repository commit, project name, configure date and projects version that are forwarded into the projects's configure header file located at `src/app/project-global-decls.h.in`. The `project-global-decls.h.in` will be compiled into the build directory as `project-global-decls.h`.

## Project tests

Project already contains some simple test samples. Based on them you may implement full test of the introduced code. 

See the [Project build](#project-build) subsection to enable unit testing with CMake.

### Google Test

Currently test samples are based on the GTest framework. GTest framework by itself becomes available by the `FetchContent_Declare`/`FetchContent_MakeAvailable` CMake-commands if no system GTest is available. 

Of course, the project's CMakeLists.txt files are probing the GTest only if tests are enabled by `ENABLE_UNIT_TESTS` CMake variable. System GTest probe may be turned OFF by setting appropriate value to the `GTEST_TRY_SYSTEM_PROBE` CMake variable.

Look for a `cmake/template-project-make-GTest-available.cmake` to see details or change GTest version etc.

## Extensions

There will be introduced some other standard project features in the future.

# Project build

## IDE build

Of course if your IDE supports CMake build system integration you may just press the `Build` and/or `Run` button somewhere in the IDE window with opened project and it's done! No need to perform a search and execute commands.

## Command line build

The project uses the CMake build system so a build command should be familiar to the most of the C++ developers around the world!

Of course, project needs to be `git clone`-ed and it's root directory must be opened in the terminal or in your IDE first. After that you may execute next commands:

```
# from the project root

mkdir -vp build && cd build && cmake ../ && cmake --build . --target all
```

Which effectively will create a directory named `build` (it's already added to the `.gitignore` list), configure project using the CMake available in the system (see the [Requirements](#requirements) section of this `README.md` file) and finally builds all the targets available in the project.

## Enabling testing

### Enabling unit testing

To enable project unit test availability (for building and running) reconfigure it with enabled `ENABLE_UNIT_TESTS` variable as follows (GNU/Linux based):

```
# from the project root

mkdir -vp build && cd build && cmake ../ -DENABLE_UNIT_TESTS=ON && cmake --build . --target all
```

### Disabling system GTest probe 

To disable the system available GTest framework assets usage set appropriate value to the `GTEST_TRY_SYSTEM_PROBE` CMake variable by executing command like (GNU/Linux based):

```
mkdir -vp build && cd build && cmake ../ -DENABLE_UNIT_TESTS=ON -DGTEST_TRY_SYSTEM_PROBE=OFF && cmake --build . --target all
```

During command execution project build system will try to make GTest available through the Internet only for current project with specified version in the `cmake/template-project-make-GTest-available.cmake` file.

## Documentation build

Currently it's possible to auto-generate the project documentation by the Doxygen tool from the available sources comments.

To enable Doxygen documentation CMake-target during the project configure process call a command that sets the `ENABLE_DOC_DOXYGEN` CMake variable to the `ON` value (GNU/Linux based):

```
# inside the project root directory 

mkdir -vp build && cd build && cmake ../ -DENABLE_DOC_DOXYGEN=ON
```

Which effectively will create a directory named `build` inside the project root directory, enters it by a `cd` command and configures project to enable Doxygen documentation build.

Finally build the documentation by executing the command:

```
# inside the project build directory

cmake --build . --target Doxygen-doc
```

Which in turn will generate the `doc/CppAppTemplate-html` directory (already added to the `.gitignore` file) which will contain the HTML-type documentation. In order to open and examine generated documentation open the `doc/CppAppTemplate-html/index.html` file. The `CppAppTemplate-html` directory name will change if changed default executable name for the project by setting a new value for the `PROJECT_NAME` in the `CMakeLists.txt` file or `PROJECT_LIBRARY_NAME` variable in the `template-project-misc-variables-declare.cmake` file or the `DOXYGEN_OUT_HTML_NAME` variable which in turn set the whole name for the directory.

The `doc/Doxyfile.in` file contains all available Doxygen configuration parameters which may be changed in order to change the documentation output.

## Configuring the documentation install support

It's possible to enable support for the document installation by setting up the `ENABLE_DOC_DOXYGEN` and `DOXYGEN_DO_INSTALL` variables to `ON` value during the project configure stage.

```
# inside the project build directory

cmake ../ -DENABLE_DOC_DOXYGEN=ON -DDOXYGEN_DO_INSTALL=ON
```

The `DOXYGEN_OUT_HTML_NAME` CMake variable will configure the documentation html directory name (passed into the `Doxyfile`).

## Enabling and performing code formatting target

In order to make `clang-format` target available set the `ENABLE_CLANGFORMAT` variable value to `ON` during the project configuration stage (GNU/Linux based):

```
# inside the project root directory 

mkdir -vp build && cd build && cmake ../ -DENABLE_CLANGFORMAT=ON
```

To perform the whole project code format in accordance with available `misc/.clang-format` code formatter configuration execute next building command:

```
# inside the project build directory

cmake --build . --target clang-format
```

The `clang-format` target details may be examined and/or altered in the `cmake/template-project-clang-format-target.cmake` CMake submodule file.

## Enabling the static code analyzer target with cppcheck

In order to make the cppcheck target available for the execution, configure project with enabled `ENABLE_CPPCHECK` variable:

```
# inside the project root directory 

mkdir -vp build && cd build && cmake ../ -DENABLE_CPPCHECK=ON
```

And to perform the actual static code analysis by itself run the `cppcheck` target for the build:

```
# inside the project build directory

cmake --build . --target cppcheck
```

The `cppcheck` target details may be examined and/or altered in the `cmake/template-project-cppcheck-target.cmake` CMake submodule file.

## Enabling the static code analyzer with clang-tidy

In order to enable the static code check for the each translation unit or each `*.cpp` file in the project with a `clang-tidy` application enable it during the project configuration stage by setting the `ENABLE_CLANG_TIDY` variable value to `ON` in the configuration command:

```
# inside the project root directory

mkdir -vp build && cd build && cmake ../ -DENABLE_CLANG_TIDY=ON
```

And to perform the actual static code analysis by itself build any target of interest and the `clang-tidy` command will perform check on each of the compilation target:

```
# inside the project build directory

cmake --build . --target all
```

For more information about the `clang-tidy` examine the `cmake/template-project-clang-tidy-target.cmake`, `misc/.clang-tidy` files
and the `clang-tidy` application documentation of a used version.

**Warning!** The `clang-tidy` static code analysis may dramatically increase the code compilation time.

# Run available executables

## Tests run

### Run tests by the ctest

If enabled by the developer through the `ENABLE_UNIT_TESTS` variable and successfully build, the one may run all available test by the `ctest` command from a project build directory (GNU/Linux based):

```
# run from the project build directory

ctest
```

Alternatively, run the `ctest` command from any location by specifying the test dir (GNU/Linux based):

```
ctest --tests-dir /path/to/the/project/build/directory
```

In order to run particular test execute the `ctest` command with test's name after the `-R` command line flag. For example, for the `UTEST_LibraryFacade` test it'll look something like this:

```
# from the project build directory 

ctest -R UTEST_LibraryFacade
```

### Manual tests run

Currently tests are separated in different files named with `UTEST_*` pattern for the unit tests.

You may search for all compiled available tests by a next command:

```
# from the project root or a build directory

find -type f -executable -name 'UTEST_*'
```

After that, choose particular test of interest and execute it manually if needed. For example, for the `LibraryFacade` class pass it's UT relative file system path from a project's root directory into the command line and hit enter (GNU/Linux based):

```
# from the project root

./build/src/lib/facade/tests/unit/LibraryFacade/UTEST_LibraryFacade
```

# Installing

Execute available install commands from the project's build directory.

## Default installation

In order to install generated executable (as shown previous) file into your's system binary default folder execute next command in the command line (GNU/Linux based):

```
# installs generated library under the /usr/local/lib/ for example
# and installs header include files under the /usr/local/include/libCppAppTemplateLib
# run from the project's build directory

sudo cmake --install .
```

Usually it's the `/usr/local/lib` directory for the library (on the Unix-like OS) which may be inaccessible from the `PATH` environment variable (e.g. can not be started as a regular command).

## Custom installation path

To install binary into the system globally available directory add the `--prefix` parameter to the command above as next:

```
# replace the /usr/bin path with our own if needed
# run from the project's build directory

sudo cmake --install . --prefix "/usr"
```

Examine the `PATH` environment variable to chose directory best suited for your current OS (execute `echo $PATH` in the terminal). Alternatively, any path may be specified.

## Documentation install

If project was configured to support the documentation install by the command which looks like next:

```
# inside the project build directory

cmake ../ -DENABLE_DOC_DOXYGEN=ON -DDOXYGEN_DO_INSTALL=ON
```

The installation command (for example, described in the [Default installation](#default-installation) section) will install the generated HTML documentation files into appropriate directories.