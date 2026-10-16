## Configuring the documentation install support

It's possible to enable support for the document installation by setting up the `ENABLE_DOC_DOXYGEN` and `DOXYGEN_DO_INSTALL` options to the `true` value during the project configure stage.

```
# inside the project root directory

meson setup build -DENABLE_DOC_DOXYGEN=true -DDOXYGEN_DO_INSTALL=true
```

The install step then copies the generated HTML directory into the `share/doc` directory of the install prefix (for example, the `/usr/local/share/doc/CppAppTemplate-html`). The `DOXYGEN_OUT_HTML_NAME` value of the `doc/meson.build` file configures the documentation html directory name (passed into the `Doxyfile`).
