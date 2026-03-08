### Disabling system GTest probe 

To disable the system available GTest framework assets usage set appropriate value to the `GTEST_TRY_SYSTEM_PROBE` Meson variable by executing command like (GNU/Linux based):

```
# currently wont work !!!
# from the projects root directory

meson setup build -DENABLE_UNIT_TESTS=true -DGTEST_TRY_SYSTEM_PROBE=OFF && meson compile -C build
```
