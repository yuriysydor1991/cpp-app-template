## Enabling the dynamic memory check target with valgrind

In order to make the `valgrind` target available for the execution, configure project with the enabled `ENABLE_VALGRIND` option:

```
# inside the project root directory

meson setup build -DENABLE_VALGRIND=true
```

To perform the dynamic memory check on the application build run the next command:

```
# inside the project root directory

meson compile -C build valgrind
```

The `valgrind` target details may be examined and/or altered in the `src/meson.build` file (the `ENABLE_VALGRIND` branch). It runs `valgrind --leak-check=full --error-exitcode=1 --show-leak-kinds=all` against the main project executable.

**Warning! It will start the application.** The dynamic memory check requires the application to be started and to go through the full cycle. Ensure that the application execution will have a finite time.

See [Optional for the memory check with Valgrind](/doc/sections/en_US/3-8-optional-for-the-memory-checkwith-Valgrind.md) for the `valgrind` install command.
