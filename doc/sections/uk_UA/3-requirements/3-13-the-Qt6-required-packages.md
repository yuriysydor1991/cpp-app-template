## Обов'язкові пакети Qt6

Для того щоб зробити доступними ресурси Qt6, необхідно скористатися командою яка виглядатиме наступним чином (ОС на базі GNU/Linux):

```
# обов'язкові пакети Qt6

sudo apt install -y qt6-base-dev qt6-base-dev-tools
```

Ця гілка є консольною програмою: вона використовує лише модулі [Qt6](https://www.qt.io/development/qt-framework/qt6) Core і [QtDBus](https://doc.qt.io/qt-6/qtdbus-index.html) (`Qt6::DBus`), які обидва входять до пакета `qt6-base-dev` вище - модулі Qt Quick/QML не потрібні. Під час виконання програмі потрібен доступ до запущеної **системної** шини [D-Bus](https://uk.wikipedia.org/wiki/D-Bus) зі службою [systemd-hostnamed](https://www.freedesktop.org/software/systemd/man/latest/org.freedesktop.hostname1.html) (`org.freedesktop.hostname1`) - стандартного компонента будь-якої системи GNU/Linux на базі systemd. Якщо шина недоступна, програма виводить у журнал відповідну помилку і завершується з ненульовим статусом; інакше вона виводить отриману системну інформацію через свої виклики логування LOGI.
