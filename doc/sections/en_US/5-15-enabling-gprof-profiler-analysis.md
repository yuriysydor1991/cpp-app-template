## Enabling gprof profiler analysis

In order to perform the application profiler analysis with help of the `gprof` application enable it's support by setting the `true` value for the `ENABLE_GPROF` Meson option in a Debug build:

```
# Inside the source root directory

meson setup build --buildtype=debug -DENABLE_GPROF=true
```

After configuring project with support for the `gprof` profiling facility build the `gprof-analyze` target:

```
# Inside the source root directory

meson compile -C build gprof-analyze
```

Which will execute application inside the `src` directory of the build tree and starts the `gprof` profiling analyze tool for the `gmon.out` file generated there (for example `build/src/gmon.out`). The resulting analysis may be examined in the `gprof-analyze.txt` file next to it (for example `build/src/gprof-analyze.txt`).

Profiling with the `gprof` may be enabled only with `--buildtype=debug`. The Meson submodule `meson/enablers/profilers/template-project-profiler-gprof/meson.build` will emit a hard error if configured against any other build type.
