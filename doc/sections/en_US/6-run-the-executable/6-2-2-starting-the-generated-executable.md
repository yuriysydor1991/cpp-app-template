### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appV8` branch executable initializes the V8 JavaScript engine and runs the JavaScript code of the Application, whose `console.log` call prints through the project logger with the JavaScript file name and line in place of the C++ ones:

```
2026-10-05 18:25:16 INF 140370990078208 main.js:1 : Hello, V8! Insert your JavaScript code here!
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
