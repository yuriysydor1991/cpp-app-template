**Your neat C++ application template project**

# Goal of the template project

Project is designed to increase the speed of the application creation process at the project startup by providing templated application structure. So developer may just jump straight into implementing a particular application with no or minimum project start structure set up.

Helps you go beyond raw code — build a complete, ready-to-ship **software product** fast!

Enables rapid creation of a complete **software product** — not just raw code or a simple program.

**Just fork it and implement application straight away!**

The template project **is not a framework** in traditional means so infrastructure implementation items may be altered to fit needs or even erased in case of redundancy.

See more at the [kytok.org.ua](http://www.kytok.org.ua/)

💵 Donate at [http://kytok.org.ua/page/pozertvy](http://kytok.org.ua/page/pozertvy)

# The template project flavors

Examine available branches to find your most applicable variant of the template or combine multiple branches by merging them to assemble the best suited template structure for your needs:

- `main` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template)] (**current**) just the clear `main` function and all available CMake integrations with no additional app infrastructure classes.
- `app` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/app), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/app)] with just general application related classes to generate a single binary executable.
- `applib` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/applib), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/applib)] for the application binary with additional separate library binary and header files (available for the installation) in order to provide library's code reusability across multiple applications.
- `lib` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/lib), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/lib)] for the library with the headers include files (and documentation) without target binary.
- `appQt6` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6)] for the application general classes with additional defined structure for the Qt6 QML window application development.
- `appGtkmm3` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3)] for the application general classes with additional defined structure for the Gtkmm-3.0 with C++ window application development.
- `appGtkmm3Glade` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3Glade), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3Glade)] for the application general classes with additional defined structure for the C++ application development with Gtkmm-3.0 and [Glade](https://en.wikipedia.org/wiki/Glade_Interface_Designer) application with XML UI creation.
- `appGtkmm4` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4)] for the application general classes with additional defined structure for the [Gtkmm-4](https://gtkmm.gnome.org/en/index.html) with C++ window application development.
- `appFreeGlut` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appFreeGlut), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appFreeGlut)] with just general application related classes to generate a single binary executable with a FreeGlut library for the OpenGL 3D development.
- `appSDL2` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDL2), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSDL2)] with just general application related classes to generate a single binary executable with a [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) library for the OpenGL 3D development and more!
- `appMeson` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMeson), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMeson)] with just general application related classes to generate a single binary executable with the [Meson](https://mesonbuild.com/) build system.
- `appWt4` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appWt4), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appWt4)] the template infrastructure to fast start Web application developing based on the [Wt C++](https://www.webtoolkit.eu/wt) full stack framework.
- `appPgSQLxx` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appPgSQLxx), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appPgSQLxx)] the template infrastructure to fast start application development with the [PostgreSQL DBMS](https://en.wikipedia.org/wiki/PostgreSQL) usage.
- `appBoostBeast` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appBoostBeast), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appBoostBeast)] the template infrastructure for the Web application fast start development with the [Boost Beast](https://www.boost.org/libs/beast) HTTP server.
- `appMySQLCppConn` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMySQLCppConn), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMySQLCppConn)] the template infrastructure to fast start application development with the [MySQL DBMS](https://en.wikipedia.org/wiki/MySQL) usage.
- `appSQLiteCpp3` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSQLiteCpp3), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSQLiteCpp3)] the template infrastructure to fast start application development with the [SQLite DBMS](https://en.wikipedia.org/wiki/SQLite) and [SQLiteCpp C++ bind](https://github.com/SRombauts/SQLiteCpp) usage.
- `appMongoDBCpp4` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMongoDBCpp4), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMongoDBCpp4)] the template infrastructure to fast start application development with the [MongoDB NoSQL DBMS](https://en.wikipedia.org/wiki/MongoDB) usage.
- `appLog4Cpp5` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appLog4Cpp5), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appLog4Cpp5)] the template infrastructure to fast start the application development with the [log4cpp](https://log4cpp.sourceforge.net/) extended logging library.
- `appBoostLog` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appBoostLog), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appBoostLog)] the template infrastructure to fast start the application development with the [Boost.Log](https://www.boost.org/doc/libs/latest/libs/log/doc/html/index.html) extended logging library.
- `appCURL` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appCURL), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appCURL)] the template infrastructure to fast start the application development with the [CURL](https://en.wikipedia.org/wiki/CURL) multi protocol client library (including the HTTP) to download data from the network.

Alter current `README.md` and a `CHANGELOG.md` files to match your implementation introduced into the destination new project. Examine the `doc` directory for possible translations of a current md document:
- `uk_UA` at [doc/README.uk_UA.md](doc/README.uk_UA.md)

# Documentation contents

**Document is under the refinement**

1. [Cloning the C++ template project](/doc/sections/en_US/1-cloning-the-cxx-template-project.md)
1. [Forking and replacing the origin](/doc/sections/en_US/2-forking-and-replacing-the-origin.md)
1. [Requirements](/doc/sections/en_US/3-requirements.md)
    1. [Required tools for the GNU/Linux based OS](/doc/sections/en_US/3-1-required-tools-for-the-GNU-Linux-based-OS.md)
    1. [Required tools for the MS Windows based OS](/doc/sections/en_US/3-2-required-tools-for-the-MS-Windows-based-OS.md)
    1. [Optional for the tests](/doc/sections/en_US/3-3-optional-for-the-tests.md)
    1. [Optional for the documentation](/doc/sections/en_US/3-4-optional-for-the-documentation.md)
    1. [Optional for the code formatting](/doc/sections/en_US/3-5-optional-for-the-code-formatting.md)
    1. [Optional for the code analyzer (cppcheck)](/doc/sections/en_US/3-6-optional-for-the-code-analyzer-cppcheck.md)
    1. [Optional for the code analyzer with clang-tidy](/doc/sections/en_US/3-7-optional-for-the-code-analyzer-with-clang-tidy.md)
    1. [Optional for the memory check with Valgrind](/doc/sections/en_US/3-8-optional-for-the-memory-checkwith-Valgrind.md)
    1. [Optional for the flatpak packager](/doc/sections/en_US/3-9-optional-for-the-flatpak-packager.md)
    1. [Optional for the Docker container runs](/doc/sections/en_US/3-10-optional-for-docker-container-runs.md)
1. [Project structure](/doc/sections/en_US/4-project-structure.md)
    1. [Implement code straight away!](/doc/sections/en_US/4-1-implement-code-straight-away.md)
    1. [Changing the project and executable name](/doc/sections/en_US/4-2-changing-the-project-and-executable-name.md)
    1. [Version tracking and other project parameters](/doc/sections/en_US/4-3-version-tracking-and-other-project-parameters.md)
    1. [Project tests](/doc/sections/en_US/4-4-project-tests.md)
        1. [Google Test](/doc/sections/en_US/4-4-1-google-test.md)
    1. [Extensions](/doc/sections/en_US/4-5-extensions.md)
1. [Project build](/doc/sections/en_US/5-project-build.md)
    1. [IDE build](/doc/sections/en_US/5-1-IDE-build.md)
    1. [Command line build](/doc/sections/en_US/5-2-command-line-build.md)
    1. Enabling testing
        1. [Enabling unit testing](/doc/sections/en_US/5-3-1-enabling-unit-testing.md)
        1. [Disabling system GTest probe](/doc/sections/en_US/5-3-2-disabling-system-GTest-probe.md)
    1. [Documentation build](/doc/sections/en_US/5-4-documentation-build.md)
    1. [Configuring the documentation install support](/doc/sections/en_US/5-5-configuring-the-documentation-install-support.md)
    1. [Enabling and performing code formatting target](/doc/sections/en_US/5-6-enabling-and-performing-code-formatting-target.md)
    1. [Enabling the static code analyzer target with cppcheck](/doc/sections/en_US/5-7-enabling-the-static-code-analyzer-target-with-cppcheck.md)
    1. [Enabling the static code analyzer with clang-tidy](/doc/sections/en_US/5-8-enabling-static-code-analyzer-with-clang-tidy.md)
    1. [Enabling the dynamic memory check target with valgrind](/doc/sections/en_US/5-9-enabling-the-dynamic-memory-check-target-with-valgrind.md)
    1. [Enabling DEB package generation with cpack](/doc/sections/en_US/5-10-enabling-DEB-package-generation-with-cpack.md)
    1. [Enabling the flatpak package generation support](/doc/sections/en_US/5-11-enabling-the-flatpak-package-generation-support.md)
    1. [Enabling the Docker container build and run](/doc/sections/en_US/5-12-enabling-the-docker-container-build-and-run.md)
    1. [Enabling sanitizers](/doc/sections/en_US/5-13-enabling-sanitizers.md)
    1. [Enabling the libcurl](/doc/sections/en_US/5-14-enabling-libcurl.md)
    1. [Enabling gprof profiler analysis](/doc/sections/en_US/5-15-enabling-gprof-profiler-analysis.md)
    1. [Enabling vagrind's callgrind profiler analysis](/doc/sections/en_US/5-16-enabling-valgrinds-callgrind-profiler-analysis.md)
    1. [Enabling Jenkins pipeline inside Docker container](/doc/sections/en_US/5-17-enabling-Jenkins-pipeline-inside-Docker-container.md)
1. [Run the executable](/doc/sections/en_US/6-run-the-executable.md)
    1. [IDE run](/doc/sections/en_US/6-1-IDE-run.md)
    1. Command line run
        1. [Searching for the generated executable](/doc/sections/en_US/6-2-1-searching-for-the-generated-executable.md)
        1. [Starting the generated executable](/doc/sections/en_US/6-2-2-starting-the-generated-executable.md)
    1. Tests run
        1. [Run tests by the ctest](/doc/sections/en_US/6-3-1-run-tests-by-the-ctest.md)
1. [Installing](/doc/sections/en_US/7-installing.md)
