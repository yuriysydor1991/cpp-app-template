## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
# the default dev tools
 sudo apt install -y git g++ cmake

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