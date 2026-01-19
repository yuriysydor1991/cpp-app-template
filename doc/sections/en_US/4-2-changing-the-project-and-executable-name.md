## Changing the project and executable name

Change the name of the project in the project's root `CMakeLists.txt` file by introducing a new value for the the `PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable which is located at `cmake/template-project-misc-variables-declare.cmake`. It is recommended to do so the executable will represent your new application name instead of templated default one - the `CppAppTemplate`.
