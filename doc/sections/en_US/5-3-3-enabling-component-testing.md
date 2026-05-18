### Enabling component testing

To enable project component tests (the `CTEST_app` executable under `src/app/tests/component/`) reconfigure the project with the `ENABLE_COMPONENT_TESTS` option set to `true` (GNU/Linux based):

```
# from the project root

meson setup build -DENABLE_COMPONENT_TESTS=true && meson compile -C build
```

Component tests are registered through Meson's `test()` function and are picked up by the `meson test -C build` command alongside the unit tests.
