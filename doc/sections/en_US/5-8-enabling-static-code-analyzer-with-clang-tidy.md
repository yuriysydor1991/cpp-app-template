## Enabling the static code analyzer with clang-tidy

**The clang-tidy currently not integrated in current template branch**

In order to enable the static code check for the each translation unit or each `*.cpp` file in the project with a `clang-tidy` application enable it during the project configuration stage by setting the `ENABLE_CLANG_TIDY` variable value to `ON` in the configuration command:

```
# inside the project root directory

meson setup builddir -DENABLE_CLANG_TIDY=true
```

And to perform the actual static code analysis by itself build any target of interest and the `clang-tidy` command will perform check on each of the compilation target:

```
# inside the project root directory

meson compile -C builddir
```

For more information about the `clang-tidy` examine the ~~`cmake/template-project-clang-tidy-target.cmake`~~, `misc/.clang-tidy` files and the `clang-tidy` application documentation of a used version.

**Warning!** The `clang-tidy` static code analysis may dramatically increase the code compilation time.
