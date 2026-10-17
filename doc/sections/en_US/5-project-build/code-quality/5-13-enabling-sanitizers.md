## Enabling sanitizers

In order to enable the sanitizers to check the library and its tests at the runtime, configure project with the command:

```
# inside the project root directory

cmake -S . -B build -DENABLE_SANITIZERS=ON -DENABLE_UNIT_TESTS=ON -DENABLE_COMPONENT_TESTS=ON
```

For a general purpose sanitizers. See the `cmake/compile-options/sanitizers/template-project-sanitizers.cmake` to examine available list of the sanitizers. The CI pipelines build the tests the very same way.

Alternatively, enable the threads sanitizers with the command:

```
# inside the project root directory

cmake -S . -B build -DENABLE_SANITIZERS_THREADS=ON -DENABLE_UNIT_TESTS=ON -DENABLE_COMPONENT_TESTS=ON
```

to check the possible data races of the newly introduced multithreaded library code.

Do not combine the `ENABLE_SANITIZERS` and `ENABLE_SANITIZERS_THREADS`.

Any findings will be printed into the stdout/stderr of the test (or of any other program linked against the instrumented library) once it runs, for example by the `ctest` command.
