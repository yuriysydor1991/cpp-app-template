## The Qt6 required packages

In order to be able to use the Qt6 resources install them with command that may look like next (GNU/Linux based OS):

```
# all the Qt6 required packages

sudo apt install -y qt6-base-dev qt6-base-dev-tools
```

This branch is a console application: it uses only the [Qt6](https://www.qt.io/development/qt-framework/qt6) Core and [QtDBus](https://doc.qt.io/qt-6/qtdbus-index.html) (`Qt6::DBus`) modules, both of which ship with the `qt6-base-dev` package above - no Qt Quick/QML modules are required. At run time the executable needs access to a running [D-Bus](https://en.wikipedia.org/wiki/D-Bus) **system** bus exposing the [systemd-hostnamed](https://www.freedesktop.org/software/systemd/man/latest/org.freedesktop.hostname1.html) (`org.freedesktop.hostname1`) service - a standard component of any systemd based GNU/Linux system. When the bus is not reachable the executable logs the corresponding error and exits with a non-zero status; otherwise it logs the obtained system information through its LOGI logging calls.
