## Enabling the flatpak package generation support

In order to enable the flatpak generation of the redistribution package on the template project configure it with enabled option `ENABLE_FLATPAK` (GNU/Linux and alike):

```
# inside the project root directory 

cmake -B build -S . -DENABLE_FLATPAK=ON
```

Which in order will enable the `flatpak` target.

The `flatpak-builder` compiles the project inside it's own sandbox, which carries no network access, while the Font Awesome enabler fetches it's checkout through the Internet. The generated manifest therefore lists the very same `TEMPLATE_APP_FONTAWESOME_GIT` repository and `TEMPLATE_APP_FONTAWESOME_GIT_TAG` tag among the module sources, so that the `flatpak-builder` downloads the checkout before the sandbox is entered, and hands it over to the sandboxed configure through the `TEMPLATE_APP_FONTAWESOME_DIR` option. Every other source of the icon set (an own repository mirror or an own tag) reaches the flatpak package the very same way: through those two cache variables.

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
flatpak run ua.org.kytok.template.CppAppTemplate
```
