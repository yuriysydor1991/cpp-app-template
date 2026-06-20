## Обов'язкові пакети Qt6

Для того щоб зробити доступними ресурси Qt6, необхідно скористатися командою яка виглядатиме наступним чином (ОС на базі GNU/Linux):

```
# багацько пакетів Qt6, що можуть знадобитись

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
  qml6-module-qtquick-timeline \
  qt6-location-dev qt6-positioning-dev \
  qml6-module-qtlocation qml6-module-qtpositioning
```

Пакети `qt6-location-dev`, `qt6-positioning-dev`, `qml6-module-qtlocation` і `qml6-module-qtpositioning` надають модулі [Qt Location](https://doc.qt.io/qt-6/qtlocation-index.html) та [Qt Positioning](https://doc.qt.io/qt-6/qtpositioning-index.html), що містять рідний QML-елемент [Map](https://doc.qt.io/qt-6/qml-qtlocation-map.html) (разом із вбудованим втулком геосервісів `osm` для мап OpenStreetMap), який використовується у цій гілці. Вони потребують Qt 6.5 або новішої версії, у якій модуль Qt Location було повернуто.
