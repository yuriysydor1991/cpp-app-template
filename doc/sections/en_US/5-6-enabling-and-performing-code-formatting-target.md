## Enabling and performing code formatting target

In order to make `clang-format` target available set the `ENABLE_CLANGFORMAT` variable value to `true` during the project configuration stage (GNU/Linux based):

```
# inside the project root directory 

meson setup build -DENABLE_CLANGFORMAT=true
```

To perform the whole project code format in accordance with available `misc/.clang-format` code formatter configuration execute next building command:

```
# inside the project root directory

meson compile -C build clang-format
```

The `clang-format` target details may be examined and/or altered in the `meson/template-project-clang-format-target/meson.build` Meson submodule file.
