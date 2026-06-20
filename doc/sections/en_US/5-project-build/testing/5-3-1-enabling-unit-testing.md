### Enabling unit testing

To enable project unit test availability (for building and running) reconfigure it with enabled `ENABLE_UNIT_TESTS` variable as follows (GNU/Linux based):

```
# from the project root

cmake -B build -S . -DENABLE_UNIT_TESTS=ON && cmake --build build
```
