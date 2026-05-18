## Enabling the static code analyzer with clang-tidy

In order to enable the static code check for the each translation unit or each `*.cpp` file in the project with a `clang-tidy` application enable it during the project configuration stage by setting the `ENABLE_CLANG_TIDY` option value to `true` in the configuration command:

```
# inside the project root directory

meson setup build -DENABLE_CLANG_TIDY=true
```

And to perform the actual static code analysis by itself build the `clang-tidy` target and the `clang-tidy` command will perform a check on each compilation source:

```
# inside the project root directory

meson compile -C build clang-tidy
```

For more information about the `clang-tidy` examine the `meson/template-project-clang-tidy-target/meson.build` Meson submodule, the project's `misc/.clang-tidy` configuration file and the `clang-tidy` application documentation of a used version.

**Warning!** The `clang-tidy` static code analysis may dramatically increase the code compilation time.

See [Optional for the code analyzer with clang-tidy](/doc/sections/en_US/3-7-optional-for-the-code-analyzer-with-clang-tidy.md) for the `clang-tidy` install command.
