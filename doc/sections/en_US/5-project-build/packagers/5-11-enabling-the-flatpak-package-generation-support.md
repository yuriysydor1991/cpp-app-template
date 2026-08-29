## Enabling the flatpak package generation support

In order to enable the flatpak generation of the redistribution package on the template project configure it with enabled option `ENABLE_FLATPAK` (GNU/Linux and alike):

```
# inside the project root directory 

cmake -B build -S . -DENABLE_FLATPAK=ON -DENABLE_PACKAGERS_ONLY=ON
```

Which in order will enable the `flatpak` target.

The `flatpak-builder` compiles the project from its sources inside its own sandbox, so the `ENABLE_PACKAGERS_ONLY` option above keeps the project sources and the 3rd party libraries they link against out of the configure: the `flatpak` target is then available on a host that carries none of the project's build dependencies. Drop that option to configure the ordinary build targets next to the `flatpak` one.

And finally to generate the flatpak package run the `flatpak` target for the build:

```
# inside the project root directory 

cmake --build build --target flatpak
```

In case of the success target build, there will be created the flatpak file under the root build directory named, for example, the `CppAppTemplate-0.10.0.flatpak`. In order to examine and/or change the flatpak generation target parameters visit the `cmake/template-project-flatpak-target.cmake` or `misc/packagers/flatpak.conf.json.in ` files.

Refer to the flatpak documentation on how to install and run applications distributed from a flatpaks files. For the current template project's defaults the install and run command may look like this:

```
# to install (version may change)
# inside the project build directory
flatpak install --user CppAppTemplate-0.10.0.flatpak

# to run the application
flatpak run ua.org.kytok.template.firebird.CppAppTemplate
```
