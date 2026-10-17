## Required source for the MatPlot++ project

In order to be able to use the MatPlot++ library with the gnuplot application backend install it with:

```
sudo apt install -y gnuplot
```

Now clone and compile the MatPlot++ project with help of the next commands:

```
# clone the MatPlot++ project into local directory
git clone --branch v1.2.2 https://github.com/alandefreitas/matplotplusplus.git

# configure the project
cmake -B matplotplusplus-build -S matplotplusplus \
    -DMATPLOTPP_BUILD_EXAMPLES=OFF \
    -DMATPLOTPP_BUILD_SHARED_LIBS=ON \
    -DMATPLOTPP_BUILD_TESTS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON \
    -DCMAKE_INSTALL_PREFIX=/usr

# build the project with help of all CPUs available
cmake --build matplotplusplus-build -j$(nproc)

# install the MatPlot++ project into system
sudo cmake --install matplotplusplus-build --prefix /usr
```

The `ENABLE_MATPLOTCXX` CMake option (`ON` by default) makes the configure step use a system wide installed Matplot++ or fetch and build the `TEMPLATE_APP_MATPLOTCXX_GIT_TAG` release (`v1.2.2`) itself. Since the `src/matplotxx` example requires the library, turning the option `OFF` stops the configuration with an explanation, until the `add_subdirectory(matplotxx)` call of the `src/CMakeLists.txt` file is dropped together with the `src/matplotxx` subdirectory and the Matplot++ example of the `src/app/applications/Application.cpp` file.
