## Customizing the installable library name segments

The library name that downstream consumers see (the library binary, the
`include/<name>/` subdir for public headers, the pkg-config file and the CMake
package directory + imported-target namespace) is derived from three optional
Meson options. They let parallel installs of distinct versions of the library
coexist on the same host - e.g.
`include/CppAppTemplate-0.11.0-dev/` next to `include/CppAppTemplate-0/`.

| Option | Default | Effect |
|---|---|---|
| `-DLIB_INCLUDE_MINOR_IN_NAME=true` | `false` | Appends `.<minor>` to the library name |
| `-DLIB_INCLUDE_MICRO_IN_NAME=true` | `false` | Appends `.<micro>` (implies the minor flag) |
| `-DLIB_NAME_SUFFIX='-dev'` | `''` | Appends an arbitrary trailing tag |

Resulting library name examples for a `0.11.0` project:

| Configure flags | Library name |
|---|---|
| (none) | `CppAppTemplate-0` |
| `-DLIB_INCLUDE_MINOR_IN_NAME=true` | `CppAppTemplate-0.11` |
| `-DLIB_INCLUDE_MINOR_IN_NAME=true -DLIB_INCLUDE_MICRO_IN_NAME=true` | `CppAppTemplate-0.11.0` |
| `-DLIB_NAME_SUFFIX='-dev'` | `CppAppTemplate-0-dev` |
| `-DLIB_INCLUDE_MINOR_IN_NAME=true -DLIB_INCLUDE_MICRO_IN_NAME=true -DLIB_NAME_SUFFIX='-dev'` | `CppAppTemplate-0.11.0-dev` |

The same name is used consistently for every installed artefact:

- `<libdir>/lib<NAME>.so.<version>` (the shared library binary),
- `<prefix>/include/<NAME>/*.h` (the public headers install subdir),
- `<libdir>/pkgconfig/<NAME>.pc` (the pkg-config file - downstream Meson uses `dependency('<NAME>')`),
- `<libdir>/cmake/<NAME>/` + the `<NAME>::<NAME>` imported target (downstream CMake uses `find_package(<NAME> CONFIG)`).

The derivation lives in `meson/template-project-misc-variables-declare/meson.build`
and is exposed as the `PROJECT_LIBRARY_NAME` Meson variable that the rest of the
build system consumes.
