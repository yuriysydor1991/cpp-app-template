### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).

The WebAssembly build of the `appWebAssembly` branch generates the `./src/CppAppTemplate.html` page instead, which the `emrun ./src/CppAppTemplate.html` command opens in the browser, as the [Building the WebAssembly binary for the browsers](/doc/sections/en_US/5-project-build/platforms/5-74-building-the-WebAssembly-binary-for-the-browsers.md) section tells.
