### Enabling unit testing

To enable project unit test availability (for building and running) reconfigure it with enabled `ENABLE_UNIT_TESTS` variable as follows (GNU/Linux based):

```
# from the project root

cmake -B build -S . -DENABLE_UNIT_TESTS=ON && cmake --build build
```

The component tests (the `CTEST_*` ones, which exercise several classes together, e.g. the logger ones of every branch) are switched on by the separate `ENABLE_COMPONENT_TESTS` variable, so enable both to build every available test - the very same way the CI pipelines and the `Debug` quick build scripts do (GNU/Linux based):

```
# from the project root

cmake -B build -S . -DENABLE_UNIT_TESTS=ON -DENABLE_COMPONENT_TESTS=ON && cmake --build build
```

A branch without unit tests of its own (`main`, for example) has only the component tests, so its `ENABLE_UNIT_TESTS=ON` alone builds no test at all.
