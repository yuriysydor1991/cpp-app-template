## Installing the library development files

An installed shared library serves two different audiences. Running a program
that is already linked against the library needs nothing but the versioned
binary the dynamic loader resolves through the SONAME. Building a *new* program
against the library additionally needs the development files: the public
headers, the CMake package integration files and the unversioned
`lib<name>.so` namelink that the `-l<name>` linker flag looks for.

Distributions split those two groups into separate packages - the runtime one
and the `-dev` / `-devel` one. The `LIB_INSTALL_DEV_FILES` option lets this
project install either the whole set or the runtime half alone.

| Option | Default | Effect |
|---|---|---|
| `-DLIB_INSTALL_DEV_FILES=ON` | `ON` | Installs the runtime library together with the development files |
| `-DLIB_INSTALL_DEV_FILES=OFF` | | Installs the runtime library only |

A runtime only installation:

```
# inside the project root directory

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DLIB_INSTALL_DEV_FILES=OFF
cmake --build build
cmake --install build --prefix /usr/local
```

What each mode installs for a `0.12.0` project named `CppAppTemplate`:

| Installed artefact | `ON` | `OFF` |
|---|---|---|
| `<prefix>/lib/libCppAppTemplate-0.so.0.12.0` - the library binary | yes | yes |
| `<prefix>/lib/libCppAppTemplate-0.so.0` - the SONAME symlink the loader resolves | yes | yes |
| `<prefix>/lib/libCppAppTemplate-0.so` - the namelink the linker resolves | yes | no |
| `<prefix>/include/CppAppTemplate-0/*.h` - the public headers | yes | no |
| `<prefix>/lib/cmake/CppAppTemplate-0/*.cmake` - the `find_package` integration | yes | no |
| the debug symbols, if the project installs any | yes | no |

The template installs no separate debug symbol files of its own - a `Debug`
build carries its debug info inside the library binary itself. The option is
the place to gate such an install rule should a derived project add one.

Turning the option off changes nothing about what is *built* - only the install
rules are dropped. The same build tree can therefore be installed both ways
without reconfiguring anything else.

The option is declared in [cmake/template-project-misc-variables-declare.cmake](/cmake/template-project-misc-variables-declare.cmake) and consumed by [src/lib/CMakeLists.txt](/src/lib/CMakeLists.txt) and [src/lib/facade/CMakeLists.txt](/src/lib/facade/CMakeLists.txt).

See also the [Customizing the installable library name segments](/doc/sections/en_US/5-project-build/compression/5-23-customizing-library-name-segments.md) section, which decides the `<NAME>` used by every artefact listed above.
