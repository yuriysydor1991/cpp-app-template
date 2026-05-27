## The Qt6 required packages

In order to be able to use the Qt6 resources install them with command that may look like next (GNU/Linux based OS):

```
# all the Qt6 required packages

sudo apt install -y qt6-base-dev qt6-base-dev-tools \
  qt6-declarative-dev qt6-tools-dev qt6-tools-dev-tools \
  qml6-module-qtquick qml6-module-qtqml-workerscript \
  qml6-module-qtquick-templates qml6-module-qtquick-window \
  qml6-module-qtquick-controls qml6-module-qtquick-layouts \
  qml6-module-qtquick-dialogs qml6-module-qtquick-virtualkeyboard \
  qml6-module-qtquick-localstorage qml6-module-qtquick-nativestyle \
  qml6-module-qtquick-particles qml6-module-qtquick-pdf \
  qml6-module-qtquick-scene2d qml6-module-qtquick-scene3d \
  qml6-module-qtquick-shapes qml6-module-qtquick-tooling \
  qml6-module-qtquick-timeline
```

The native D-Bus client used by this branch relies on the [QtDBus](https://doc.qt.io/qt-6/qtdbus-index.html) module (the CMake `Qt6::DBus` target), which is already part of the `qt6-base-dev` package listed above, so no extra build dependency is required. At run time the executable needs access to a running [D-Bus](https://en.wikipedia.org/wiki/D-Bus) **system** bus exposing the [systemd-hostnamed](https://www.freedesktop.org/software/systemd/man/latest/org.freedesktop.hostname1.html) (`org.freedesktop.hostname1`) service - a standard component of any systemd based GNU/Linux system. When the bus is not reachable the window still opens and shows the corresponding error instead of the system information.