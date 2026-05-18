## Enabling gprof profiler analysis

In order to perform the application profiler analysis with help of the `gprof` application enable it's support by setting the `true` value for the `ENABLE_GPROF` Meson option in a Debug build:

```
# Inside the source root directory

meson setup build --buildtype=debug -DENABLE_GPROF=true
```

After configuring project with support for the `gprof` profiling facility build the `gprof-analyze` target:

```
# Inside the source root directory
# might not work !!!

meson compile -C build gprof-analyze
```

Which will execute application and starts the `gprof` profiling analyze tool for `gmon.out` generated file under the project's build directory (for example `build/src/gmon.out`). The resulting analysis may be examined by `gprof-analyze.txt` under the project's build directory.

Profiling with the `gprof` may be enabled only with `--buildtype=debug`. The Meson submodule `meson/template-project-profiler-gprof/meson.build` will emit a hard error if configured against any other build type.
