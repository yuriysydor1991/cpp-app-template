
# Installing

Execute available install commands from the project's build directory.

## Default installation

In order to install the built library together with its development files into the default `/usr/local` prefix, execute next command in the command line (GNU/Linux based):

```
# installs the library under the /usr/local/lib/ for example
# and the header include files under the /usr/local/include/CppAppTemplate-0.12

sudo cmake --install .
```

The library lands in the `<prefix>/${CMAKE_INSTALL_LIBDIR}` directory and its headers and CMake package files next to it, see the [Installing the library development files](/doc/sections/en_US/5-project-build/5-37-installing-the-library-development-files.md) section for the whole layout. A library is no command to start, so no `PATH` change is needed; a program linked against it finds it through the dynamic loader, which searches `/usr/local/lib` on most of the GNU/Linux distributions (run `sudo ldconfig` after the install to refresh its cache).

## Installation by the quick build scripts

The scripts of the [Quick build scripts](/doc/sections/en_US/5-project-build/5-36-quick-build-scripts.md) section perform the install step themselves when the `--install` parameter is given, so the whole configure, build and install cycle takes the single command:

```
# inside the project root directory

scripts/build/release.sh --install
```

The install step alone, against the already built `build/release` directory, is performed by its stage script:

```
# inside the project root directory

scripts/build/release-install.sh --install
```

Both of them install into the `/usr` prefix by the `sudo cmake --install` call, so the `sudo` password is asked for. Without the `--install` parameter the install step is skipped entirely and no password is ever asked.

## Custom installation path

To install the library under another prefix add the `--prefix` parameter to the command above as next:

```
# replace the /usr path with our own if needed
# run from the project's build directory

sudo cmake --install . --prefix "/usr"
```

The `/usr` prefix puts the library into the system library directory (e.g. `/usr/lib/x86_64-linux-gnu` on Debian and Ubuntu), which the dynamic loader always searches. Any other path may be specified too: pass it through the `CMAKE_PREFIX_PATH` variable to the downstream CMake projects and through the `LD_LIBRARY_PATH` variable (or an RPATH) to the programs linked against the library.

## Documentation install

If project was configured to support the documentation install by the command which looks like next:

```
# inside the project build directory

cmake ../ -DENABLE_DOC_DOXYGEN=ON -DDOXYGEN_DO_INSTALL=ON
```

The installation command (for example, described in the [Default installation](#default-installation) section) will install the generated HTML documentation files into appropriate directories.
