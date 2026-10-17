## Required PLplot packages

In order to make available the PLplot development library install next packages into the system:

```
sudo apt install -y libplplot-dev
```

The example plot is shown by an interactive PLplot device: the `qtwidget` one of the `plplot-driver-qt` package or, when it's missing, the `xcairo` one of the `plplot-driver-cairo` package or the `xwin` one of the `plplot-driver-xwin` package. The library package carries no device driver, so install one of them too, otherwise the executable reports the missing driver and exits with a failure status:

```
sudo apt install -y plplot-driver-qt
```

Or compile it manually by commands that may look like next:

```
# clone the project into current directory
git clone https://git.code.sf.net/p/plplot/plplot plplot

# check out the commit the project pins (the TEMPLATE_APP_PLPLOT_GIT_TAG one)
git -C plplot checkout df0c00e11f2c289bb186e20b44651aa0184beb8b

# configure CMake project (the gnu17 C dialect keeps the pre-C23 PLplot
# configuration checks compilable by the modern C compilers)
cmake -B plplot-build -S plplot -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DENABLE_fortran=OFF -DCMAKE_C_FLAGS=-std=gnu17

# build all the project contents, the device drivers included whose development
# packages are found (e.g. the libx11-dev one for the xwin device)
cmake --build plplot-build -j$(nproc)

# install it into the system
sudo cmake --install plplot-build --prefix /usr
```

The `ENABLE_PLPLOT` CMake option (`ON` by default) makes the configure step use a system wide installed PLplot or fetch and build the `TEMPLATE_APP_PLPLOT_GIT_TAG` commit itself. Since the `src/plplot` example requires the library, turning the option `OFF` stops the configuration with an explanation, until the `add_subdirectory(plplot)` call of the `src/CMakeLists.txt` file is dropped together with the `src/plplot` subdirectory and the PLplot example of the `src/app/applications/Application.cpp` file.
