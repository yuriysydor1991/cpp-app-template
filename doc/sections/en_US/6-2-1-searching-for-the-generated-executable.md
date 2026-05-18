### Searching for the generated executable

To find executable in the project build directory execute the `find` command:

```
find . -name 'CppAppTemplate'
```

The `CppAppTemplate` is a default executable name. Replace it with your custom one if you change the project name in the root `meson.build` file (the first positional argument to `project(...)`) - the executable name is derived from `meson.project_name()` inside `src/meson.build`.
