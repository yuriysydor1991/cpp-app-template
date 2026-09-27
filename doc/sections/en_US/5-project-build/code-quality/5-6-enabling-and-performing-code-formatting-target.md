## Enabling and performing code formatting target

In order to make `clang-format` target available set the `ENABLE_CLANGFORMAT` variable value to `ON` during the project configuration stage (GNU/Linux based):

```
# inside the project root directory

cmake -B build -S . -DENABLE_CLANGFORMAT=ON
```

To perform the whole project code format in accordance with available `misc/.clang-format` code formatter configuration execute next building command:

```
# inside the project root directory

cmake --build build --target clang-format
```

The `clang-format` target details may be examined and/or altered in the `cmake/template-project-clang-format-target.cmake` CMake submodule file.

The [debug-clang-format.sh](/scripts/build/debug-clang-format.sh) script of the [Quick build scripts](/doc/sections/en_US/5-project-build/5-36-quick-build-scripts.md) section configures the `build/debug` directory with the `ENABLE_CLANGFORMAT` option and builds the `clang-format` target there with a single command (GNU/Linux based):

```
# inside the project root directory

scripts/build/debug-clang-format.sh
```
