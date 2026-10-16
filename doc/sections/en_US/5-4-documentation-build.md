## Documentation build

Currently it's possible to auto-generate the project documentation by the Doxygen tool from the available sources comments.

To enable Doxygen documentation Meson-target during the project configure process call a command that sets the `ENABLE_DOC_DOXYGEN` Meson variable to the `true` value (GNU/Linux based):

```
# inside the project root directory 

meson setup build -DENABLE_DOC_DOXYGEN=true
```

Which effectively will create a directory named `build` inside the project root directory and configures project to enable Doxygen documentation build.

Finally build the documentation by executing the command:

```
# inside the project root directory

meson compile -C build Doxygen-doc
```

Which in turn will generate the `build/doc/CppAppTemplate-html` directory inside the build tree which will contain the HTML-type documentation. In order to open and examine generated documentation open the `build/doc/CppAppTemplate-html/index.html` file. The `CppAppTemplate-html` directory name will change if the default project name is changed (the first positional argument to `project(...)` in the root `meson.build` file) or the `DOXYGEN_OUT_HTML_NAME` value of the `doc/meson.build` file which in turn sets the whole name for the directory.

The `doc/Doxyfile.meson.in` file contains all available Doxygen configuration parameters which may be changed in order to change the documentation output.
