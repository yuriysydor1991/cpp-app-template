
# Installing

Execute available install commands from the project's build directory.

## Default installation

In order to install the built library together with its development files into the default `/usr/local` prefix execute next command in the command line (GNU/Linux based):

```
# installs the library under the /usr/local/lib/<multiarch> for example and
# the header include files under the /usr/local/include
# run from the project's root directory

sudo meson install -C build
```

A library is no command to start, so no `PATH` change is needed: a program linked against it finds it through the dynamic loader (run `sudo ldconfig` after the install to refresh its cache), and the downstream projects find it through its pkg-config and CMake package files.

## Custom installation path

The install location is the installation prefix chosen at the configure stage (the `/usr/local` by default). To install the library under another prefix, for example the `/usr` one, reconfigure the build directory with the `--prefix` parameter and install it as shown above:

```
# replace the /usr path with our own if needed
# run from the project's root directory

meson configure build --prefix=/usr
sudo meson install -C build
```

The `/usr` prefix puts the library into the system library directory, which the dynamic loader always searches. Any other path may be specified too: pass it through the `PKG_CONFIG_PATH` or the `CMAKE_PREFIX_PATH` variable to the downstream projects and through the `LD_LIBRARY_PATH` variable (or an RPATH) to the programs linked against the library.

The `--destdir` parameter of the `meson install` command does not replace the prefix, it prepends a staging directory to it (the `meson install -C build --destdir /tmp/stage` installs the executable into the `/tmp/stage/usr/local/bin` directory), which is what the packager targets use.

## Documentation install

If project was configured to support the documentation install by the command which looks like next:

```
# inside the project root directory

meson setup build -DENABLE_DOC_DOXYGEN=true -DDOXYGEN_DO_INSTALL=true
```

The installation command (for example, described in the [Default installation](#default-installation) section) will install the generated HTML documentation files into appropriate directories.
