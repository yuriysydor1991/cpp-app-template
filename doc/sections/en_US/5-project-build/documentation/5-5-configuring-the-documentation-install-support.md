## Configuring the documentation install support

It's possible to enable support for the document installation by setting up the `ENABLE_DOC_DOXYGEN` and `DOXYGEN_DO_INSTALL` variables to `ON` value during the project configure stage.

```
# inside the project root directory

cmake -B build -S . -DENABLE_DOC_DOXYGEN=ON -DDOXYGEN_DO_INSTALL=ON
```

With the install support enabled the `Doxygen-doc` target becomes a part of the default build, so the regular build and install commands generate and install the documentation without a separate documentation build:

```
# inside the project root directory

cmake --build build
cmake --install build
```

The HTML documentation directory is installed into the standard documentation directory of the install prefix (the `CMAKE_INSTALL_DOCDIR` one of the `GNUInstallDirs` CMake module), for example `/usr/local/share/doc/CppAppTemplate/CppAppTemplate-html`.

The `DOXYGEN_OUT_HTML_NAME` CMake variable will configure the documentation html directory name (passed into the `Doxyfile`).
