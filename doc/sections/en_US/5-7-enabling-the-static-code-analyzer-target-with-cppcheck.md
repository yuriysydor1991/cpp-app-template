## Enabling the static code analyzer target with cppcheck

In order to make the cppcheck target available for the execution, configure project with enabled `ENABLE_CPPCHECK` option:

```
# inside the project root directory 

meson setup builddir -DENABLE_CPPCHECK=true
```

And to perform the actual static code analysis by itself run the `cppcheck` target for the build:

```
# inside the project root directory

meson compile -C builddir cppcheck
```

The `cppcheck` target details may be examined and/or altered in the `meson/template-project-cppcheck-target/meson.build` Meson submodule file.
