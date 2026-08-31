## Optional for the AppImage packager

The `appimage` target invokes the `appimagetool` command, which the GNU/Linux distributions rarely package. Download it from the [appimagetool releases](https://github.com/AppImage/appimagetool/releases) and put it into a directory of the `PATH` under the `appimagetool` name:

```
# replace the x86_64 with the architecture of the host
curl -L -o appimagetool \
  https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage

chmod +x appimagetool

sudo mv appimagetool /usr/local/bin/
```

The `appimagetool` is an [AppImage](https://appimage.org/) itself, so the `libfuse` library is required to start it, the same way it is required to start the produced package:

```
sudo apt install -y libfuse2t64
```

Without the library both the tool and the produced package are still startable with the `--appimage-extract-and-run` option, or with the `APPIMAGE_EXTRACT_AND_RUN=1` environment variable set.

Look for the details at the [Enabling the AppImage packager](/doc/sections/en_US/5-project-build/packagers/5-40-enabling-the-AppImage-packager.md).
