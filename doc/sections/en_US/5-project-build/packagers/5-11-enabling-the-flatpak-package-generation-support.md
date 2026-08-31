## Enabling the flatpak package generation support

In order to enable the flatpak generation of the redistribution package on the template project configure it with enabled option `ENABLE_FLATPAK` (GNU/Linux and alike):

```
# inside the project root directory 

cmake -B build -S . -DENABLE_FLATPAK=ON
```

Which in order will enable the `flatpak` target.

The `flatpak` target builds the project inside its own sandbox, so the gtkmm4 and the libadwaita development files are never taken from the host. Turn their enablers off whenever the host lacks them:

```
# inside the project root directory 

cmake -B build -S . -DENABLE_FLATPAK=ON -DENABLE_GTKMM4=OFF -DENABLE_LIBADWAITA=OFF
```

The [build-flatpak.sh](/scripts/build/build-flatpak.sh) script of the [Quick build scripts](/doc/sections/en_US/5-project-build/5-36-quick-build-scripts.md) section performs that very configure on its own.

And finally to generate the flatpak package run the `flatpak` target for the build:

```
# inside the project root directory 

cmake --build build --target flatpak
```

In case of the success target build, there will be created the flatpak file under the root build directory named, for example, the `CppAppTemplate-0.9.0-x86_64.flatpak`. In order to examine and/or change the flatpak generation target parameters visit the `cmake/template-project-flatpak-target.cmake` or `misc/packagers/flatpak/flatpak.conf.json.in ` files.

Refer to the flatpak documentation on how to install and run applications distributed from a flatpaks files. For the current template project's defaults the install and run command may look like this:

```
# to install (version may change)
# inside the project build directory
flatpak install --user CppAppTemplate-0.9.0-x86_64.flatpak

# to run the application
flatpak run ua.org.kytok.template.gtkmm4.CppAppTemplate
```
