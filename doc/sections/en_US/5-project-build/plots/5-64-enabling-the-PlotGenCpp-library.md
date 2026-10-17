## Enabling the PlotGenCpp library

The [PlotGenCpp](https://github.com/skhelladi/PlotGenCpp) library draws the example sine plot of this branch inside an [SFML](https://www.sfml-dev.org/) window. Both libraries are hard requirements of the branch, enabled by the `ENABLE_PLOTGENCPP` and the `ENABLE_SFML` CMake variables, which are `ON` by default. The CMake configure step stops with an error when any of them is set to `OFF`.

### The PlotGenCpp library

The library ships no CMake package, so it is always taken from it's git repository during the CMake configure step. Both the repository and it's tag are the `TEMPLATE_APP_PLOTGENCPP_GIT` and the `TEMPLATE_APP_PLOTGENCPP_GIT_TAG` CMake variables:

```
# Inside the source root directory

cmake -S . -B build -DTEMPLATE_APP_PLOTGENCPP_GIT_TAG=main
```

### The SFML library

The PlotGenCpp library and the project link the `sfml-graphics`, `sfml-window` and `sfml-system` libraries of the SFML 2 line. A system wide installed SFML 2 is used when it is found (the `libsfml-dev` package of the Ubuntu 24.04 and the Debian 13), and the `2.6.2` release is taken from the git repository otherwise, without it's audio and network modules. Both the repository and it's tag are the `TEMPLATE_APP_SFML_GIT` and the `TEMPLATE_APP_SFML_GIT_TAG` CMake variables.

The `libsfml-dev` package of the Ubuntu 26.04 carries the SFML 3, which the probe skips, so the fetched copy is built there. Building it needs the X11, OpenGL, FreeType and udev development packages:

```
sudo apt install -y libfreetype-dev libx11-dev libxrandr-dev libxcursor-dev libudev-dev libgl-dev
```

The [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) script installs those packages and builds and installs the SFML `2.6.2` release from source, so the probe finds a system wide SFML 2 there as well.

### Installing

The PlotGenCpp library installs itself next to the executable (together with it's `PlotterExamples` demo) and the fetched SFML installs into the `lib` directory of the installation prefix. On GNU/Linux the installed executable carries the `$ORIGIN` and the `$ORIGIN/../lib` RPATH to find both, so it starts from any installation prefix and from the generated packages.

### Running

The generated executable opens a window with the plot and returns once the window is closed or the Escape key is pressed:

```
./build/src/CppAppTemplate
```

The window and it's event loop belong to the `PlotGen::show()` method of the library, which never looks at the stop flag the application signal handlers raise, so close the window to end the program.

### The subsystem structure

The `plotgencppi::PlotGenCppController` class of the `src/plotgencpp` directory draws the plot, and the `app::Application` class drives it. The tests replace the library with the `src/plotgencpp/tests/mocks/plotgen/plotgen.h` stand-in, so they never open a window.
