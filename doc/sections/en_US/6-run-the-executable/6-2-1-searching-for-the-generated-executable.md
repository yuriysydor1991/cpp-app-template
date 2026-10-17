### Searching for the generated executable

To find executable in the project build directory execute the `find` command:

```
find . -name 'CppAppTemplate'
```

On macOS it finds the executable inside the bundle, `./src/CppAppTemplate.app/Contents/MacOS/CppAppTemplate`.

The `CppAppTemplate` is a default executable name. Replace it with your custom one if you change the name of the project in the root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
