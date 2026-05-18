## Enabling sanitizers

In order to enable the sanitizers to check application at the runtime, configure project with the command:

```
# inside the project root directory

meson setup build -DENABLE_SANITIZERS=true
```

For a general purpose sanitizers (`address`, `leak`, `undefined`). See the `meson/template-project-sanitizers/meson.build` Meson submodule file to examine the available list of the sanitizer compile and link flags.

Alternatively, enable the thread sanitizer with the command:

```
# inside the project root directory

meson setup build -DENABLE_SANITIZERS_THREADS=true
```

to check the possible data races of the newly introduced multithreaded application code.

Do not combine the `ENABLE_SANITIZERS` and `ENABLE_SANITIZERS_THREADS`. The Meson submodule reports a hard error if both are set since the `ThreadSanitizer` is incompatible with the `Address+Leak` sanitizers.

Any findings will be printed into the application' stdout/stderr after the build and run.
