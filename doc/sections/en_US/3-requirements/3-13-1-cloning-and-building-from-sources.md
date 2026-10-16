### Cloning and building from sources

In order to install the [Wt C++ framework](https://www.webtoolkit.eu/wt) system wide out of its sources located at the [https://github.com/emweb/wt](https://github.com/emweb/wt) repository, clone the release the project is tested with and build it with next commands:

```
git clone --branch 4.11.4 --depth 1 https://github.com/emweb/wt.git
cmake -S wt -B wt/build -DCMAKE_BUILD_TYPE=Release -DENABLE_LIBWTDBO=OFF -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
cmake --build wt/build -j$(nproc)
sudo cmake --install wt/build
```

The project configure finds the installed Wt then (see the `WT4_TRY_SYSTEM_PROBE` option). The [Dockerfile.in](/misc/Dockerfiles/Dockerfile.in) builds the Wt the same way with the whole list of the disabled features. Refer to the Wt README.md and INSTALL files for the other build options.
