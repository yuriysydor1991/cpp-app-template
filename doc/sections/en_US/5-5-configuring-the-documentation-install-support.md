## Configuring the documentation install support

It's possible to enable support for the document installation by setting up the `ENABLE_DOC_DOXYGEN` and `DOXYGEN_DO_INSTALL` variables to `ON` value during the project configure stage.

```
# inside the project root directory

meson setup build -DENABLE_DOC_DOXYGEN=true -DDOXYGEN_DO_INSTALL=true
```

The `DOXYGEN_OUT_HTML_NAME` Meson variable will configure the documentation html directory name (passed into the `Doxyfile`).
