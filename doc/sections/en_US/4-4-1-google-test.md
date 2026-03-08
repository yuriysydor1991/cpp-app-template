### Google Test

Currently test samples are based on the GTest framework.

Of course, the project's `meson.build` files are probing the GTest only if tests are enabled by `ENABLE_UNIT_TESTS` Meson variable. System GTest probe may be turned OFF by setting appropriate value to the `GTEST_TRY_SYSTEM_PROBE` Meson variable.
