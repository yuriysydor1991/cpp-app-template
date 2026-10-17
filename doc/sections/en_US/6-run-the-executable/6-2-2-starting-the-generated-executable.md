### Starting the generated executable

On macOS the executable is built as the `CppAppTemplate.app` bundle. Start it like any other macOS application, or run the executable inside the bundle to see its console output and to pass the command line arguments:

```
# from the build dir
open src/CppAppTemplate.app

# or
./src/CppAppTemplate.app/Contents/MacOS/CppAppTemplate --help
```

On the other platforms there is no bundle (the Cocoa window is macOS only and the executable just prints a notice), so if executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
