## Enabling the dynamic memory check target with valgrind

**Valgrind is currently not integrated in current flavor of the template project**

In order to make the `valgrind` target available for the execution, configure project with the enabled `ENABLE_VALGRIND` variable like:

```
# inside the project root directory 

meson setup builddir -DENABLE_VALGRIND=ON
```

To perform the dynamic memory check on the application build run next command:

```
# inside the project root directory

meson compile -C builddir valgrind
```

The `valgrind` target details may be examined and/or altered in the ~~`cmake/template-project-valgrind-target.cmake`~~ CMake submodule file.

**Warning! It will start application.** The dynamic memory check requires application to be started and go through the full cycle. Ensure that application execution will have a finite time.
