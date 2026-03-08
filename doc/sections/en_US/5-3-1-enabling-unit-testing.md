### Enabling unit testing

To enable project unit test availability (for building and running) reconfigure it with enabled `ENABLE_UNIT_TESTS` variable as follows (GNU/Linux based):

```
# from the project root

meson setup build -DENABLE_UNIT_TESTS=true && meson compile -C build
```
