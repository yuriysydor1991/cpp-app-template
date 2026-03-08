## Changing the project and executable name

Change the name of the project in the project's appropriate `meson.build` file by introducing a new value for the the `PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable which is located at `meson/template-project-dockerers/meson.build`. It is recommended to do so the executable will represent your new application name instead of templated default one - the `CppAppTemplate`.
