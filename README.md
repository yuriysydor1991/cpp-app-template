**Your neat C++ application template project**

# Goal of the template project

Project is designed to increase the speed of the application creation process at the project startup by providing templated application structure. So developer may just jump straight into implementing a particular application with no or minimum project start structure set up.

Helps you go beyond raw code — build a complete, ready-to-ship **software product** fast!

Enables rapid creation of a complete **software product** — not just raw code or a simple program.

**Just fork it and implement your application straight away!**

The template project **is not a framework** in traditional means so infrastructure implementation items may be altered to fit needs or even erased in case of redundancy.

See more at the [kytok.org.ua](http://www.kytok.org.ua/)

💵 Donate at [http://kytok.org.ua/page/pozertvy](http://kytok.org.ua/page/pozertvy)

# The template project flavors

Examine available branches to find your most applicable variant of the template or combine multiple branches by merging them to assemble the best suited template structure for your needs:

## Basic application infrastructure

- `main` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template)] just the clear `main` function and all available CMake integrations with no additional app infrastructure classes.
- `app` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/app), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/app)] with just general application related classes to generate a single binary executable.
- `applib` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/applib), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/applib)] for the application binary with additional separate library binary and header files (available for the installation) in order to provide library's code reusability across multiple applications.
- `lib` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/lib), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/lib)] for the library with the headers include files (and documentation) without target binary.
- `appMeson` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMeson), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMeson)] with just general application related classes to generate a single binary executable with the [Meson](https://mesonbuild.com/) build system.
- `applibMeson` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/applibMeson), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/applibMeson)] for the application binary with additional separate library binary and header files (available for the installation) in order to provide library's code reusability across multiple applications, built with the [Meson](https://mesonbuild.com/) build system and detectable by downstream Meson projects via `dependency()` (pkg-config) with optional CMake `find_package()` support.
- `libMeson` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/libMeson), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/libMeson)] for the library with the headers include files (and documentation) without target binary, built with the [Meson](https://mesonbuild.com/) build system and detectable by downstream Meson projects via `dependency()` (pkg-config) with optional CMake `find_package()` support.

## Logging messages

- `appLog4Cpp5` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appLog4Cpp5), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appLog4Cpp5)] the template infrastructure to fast start the application development with the [log4cpp](https://log4cpp.sourceforge.net/) extended logging library.
- `appBoostLog` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appBoostLog), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appBoostLog)] the template infrastructure to fast start the application development with the [Boost.Log](https://www.boost.org/doc/libs/latest/libs/log/doc/html/index.html) extended logging library.

## Windowing / GUI

- `appQt6` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6)] for the application general classes with additional defined structure for the [Qt6](https://www.qt.io/development/qt-framework/qt6) [QML](https://doc.qt.io/qt-6/qtqml-index.html) window application development.
- `appGtkmm3` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3)] for the application general classes with additional defined structure for the [Gtkmm](https://gtkmm.gnome.org/en/index.html)-3.0 with C++ window application development.
- `appGtkmm3Glade` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3Glade), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3Glade)] for the application general classes with additional defined structure for the C++ application development with [Gtkmm](https://gtkmm.gnome.org/en/index.html)-3.0 and [Glade](https://en.wikipedia.org/wiki/Glade_Interface_Designer) application with XML UI creation.
- `appGtkmm4` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4)] (**current**) for the application general classes with additional defined structure for the [Gtkmm-4](https://gtkmm.gnome.org/en/index.html) with C++ window application development.
- `appwxWidgets` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appwxWidgets), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appwxWidgets)] for the application general classes with additional defined structure for the [wxWidgets](https://www.wxwidgets.org/) cross-platform C++ window application development, provided through CMake FetchContent.

## 3D / OpenGL / Vulkan

- `appSDL3` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDL3), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSDL3)] with just general application related classes to generate a single binary executable with a [SDL3](https://wiki.libsdl.org/SDL3/FrontPage) library for the [OpenGL](https://www.opengl.org/) 3D development and more!
- `appSDL2` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDL2), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSDL2)] with just general application related classes to generate a single binary executable with a [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) library for the [OpenGL](https://www.opengl.org/) 3D development and more!
- `appGtkmm4GLArea` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4GLArea), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4GLArea)] with general application related classes to generate a single binary executable that embeds raw [OpenGL](https://www.opengl.org/) rendering inside a [Gtkmm-4](https://gtkmm.gnome.org/en/index.html) window with the native [Gtk::GLArea](https://docs.gtk.org/gtk4/class.GLArea.html) widget.
- `appQt6GLArea` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6GLArea), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6GLArea)] with general application related classes to generate a single binary executable that embeds raw [OpenGL](https://www.opengl.org/) rendering inside a [Qt6](https://www.qt.io/development/qt-framework/qt6) [QML](https://doc.qt.io/qt-6/qtqml-index.html) window with a [QQuickFramebufferObject](https://doc.qt.io/qt-6/qquickframebufferobject.html) scene-graph item.
- `appSFML` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSFML), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSFML)] with just general application related classes to generate a single binary executable with the [SFML](https://www.sfml-dev.org/) multimedia library (2D graphics, windowing, input and [OpenGL](https://www.opengl.org/) access) provided through the system package or the CMake FetchContent fallback.
- `appFreeGlut` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appFreeGlut), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appFreeGlut)] with just general application related classes to generate a single binary executable with a [FreeGlut](https://freeglut.sourceforge.net/) library for the [OpenGL](https://www.opengl.org/) 3D development.
- `appQt6Vulkan` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6Vulkan), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6Vulkan)] with general application related classes to generate a single binary executable that creates a [Vulkan](https://www.vulkan.org/) instance through the native [Qt6](https://www.qt.io/development/qt-framework/qt6) [QVulkanInstance](https://doc.qt.io/qt-6/qvulkaninstance.html) (`Qt6::Gui`), enumerates the available physical devices (GPUs), logs their properties via the application logger and shows a blank, black, Vulkan rendered window (a [QVulkanWindow](https://doc.qt.io/qt-6/qvulkanwindow.html) cleared to black) for the duration of the Qt event loop (the Qt6 framework counterpart of the app based appVulkan branch).
- `appGtkmm4Vulkan` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4Vulkan), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4Vulkan)] with general application related classes to generate a single binary executable that creates a [Vulkan](https://www.vulkan.org/) instance through the raw Vulkan loader, enumerates the available physical devices (GPUs) and logs their properties via the application logger, then renders a black frame with Vulkan into an off-screen image and shows it in a [Gtkmm-4](https://gtkmm.gnome.org/en/index.html) window through a Linux dma-buf ([Gdk::DmabufTexture](https://docs.gtk.org/gdk4/class.DmabufTexture.html)), since GTK4 has no native Vulkan rendering widget (the Gtkmm-4 counterpart of the app based appVulkan branch).

## Web / HTTP / Net

- `appWt4` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appWt4), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appWt4)] the template infrastructure to fast start Web application developing based on the [Wt C++](https://www.webtoolkit.eu/wt) full stack framework.
- `appBoostBeast` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appBoostBeast), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appBoostBeast)] the template infrastructure for the Web application fast start development with the [Boost Beast](https://www.boost.org/libs/beast) HTTP server.
- `appCURL` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appCURL), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appCURL)] the template infrastructure to fast start the application development with the [CURL](https://en.wikipedia.org/wiki/CURL) multi protocol client library (including the [HTTP](https://uk.wikipedia.org/wiki/HTTP)) to download data from the network.

## Database Management systems (DBMS) / SQL / NoSQL

- `appPgSQLxx` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appPgSQLxx), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appPgSQLxx)] the template infrastructure to fast start application development with the [PostgreSQL DBMS](https://en.wikipedia.org/wiki/PostgreSQL) usage.
- `appFirebird` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appFirebird), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appFirebird)] the template infrastructure to fast start application development with the [Firebird DBMS](https://firebirdsql.org/) usage through the native client library (fbclient).
- `appMySQLCppConn` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMySQLCppConn), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMySQLCppConn)] the template infrastructure to fast start application development with the [MySQL DBMS](https://en.wikipedia.org/wiki/MySQL) usage.
- `appSQLiteCpp3` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSQLiteCpp3), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSQLiteCpp3)] the template infrastructure to fast start application development with the [SQLite DBMS](https://en.wikipedia.org/wiki/SQLite) and [SQLiteCpp C++ bind](https://github.com/SRombauts/SQLiteCpp) usage.
- `appMongoDBCpp4` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMongoDBCpp4), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMongoDBCpp4)] the template infrastructure to fast start application development with the [MongoDB NoSQL DBMS](https://en.wikipedia.org/wiki/MongoDB) usage.

## Data Visualization / Plots / Graphs

- `appMatPlotxx` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMatPlotxx), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMatPlotxx)] the template infrastructure to fast start application development with the [MatPlot++](https://alandefreitas.github.io/matplotplusplus/) usage - a nice plot library with required [gnuplot](http://www.gnuplot.info/) application and [Qt6](https://www.qt.io/development/qt-framework/qt6).
- `appPLplot` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appPLplot), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appPLplot)] the template infrastructure to fast start application development with the [PLplot](https://plplot.sourceforge.net/) usage - a powerful plotting library used in scientific applications with a lot of windowing and language bindings and export capabilities (PNG, SVG, JPEG, GIF, PDF and more).
- `appQt6ChartView` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6ChartView), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6ChartView)] the template infrastructure to fast start data visualization and plotting right inside a [Qt6](https://www.qt.io/development/qt-framework/qt6) [QML](https://doc.qt.io/qt-6/qtqml-index.html) window with the native [ChartView](https://doc.qt.io/qt-6/qml-qtcharts-chartview.html) element from the [QtCharts](https://doc.qt.io/qt-6/qtcharts-index.html) module.

## Maps

- `appGtkmm4LeafLet` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4LeafLet), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4LeafLet)] with general application related classes to generate a single binary executable with usage of [Gtkmm-4](https://gtkmm.gnome.org/en/index.html) with [WebKitGtk](https://webkitgtk.org/) and [LeafLet](https://leafletjs.com/) maps.
- `appQt6LeafLet` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6LeafLet), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6LeafLet)] with general application related classes to generate a single binary executable with usage of [Qt6](https://www.qt.io/development/qt-framework/qt6) and [QML](https://doc.qt.io/qt-6/qtqml-index.html) with [WebView QML](https://doc.qt.io/qt-6/qml-qtwebview-webview.html) and [LeafLet](https://leafletjs.com/) maps.
- `appQt6QtLocation` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6QtLocation), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6QtLocation)] with general application related classes to generate a single binary executable that renders [OpenStreetMap](https://www.openstreetmap.org/) tiles natively inside a [Qt6](https://www.qt.io/development/qt-framework/qt6) [QML](https://doc.qt.io/qt-6/qtqml-index.html) window with the native [Map](https://doc.qt.io/qt-6/qml-qtlocation-map.html) element from the [Qt Location](https://doc.qt.io/qt-6/qtlocation-index.html) module (the native counterpart of the [WebView](https://doc.qt.io/qt-6/qml-qtwebview-webview.html) based appQt6LeafLet branch).

## Computer Vision / Image Processing

- `appOpenCV` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appOpenCV), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appOpenCV)] the template infrastructure to fast start application development with the [OpenCV](https://opencv.org/) computer vision library.

## System / DBus

- `appSDBusCxxClient` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDBusCxxClient), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSDBusCxxClient)] with just general application related classes to generate a single binary executable with the usage of [Kistler-Group's sdbus-c++](https://github.com/Kistler-Group/sdbus-cpp.git) library as a [DBus](https://en.wikipedia.org/wiki/D-Bus) services client.
- `appSDBusCxxServer` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDBusCxxServer), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSDBusCxxServer)] with just general application related classes to generate a single binary executable with the usage of [Kistler-Group's sdbus-c++](https://github.com/Kistler-Group/sdbus-cpp.git) library as a server on the [DBus](https://en.wikipedia.org/wiki/D-Bus).
- `appQt6QtDBusClient` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6QtDBusClient), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6QtDBusClient)] with general application related classes to generate a single binary executable that reads the general system information from [systemd-hostnamed](https://www.freedesktop.org/software/systemd/man/latest/org.freedesktop.hostname1.html) over the [DBus](https://en.wikipedia.org/wiki/D-Bus) with the native [Qt6](https://www.qt.io/development/qt-framework/qt6) [QtDBus](https://doc.qt.io/qt-6/qtdbus-index.html) module and shows it in the [QML](https://doc.qt.io/qt-6/qtqml-index.html) window (the Qt6 framework counterpart of the sdbus-c++ based appSDBusCxxClient branch).
- `appGtkmm4GDBusClient` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4GDBusClient), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4GDBusClient)] with general application related classes to generate a single binary executable that reads the general system information from [systemd-hostnamed](https://www.freedesktop.org/software/systemd/man/latest/org.freedesktop.hostname1.html) over the [DBus](https://en.wikipedia.org/wiki/D-Bus) with the native GLib [GDBus](https://docs.gtk.org/gio/) stack through the [Gtkmm-4](https://gtkmm.gnome.org/en/index.html)/giomm `Gio::DBus` API and logs it via the application logger (the gtkmm4 framework counterpart of the sdbus-c++ based appSDBusCxxClient branch).

## Data compression / decompression

- `appZlib` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appZlib), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appZlib)] with general application related classes to generate a single binary executable that wraps the [zlib](https://www.zlib.net/) compression library in a small controller exposing simple compress / uncompress methods (in memory and to / from gzip `.gz` files), and demonstrates a compress + uncompress round-trip from the Application.
- `appLZMA` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appLZMA), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appLZMA)] with general application related classes to generate a single binary executable that wraps the [liblzma](https://tukaani.org/xz/) (XZ Utils) compression library in a small controller exposing simple in-memory compress / uncompress methods over the `.xz` (LZMA2) container, and demonstrates a compress + uncompress round-trip from the Application.


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
    1. [Optional for the snap packager](/doc/sections/en_US/3-11-optional-for-snap-packager.md)
1. [Project structure](/doc/sections/en_US/4-project-structure.md)
    1. [Project diagrams](/doc/sections/en_US/4-0-project-diagrams.md)
    1. [Implement code straight away!](/doc/sections/en_US/4-1-implement-code-straight-away.md)
    1. [Resource embedding](/doc/sections/en_US/4-6-gtkmm4-resource-embedding.md)
    1. [Changing the project and executable name](/doc/sections/en_US/4-2-changing-the-project-and-executable-name.md)
    1. [Introducing custom command line parameters](/doc/sections/en_US/4-6-introduction-of-the-custom-command-line-parameters.md)
    1. [Implement your own IApplication descendants](/doc/sections/en_US/4-7-implementing-your-onw-IApplication-descendants.md)
    1. [Version tracking and other project parameters](/doc/sections/en_US/4-3-version-tracking-and-other-project-parameters.md)
    1. [Minimal possible versions](/doc/sections/en_US/4-6-minimal-possible-versions.md)
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
    1. Code quality & sanitizers
        1. [Enabling and performing code formatting target](/doc/sections/en_US/5-6-enabling-and-performing-code-formatting-target.md)
        1. [Enabling the static code analyzer target with cppcheck](/doc/sections/en_US/5-7-enabling-the-static-code-analyzer-target-with-cppcheck.md)
        1. [Enabling the static code analyzer with clang-tidy](/doc/sections/en_US/5-8-enabling-static-code-analyzer-with-clang-tidy.md)
        1. [Enabling the dynamic memory check target with valgrind](/doc/sections/en_US/5-9-enabling-the-dynamic-memory-check-target-with-valgrind.md)
        1. [Enabling sanitizers](/doc/sections/en_US/5-13-enabling-sanitizers.md)
    1. Profilers
        1. [Enabling gprof profiler analysis](/doc/sections/en_US/5-15-enabling-gprof-profiler-analysis.md)
        1. [Enabling vagrind's callgrind profiler analysis](/doc/sections/en_US/5-16-enabling-valgrinds-callgrind-profiler-analysis.md)
    1. Containers & CI
        1. [Enabling the Docker container build and run](/doc/sections/en_US/5-12-enabling-the-docker-container-build-and-run.md)
        1. [Enabling Jenkins pipeline inside Docker container](/doc/sections/en_US/5-17-enabling-Jenkins-pipeline-inside-Docker-container.md)
    1. Packagers
        1. [Enabling DEB package generation with cpack](/doc/sections/en_US/5-10-enabling-DEB-package-generation-with-cpack.md)
        1. [Enabling the flatpak package generation support](/doc/sections/en_US/5-11-enabling-the-flatpak-package-generation-support.md)
        1. [Enabling the snap packager](/doc/sections/en_US/5-19-enabling-the-snap-package-manager.md)
        1. [Enabling FreeBSD pkg package generation with cpack](/doc/sections/en_US/5-20-enabling-FreeBSD-pkg-package-generation-with-cpack.md)
        1. [Enabling WIX MSI package generation with cpack](/doc/sections/en_US/5-21-enabling-WIX-MSI-package-generation-with-cpack.md)
        1. [Enabling RPM package generation with cpack](/doc/sections/en_US/5-22-enabling-RPM-package-generation-with-cpack.md)
    1. Libraries
        1. [Enabling the libcurl](/doc/sections/en_US/5-14-enabling-libcurl.md)
        1. [Enabling the nlohmann json library](/doc/sections/en_US/5-18-enabling-the-nlohmann-json-library.md)
    1. Security / Cryptography
        1. [Enabling the OpenSSL library](/doc/sections/en_US/5-35-enabling-the-openssl-library.md)
    1. Compression
        1. [Enabling the zlib library](/doc/sections/en_US/5-23-enabling-the-zlib-library.md)
        1. [Enabling the liblzma library](/doc/sections/en_US/5-34-enabling-the-liblzma-library.md)
    1. Images
        1. [Enabling the libpng library](/doc/sections/en_US/5-24-enabling-the-libpng-library.md)
        1. [Enabling the libjpeg library](/doc/sections/en_US/5-25-enabling-the-libjpeg-library.md)
        1. [Enabling the libwebp library](/doc/sections/en_US/5-26-enabling-the-libwebp-library.md)
        1. [Enabling the lunasvg library (SVG)](/doc/sections/en_US/5-27-enabling-the-lunasvg-library.md)
        1. [Enabling the giflib library (GIF)](/doc/sections/en_US/5-28-enabling-the-giflib-library.md)
        1. [Enabling the libtiff library (TIFF)](/doc/sections/en_US/5-29-enabling-the-libtiff-library.md)
        1. [Enabling the OpenEXR library (EXR / HDR)](/doc/sections/en_US/5-30-enabling-the-openexr-library.md)
        1. [Enabling the OpenJPEG library (JPEG 2000)](/doc/sections/en_US/5-31-enabling-the-openjpeg-library.md)
        1. [Enabling the libavif library (AVIF)](/doc/sections/en_US/5-32-enabling-the-libavif-library.md)
        1. [Enabling the libheif library (HEIF/HEIC)](/doc/sections/en_US/5-33-enabling-the-libheif-library.md)
1. [Run the executable](/doc/sections/en_US/6-run-the-executable.md)
    1. [IDE run](/doc/sections/en_US/6-1-IDE-run.md)
    1. Command line run
        1. [Searching for the generated executable](/doc/sections/en_US/6-2-1-searching-for-the-generated-executable.md)
        1. [Starting the generated executable](/doc/sections/en_US/6-2-2-starting-the-generated-executable.md)
    1. Tests run
        1. [Run tests by the ctest](/doc/sections/en_US/6-3-1-run-tests-by-the-ctest.md)
        1. [Manual tests run](/doc/sections/en_US/6-3-2-manual-tests-run.md)
1. [Installing](/doc/sections/en_US/7-installing.md)
