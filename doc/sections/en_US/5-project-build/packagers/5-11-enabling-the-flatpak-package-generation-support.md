## Enabling the flatpak package generation support

In order to enable the flatpak generation of the redistribution package on the template project configure it with enabled option `ENABLE_FLATPAK` (GNU/Linux and alike):

```
# inside the project root directory 

cmake -B build -S . -DENABLE_FLATPAK=ON
```

Which in order will enable the `flatpak` target.

And finally to generate the flatpak package run the `flatpak` target for the build:

```
# inside the project root directory 

cmake --build build --target flatpak
```

In case of the success target build, there will be created the flatpak file under the root build directory named, for example, the `CppAppTemplate-0.9.0-x86_64-freedesktop-24.08.flatpak`. The name ends with the runtime the bundle runs on, the one of the `misc/packagers/flatpak/flatpak.conf.json.in` manifest (the `freedesktop-24.08` stands for its `org.freedesktop.Platform` `24.08`), since the GUI framework of the project picks the runtime. In order to examine and/or change the flatpak generation target parameters visit the `cmake/enablers/packagers/template-project-flatpak-target.cmake` or `misc/packagers/flatpak/flatpak.conf.json.in ` files.

Refer to the flatpak documentation on how to install and run applications distributed from a flatpaks files. For the current template project's defaults the install and run command may look like this:

```
# to install (version may change)
# inside the project build directory
flatpak install --user CppAppTemplate-0.9.0-x86_64-freedesktop-24.08.flatpak

# to run the application
flatpak run ua.org.kytok.template.wt4.CppAppTemplate --docroot "/app/share/Wt;/resources" --http-listen 127.0.0.1:8000 --accesslog CppAppTemplate-http-access.log
```

The `--docroot` value names the directory that holds the Wt `resources` one, while the `/resources` after the semicolon tells the Wt to serve the URLs under it as static files (the themes, the stylesheets and the images of the widgets).
