## Enabling DEB package generation with cpack

In order to be able to generate the `deb` package file configure project to support the `cpack` command feature with a `ENABLE_DEB` variable enabled:

```
# inside the project root directory

cmake -B build -S . -DENABLE_DEB=ON
```

Next, build all available targets required for the `deb` package

```
# inside the project root directory

cmake --build build --target all
```

Finally, execute the `cpack` command inside the template project build directory:

```
# inside the project build directory

cpack
```

The package file should be generated inside the project build root directory. For example, if project name was't change and it's version is 0.8.0 so the package name may look like `CppAppTemplate-0.8.0-amd64.deb`.

The package name ends with the destination CPU architecture, the one of the package `Architecture` field as well. The `TEMPLATE_PROJECT_DEB_PACKAGE_ARCHITECTURE` cache variable holds it (default: the `dpkg --print-architecture` output, e.g. `amd64` or `arm64`), so override it when cross compiling the project or packaging it on a host without the `dpkg`.

In order to examine details of the `deb` package configuration visit the `cmake/template-project-deb-enabler.cmake` file.
