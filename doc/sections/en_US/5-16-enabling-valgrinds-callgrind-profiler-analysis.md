## Enabling vagrind's callgrind profiler analysis

In order to perform the application profiler analysis with help of the `valgrind` application enable it's support by setting the `true` value for the `ENABLE_CALLGRIND` Meson option:

```
# Inside the source root directory

meson setup build --buildtype=debug -DENABLE_CALLGRIND=true
```

After configuring project with support for the `valgrind` profiling facility build the `callgrind` target:

```
# Inside the source root directory

meson compile -C build callgrind
```

After the application run the Valgrind's `callgrind` module will generate the profiler analysis files called `callgrind.out.*` under the project's build directory. The `build/src/callgrind.out.*` files may be examined with help of the UI application called `kcachegrind`:

```
# Inside the source root directory

kcachegrind build/src/callgrind.out.*
```

The `callgrind` target definition lives under the `src/meson.build` file (the `ENABLE_CALLGRIND` branch) - it depends on the main project executable and runs `valgrind --tool=callgrind` against it.
