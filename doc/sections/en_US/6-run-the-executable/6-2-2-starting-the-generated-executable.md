### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appGettext` branch executable greets in the language of the user, with the `--help` and the `--version` messages translated too, e.g. into the Ukrainian one under the installed `uk_UA.UTF-8` locale:

```
LANG=uk_UA.UTF-8 ./src/CppAppTemplate
Привіт, gettext! Вставте сюди свої перекладені повідомлення!
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
