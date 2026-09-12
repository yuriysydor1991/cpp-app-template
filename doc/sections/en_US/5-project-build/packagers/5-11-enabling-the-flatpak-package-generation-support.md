## Enabling the flatpak package generation support

In order to enable the flatpak generation of the redistribution package on the template project configure it with enabled option `ENABLE_FLATPAK` (GNU/Linux and alike):

```
# inside the project root directory 

cmake -B build -S . -DENABLE_FLATPAK=ON
```

Which in order will enable the `flatpak` target.

The `flatpak-builder` compiles the project inside it's own sandbox, which carries no network access, while the Freesound enabler downloads it's sounds through the Internet. The generated manifest therefore hands the sounds directory the host configure has filled - the downloaded one, or the one the `TEMPLATE_APP_FREESOUND_AUDIO_DIR` variable has pointed it at - over to the module as a source of it's own, and the sandboxed configure reaches it through that very same variable. The packaged application is granted `--socket=pulseaudio`, so the sound player really reaches an audio device.

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
