### Google Test

Currently test samples are based on the GTest framework.

Of course, the project's `meson.build` files are probing the system GTest (the `gtest`, `gmock` and `gtest_main` pkg-config dependencies) only if tests are enabled by the `ENABLE_UNIT_TESTS` or `ENABLE_COMPONENT_TESTS` Meson options. See the [Optional for the tests](/doc/sections/en_US/3-3-optional-for-the-tests.md) section for the packages to install.
