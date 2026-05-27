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
  qml6-module-qtquick-timeline
```

Рідний D-Bus клієнт, що використовується у цій гілці, спирається на модуль [QtDBus](https://doc.qt.io/qt-6/qtdbus-index.html) (ціль CMake `Qt6::DBus`), який вже входить до пакета `qt6-base-dev` зазначеного вище, тож додаткової залежності для збирання не потрібно. Під час виконання програмі потрібен доступ до запущеної **системної** шини [D-Bus](https://uk.wikipedia.org/wiki/D-Bus) зі службою [systemd-hostnamed](https://www.freedesktop.org/software/systemd/man/latest/org.freedesktop.hostname1.html) (`org.freedesktop.hostname1`) - стандартного компонента будь-якої системи GNU/Linux на базі systemd. Якщо шина недоступна, вікно все одно відкривається і показує відповідну помилку замість системної інформації.
