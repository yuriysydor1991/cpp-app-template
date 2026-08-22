## Installing the library development files

An installed shared library serves two different audiences. Running a program
that is already linked against the library needs nothing but the versioned
binary the dynamic loader resolves through the SONAME. Building a *new* program
against the library additionally needs the development files: the public
headers, the pkg-config file and the CMake package integration files.

Distributions split those two groups into separate packages - the runtime one
and the `-dev` / `-devel` one. The `LIB_INSTALL_DEV_FILES` option lets this
project install either the whole set or the runtime half alone.

| Option | Default | Effect |
|---|---|---|
| `-DLIB_INSTALL_DEV_FILES=true` | `true` | Installs the runtime library together with the development files |
| `-DLIB_INSTALL_DEV_FILES=false` | | Installs the runtime library only |

A runtime only installation:

```
# inside the project root directory

meson setup build --prefix /usr/local -DLIB_INSTALL_DEV_FILES=false
ninja -C build
meson install -C build
```

The option may also be flipped on an already configured build directory:

```
meson configure build -DLIB_INSTALL_DEV_FILES=false
meson install -C build
```

What each mode installs for a `0.12.0` project named `CppAppTemplate`:

| Installed artefact | `true` | `false` |
|---|---|---|
| `<libdir>/libCppAppTemplate-0.so.0.12.0` - the library binary | yes | yes |
| `<libdir>/libCppAppTemplate-0.so.0` - the SONAME symlink the loader resolves | yes | yes |
| `<prefix>/include/CppAppTemplate-0/*.h` - the public headers | yes | no |
| `<libdir>/pkgconfig/CppAppTemplate-0.pc` - the pkg-config file | yes | no |
| `<libdir>/cmake/CppAppTemplate-0/*.cmake` - the `find_package` integration | yes | no |
| the debug symbols, if the project installs any | yes | no |

The template installs no separate debug symbol files of its own - a `debug`
build carries its debug info inside the library binary itself. The option is
the place to gate such an install rule should a derived project add one. Meson
can also strip the installed binaries outright with `meson install --strip`,
which is an orthogonal knob and stays unaffected by this option.

One development file cannot be separated on Meson: the unversioned
`<libdir>/libCppAppTemplate-0.so` namelink, which only a linker looking for
`-lCppAppTemplate-0` needs. Meson installs the whole symlink chain as a single
unit of the `library()` target, so it is installed in both modes. The CMake
based branches of this template drop it through `NAMELINK_SKIP`.

Turning the option off changes nothing about what is *built* - only the install
rules are dropped. The same build tree can therefore be installed both ways.

The option is declared in [meson_options.txt](/meson_options.txt) and consumed by [src/lib/meson.build](/src/lib/meson.build).

See also the [Customizing the installable library name segments](/doc/sections/en_US/5-29-customizing-library-name-segments.md) section, which decides the name used by every artefact listed above.
