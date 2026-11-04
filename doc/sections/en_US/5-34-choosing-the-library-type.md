## Choosing the library type

The Meson built-in `default_library` option builds the project library as a shared, a static or both of them:

| Option | Default | Effect |
|---|---|---|
| `-Ddefault_library=shared` | `shared` | Builds the `lib<NAME>.so` shared library |
| `-Ddefault_library=static` | | Builds the `lib<NAME>.a` static library |
| `-Ddefault_library=both` | | Builds both of them, the library users get the shared one |

A static library build and install:

```
# inside the project root directory

meson setup build --prefix /usr/local -Ddefault_library=static
ninja -C build
meson install -C build
```

The pkg-config file and the CMake package serve both types the same way, see [Installing the library development files](/doc/sections/en_US/5-30-installing-the-library-development-files.md). What differs for the static library:

- The `<libdir>/lib<NAME>.a` is a development file as a whole, so the `-DLIB_INSTALL_DEV_FILES=false` runtime only installation installs no library at all. The `both` type installs it in both modes, the way it installs the `.so` namelink.
- The library hands the `TEMPLATE_LIB_STATIC` definition over to its users through the pkg-config file and the CMake package, which drops the MS Windows `__declspec` pair of the `TEMPLATE_LIB_API` macro in [LibraryAPI.h](/src/lib/facade/public/LibraryAPI.h). The `both` type builds its static library out of the shared library objects, so build the `static` one for the MS Windows.
- The third-party libraries the enablers add to the library (the libcurl, the libxml2, the nlohmann json and the OpenCV ones) become link dependencies of every library user. The pkg-config file lists them, while the CMake package does not - link them by hand there.
- The objects of a static library join the binary which links it, so the hidden symbol visibility no longer keeps the logging subsystem copies of two derived libraries apart - they silently share a single logger. Rename the `default_logger` namespace too, see [Renaming the library namespaces](/doc/sections/en_US/4-8-the-librarys-installable-include-header-files.md#renaming-the-library-namespaces).

The option is consumed by [meson/template-project-misc-variables-declare/meson.build](/meson/template-project-misc-variables-declare/meson.build) and [src/lib/meson.build](/src/lib/meson.build).
