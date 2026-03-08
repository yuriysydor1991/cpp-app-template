
# Installing

Execute available install commands from the project's build directory.

## Default installation

In order to install generated executable (as shown previous) file into your's system binary default folder execute next command in the command line (GNU/Linux based):

```
# installs generated binary under the /usr/local/bin/ for example
# run from the project's root directory

sudo meson install -C build
```

Usually it's the `/usr/local/bin/` directory (on the Unix-like OS) which may be inaccessible from the `PATH` environment variable (e.g. can not be started as a regular command).

## Custom installation path

To install binary into the system globally available directory add the `--destdir` parameter to the command above as next:

```
# replace the /usr path with our own if needed
# run from the project's build directory

sudo meson install -C build --destdir "/usr"
```

Examine the `PATH` environment variable to chose directory best suited for your current OS (execute `echo $PATH` in the terminal). Alternatively, any path may be specified.

## Documentation install

If project was configured to support the documentation install by the command which looks like next:

```
# inside the project root directory

meson setup build -DENABLE_DOC_DOXYGEN=true -DDOXYGEN_DO_INSTALL=true
```

The installation command (for example, described in the [Default installation](#default-installation) section) will install the generated HTML documentation files into appropriate directories.
