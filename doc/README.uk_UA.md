**Твій охайний шаблон для С++ програми**

# Ціль проекту-шаблону

Проект-шаблон призначений для пришвидшення процесу побудови програми на стадії започаткування проекту за допомогою готової початкової структури програми. Отож розробник може одразу перейти до реалізації конкретної програми з мінімальними затратами на базову структуру.

Полегшує вийти за рамки коду - створюй складні і готові до поставки **програмний продукти** швидко!

Дозволяє стрімке створення завершеного **програмного продукту** - на противагу звичайного куска коду чи простої програми.

**Створи форк і одразу реалізуй свою програму!**

Шаблонний проект **не являється фреймворком** у традиційних термінах отож інфраструктурні елементи можна змінювати за бажанням або видалити за непотреби.

Більше за посиланням [kytok.org.ua](http://www.kytok.org.ua/)

💵 Підтримай проект за посиланням [http://kytok.org.ua/page/pozertvy](http://kytok.org.ua/page/pozertvy)

# Спеціалізації шаблонного проекту

Переглянь доступні гілки у репозиторії проекту-шаблону і використай найбільш підходящу спеціалізацію або комбінуй декілька гілок щоб створити необхідну структуру шаблону:

## Базова структура програми

- гілка `main` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template)] один файл з функцією `main` і з усіма можливими інтеграціями для генерації одного бінарного виконуваного файлу.
- гілка `app` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/app), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/app)] (**поточна**) яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу.
- гілка `applib` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/applib), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/applib)] яка складається з класів банарного виконуваного файлу з додатковими інфраструктурними класами для генерації підключаємої бібліотеки і заголовкових файлів (доступні для встановлення), що призначені для поширення коду бібліотеки для повторного перевикористання іншими бінарнами файлами.
- гілка `lib` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/lib), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/lib)] і яка призначена для предоставляння початкової інфраструктури для реалізації бібліотеки разом з заголовковими підключаємими файлами і документацією за необхідності.
- гілка `appMeson` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMeson), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMeson)] яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу разом з системою побудови [Meson](https://mesonbuild.com/).
- гілка `applibMeson` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/applibMeson), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/applibMeson)] - шаблон застосунку з виконуваним файлом та додатковою окремою бібліотекою з заголовковими підключаємими файлами (доступними для встановлення) для повторного використання коду бібліотеки в кількох застосунках, побудований системою [Meson](https://mesonbuild.com/), знаходиться проектами-споживачами на Meson через `dependency()` (pkg-config) з опціональною підтримкою CMake `find_package()`.
- гілка `libMeson` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/libMeson), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/libMeson)] - шаблон бібліотеки з заголовковими підключаємими файлами і документацією, побудованою системою [Meson](https://mesonbuild.com/), знаходиться проектами-споживачами на Meson через `dependency()` (pkg-config) з опціональною підтримкою CMake `find_package()`.

## Логування

- гілка `appLog4Cpp5` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appLog4Cpp5), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appLog4Cpp5)] котра містить інфраструктуру для швидкого старту розробки застосунку з використанням багатофункціональної бібліотеки логування повідомлень [log4cpp](https://log4cpp.sourceforge.net/)
- гілка `appBoostLog` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appBoostLog), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appBoostLog)] котра містить інфраструктуру для швидкого старту розробки застосунку з використанням бібліотеки логування повідомлень [Boost.Log](https://www.boost.org/doc/libs/latest/libs/log/doc/html/index.html)

## Віконні системи / GUI

- гілка `appQt6` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6)] яка містить загальні класи для генерації бінарного виконуваного файлу разом з структурою заданою для розробки віконної програми на базі [Qt6](https://www.qt.io/development/qt-framework/qt6) разом з [QML](https://doc.qt.io/qt-6/qtqml-index.html).
- гілка `appGtkmm3` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3)] яка містить загальні класи для генерації бінарного виконуваного файлу разом з структурою заданою для розробки віконної програми на базі [Gtkmm](https://gtkmm.gnome.org/en/index.html)-3.0 з C++.
- гілка `appGtkmm3Glade` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3Glade), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3Glade)] яка містить загальні класи для генерації бінарного виконуваного файлу разом з структурою заданою для розробки віконної програми на базі C++ з [Gtkmm](https://gtkmm.gnome.org/en/index.html)-3.0 і [Glade](https://en.wikipedia.org/wiki/Glade_Interface_Designer) - програми для створення візульних інтерфейсів.
- гілка `appGtkmm4` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4)] яка містить загальні класи для генерації бінарного виконуваного файлу разом з структурою заданою для розробки віконної програми на базі [Gtkmm-4](https://gtkmm.gnome.org/en/index.html) з C++.
- гілка `appwxWidgets` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appwxWidgets), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appwxWidgets)] яка містить загальні класи для генерації бінарного виконуваного файлу разом з структурою заданою для розробки кросплатформної віконної програми на базі [wxWidgets](https://www.wxwidgets.org/) з C++, що надається через CMake FetchContent.

## 3D / OpenGL

- гілка `appSDL3` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDL3), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSDL3)] - яка містить загальні класи для генераці одинарного бінарного виконуваного файлу разом з початковою інфраструктурою для розробки у [OpenGL](https://www.opengl.org/) 3D разом з [SDL3](https://wiki.libsdl.org/SDL3/FrontPage) і набагато більше!
- гілка `appSDL2` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDL2), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSDL2)] яка містить загальні класи для генераці одинарного бінарного виконуваного файлу разом з початковою інфраструктурою для розробки у [OpenGL](https://www.opengl.org/) 3D разом з [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) і набагато більше!
- гілка `appGtkmm4GLArea` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4GLArea), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4GLArea)] яка містить загальні класи для генерації одинарного бінарного виконуваного файлу, що вбудовує рендеринг [OpenGL](https://www.opengl.org/) безпосередньо у вікно [Gtkmm-4](https://gtkmm.gnome.org/en/index.html) за допомогою нативного віджета [Gtk::GLArea](https://docs.gtk.org/gtk4/class.GLArea.html).
- гілка `appQt6GLArea` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6GLArea), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6GLArea)] яка містить загальні класи для генерації одинарного бінарного виконуваного файлу, що вбудовує рендеринг [OpenGL](https://www.opengl.org/) безпосередньо у вікно [Qt6](https://www.qt.io/development/qt-framework/qt6) [QML](https://doc.qt.io/qt-6/qtqml-index.html) за допомогою елемента сцен-графа [QQuickFramebufferObject](https://doc.qt.io/qt-6/qquickframebufferobject.html).
- гілка `appSFML` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSFML), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSFML)] яка містить загальні класи для генераці одинарного бінарного виконуваного файлу разом з початковою інфраструктурою на базі мультимедійної бібліотеки [SFML](https://www.sfml-dev.org/) (2D графіка, вікна, ввід та доступ до [OpenGL](https://www.opengl.org/)), яка надається системним пакетом або резервним механізмом CMake FetchContent.
- гілка `appFreeGlut` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appFreeGlut), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appFreeGlut)] яка містить загальні класи для генераці одинарного бінарного виконуваного файлу разом з початковою інфраструктурою для розробки у [OpenGL](https://www.opengl.org/) 3D разом з [FreeGlut](https://freeglut.sourceforge.net/).

## Web / HTTP / Мережа

- гілка `appWt4` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appWt4), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appWt4)] шаблон з інфраструктурою для швидкого старту реалізації Web-програми на основі [Wt C++](https://www.webtoolkit.eu/wt) фулстек фреймворку.
- гілка `appBoostBeast` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appBoostBeast), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appBoostBeast)] котра містить інфраструктуру для швидкого старту розробки Web-програми з використанням швидкого HTTP сервера [Beast](https://www.boost.org/libs/beast) від Boost.
- гілка `appCURL` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appCURL), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appCURL)] котра містить інфраструктуру для швидкого старту розробки застосунку з використанням бібліотеки-клієнта [CURL](https://en.wikipedia.org/wiki/CURL) для завантажень даних з мережі і яка підтримує багато протоколів (включаючи HTTP).

## Системи керування базами даних (СУБД) / SQL / NoSQL

- гілка `appPgSQLxx` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appPgSQLxx), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appPgSQLxx)] котра містить інфраструктуру для швидкого старту розробки застосунку з використанням СУБД [PostgreSQL](https://en.wikipedia.org/wiki/PostgreSQL)
- гілка `appMySQLCppConn` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMySQLCppConn), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMySQLCppConn)] котра містить інфраструктуру для швидкого старту розробки застосунку з використанням СУБД [MySQL](https://uk.wikipedia.org/wiki/MySQL)
- гілка `appSQLiteCpp3` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSQLiteCpp3), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSQLiteCpp3)] котра містить інфраструктуру для швидкого старту розробки застосунку з використанням СУБД [SQLite](https://en.wikipedia.org/wiki/SQLite) через бібліотеку [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp)
- гілка `appMongoDBCpp4` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMongoDBCpp4), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMongoDBCpp4)] котра містить інфраструктуру для швидкого старту розробки застосунку з використанням NoSQL СУБД [MongoDB](https://en.wikipedia.org/wiki/MongoDB)


## Візуалізація Даних / Графіки / Діаграми

- гілка `appMatPlotxx` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appMatPlotxx), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appMatPlotxx)] котра містить інфраструктуру для швидкого старту розробки застосунку з використанням [MatPlot++](https://alandefreitas.github.io/matplotplusplus/) - бібліотека для малювання графіків на основі прогарми [gnuplot](http://www.gnuplot.info/) і [Qt6](https://www.qt.io/development/qt-framework/qt6).
- гілка `appPLplot` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appPLplot), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appPLplot)] котра містить інфраструктуру для швидкого старту розробки застосунку з використанням [PLplot](https://plplot.sourceforge.net/) - потужної бібліотеки генерації графіків котра використовується у наукових програмах з багатьма інтерфейсами для різних віконних систем і мов програмування, і можливостями експорту у найпопулярніші формати зображень (PNG, SVG, JPEG, GIF, PDF і інші).
- гілка `appQt6ChartView` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6ChartView), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6ChartView)] котра містить інфраструктуру для швидкого старту візуалізації даних і малювання графіків безпосередньо у вікні [Qt6](https://www.qt.io/development/qt-framework/qt6) [QML](https://doc.qt.io/qt-6/qtqml-index.html) за допомогою вбудованого елемента [ChartView](https://doc.qt.io/qt-6/qml-qtcharts-chartview.html) з модуля [QtCharts](https://doc.qt.io/qt-6/qtcharts-index.html).

## Карти

- гілка `appGtkmm4LeafLet` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4LeafLet), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4LeafLet)] яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу з використанням [Gtkmm-4](https://gtkmm.gnome.org/en/index.html) з [WebKitGtk](https://webkitgtk.org/) і картами [LeafLet](https://leafletjs.com/)
- гілка `appQt6LeafLet` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6LeafLet), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6LeafLet)] яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу разом з [Qt6](https://www.qt.io/development/qt-framework/qt6)/[QML](https://doc.qt.io/qt-6/qtqml-index.html) і [WebView QML](https://doc.qt.io/qt-6/qml-qtwebview-webview.html) а також картами [LeafLet](https://leafletjs.com/)
- гілка `appQt6QtLocation` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6QtLocation), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6QtLocation)] яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу що відображає мапу [OpenStreetMap](https://www.openstreetmap.org/) рідними засобами безпосередньо у вікні [Qt6](https://www.qt.io/development/qt-framework/qt6)/[QML](https://doc.qt.io/qt-6/qtqml-index.html) за допомогою елемента [Map](https://doc.qt.io/qt-6/qml-qtlocation-map.html) з модуля [Qt Location](https://doc.qt.io/qt-6/qtlocation-index.html) (рідний відповідник гілки appQt6LeafLet на основі [WebView](https://doc.qt.io/qt-6/qml-qtwebview-webview.html)).

## Компʼютерний зір / Обробка зображень

- гілка `appOpenCV` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appOpenCV), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appOpenCV)] котра містить інфраструктуру для швидкого старту розробки застосунку з використанням бібліотеки компʼютерного зору [OpenCV](https://opencv.org/).

## System / DBus

- `appSDBusCxxClient` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDBusCxxClient), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSDBusCxxClient)] яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу з використанням [Kistler-Group's sdbus-c++](https://github.com/Kistler-Group/sdbus-cpp.git) бібліотеки для побудови клієнта сервісів розміщених на шині [DBus](https://uk.wikipedia.org/wiki/D-Bus)
- `appSDBusCxxServer` branch at [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDBusCxxServer), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appSDBusCxxServer)] яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу з використанням [Kistler-Group's sdbus-c++](https://github.com/Kistler-Group/sdbus-cpp.git) бібліотеки для побудови сервера на шині [DBus](https://uk.wikipedia.org/wiki/D-Bus).
- гілка `appQt6QtDBusClient` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6QtDBusClient), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appQt6QtDBusClient)] яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу що зчитує загальну системну інформацію зі служби [systemd-hostnamed](https://www.freedesktop.org/software/systemd/man/latest/org.freedesktop.hostname1.html) через шину [DBus](https://uk.wikipedia.org/wiki/D-Bus) за допомогою рідного модуля [Qt6](https://www.qt.io/development/qt-framework/qt6) [QtDBus](https://doc.qt.io/qt-6/qtdbus-index.html) і відображає її у вікні [QML](https://doc.qt.io/qt-6/qtqml-index.html) (відповідник гілки appSDBusCxxClient на основі sdbus-c++ для фреймворку Qt6).
- гілка `appGtkmm4GDBusClient` розміщена на [[GitHub](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4GDBusClient), [GitLab](https://gitlab.com/yuriysydor1991/cpp-app-template/tree/appGtkmm4GDBusClient)] яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу що зчитує загальну системну інформацію зі служби [systemd-hostnamed](https://www.freedesktop.org/software/systemd/man/latest/org.freedesktop.hostname1.html) через шину [DBus](https://uk.wikipedia.org/wiki/D-Bus) за допомогою рідного стеку GLib [GDBus](https://docs.gtk.org/gio/) через [Gtkmm-4](https://gtkmm.gnome.org/en/index.html)/giomm `Gio::DBus` і виводить її у журнал застосунку (відповідник гілки appSDBusCxxClient на основі sdbus-c++ для фреймворку gtkmm4).


Редагуй поточний файл `README.md` і `CHANGELOG.md` щоб документація відповідала впровадженому коду. Для перекладів даного файлу `README.md`:
- `uk_UA` за відносною адресою doc/README.uk_UA.md

# Зміст документації

**Даний документ у процесі покращення**

1. [Клонування С++ проекту-шаблону](/doc/sections/uk_UA/1-cloning-the-cxx-template-project.md)
1. [Створення форку і заміна оригінального репозиторію](/doc/sections/uk_UA/2-forking-and-replacing-the-origin.md)
1. [Вимоги](/doc/sections/uk_UA/3-requirements.md)
    1. [Обов'язкові інструменти для ОС на базі GNU/Лінукс](/doc/sections/uk_UA/3-1-required-tools-for-the-GNU-Linux-based-OS.md)
    1. [Обов'язкові інструменти для ОС на базі MS Windows](/doc/sections/uk_UA/3-2-required-tools-for-the-MS-Windows-based-OS.md)
    1. [Необов'язкові пакети для тестів](/doc/sections/uk_UA/3-3-optional-for-the-tests.md)
    1. [Необов'язкові пакети для створення документації](/doc/sections/uk_UA/3-4-optional-for-the-documentation.md)
    1. [Необов'язкові пакети для форматування коду](/doc/sections/uk_UA/3-5-optional-for-the-code-formatting.md)
    1. [Необов'язкові пакети для статичного аналізатора коду cppcheck](/doc/sections/uk_UA/3-6-optional-for-the-code-analyzer-cppcheck.md)
    1. [Необов'язкові пакети для статичного аналізатора коду clang-tidy](/doc/sections/uk_UA/3-7-optional-for-the-code-analyzer-with-clang-tidy.md)
    1. [Необов'язкові пакет для перевірки використання пам'яті за допомогю Valgrind](/doc/sections/uk_UA/3-8-optional-for-the-memory-checkwith-Valgrind.md)
    1. [Необов'язковий програми для генерації пакету flatpak](/doc/sections/uk_UA/3-9-optional-for-the-flatpak-packager.md)
    1. [Необов'язкові пакети для запуску контейнера Docker](/doc/sections/uk_UA/3-10-optional-for-docker-container-runs.md)
    1. [Необов'язкові пакети для snap пакувальника](/doc/sections/uk_UA/3-11-optional-for-snap-packager.md)
1. [Структура проекту](/doc/sections/uk_UA/4-project-structure.md)
    1. [Діаграми проекту](/doc/sections/uk_UA/4-0-project-diagrams.md)
    1. [Реалізуй код одразу!](/doc/sections/uk_UA/4-1-implement-code-straight-away.md)
    1. [Зміна назви проекту і головного виконуваного файлу](/doc/sections/uk_UA/4-2-changing-the-project-and-executable-name.md)
    1. [Впровадження нових параметрів командного рядка](/doc/sections/uk_UA/4-6-introduction-of-the-custom-command-line-parameters.md)
    1. [Реалізація власних нащадків IApplication](/doc/sections/uk_UA/4-7-implementing-your-onw-IApplication-descendants.md)
    1. [Версіювання і інші параметри проекту](/doc/sections/uk_UA/4-3-version-tracking-and-other-project-parameters.md)
    1. [Мінімально можливі версії](/doc/sections/uk_UA/4-6-minimal-possible-versions.md)
    1. [Тести проекту](/doc/sections/uk_UA/4-4-project-tests.md)
        1. [Фреймворк тестів Google Test](/doc/sections/uk_UA/4-4-1-google-test.md)
    1. [Розширення](/doc/sections/uk_UA/4-5-extensions.md)
1. [Побудова проекту](/doc/sections/uk_UA/5-project-build.md)
    1. [Побудова за допомогою IDE](/doc/sections/uk_UA/5-1-IDE-build.md)
    1. [Побудова проекту-шаблону через командний рядок](/doc/sections/uk_UA/5-2-command-line-build.md)
    1. Вмикання тестів
        1. [Вмикання юніт-тестів](/doc/sections/uk_UA/5-3-1-enabling-unit-testing.md)
        1. [Запобігання використання GTest з ОС](/doc/sections/uk_UA/5-3-2-disabling-system-GTest-probe.md)
    1. [Побудова документації](/doc/sections/uk_UA/5-4-documentation-build.md)
    1. [Вмикання підтримки встановлення документації](/doc/sections/uk_UA/5-5-configuring-the-documentation-install-support.md)
    1. [Вмикання підтримки форматування коду](/doc/sections/uk_UA/5-6-enabling-and-performing-code-formatting-target.md)
    1. [Вмикання підтримки цілі статичного аналізатора коду cppcheck](/doc/sections/uk_UA/5-7-enabling-the-static-code-analyzer-target-with-cppcheck.md)
    1. [Вмикання підтримки статичного аналізатора коду clang-tidy](/doc/sections/uk_UA/5-8-enabling-static-code-analyzer-with-clang-tidy.md)
    1. [Вмикання цілі динамічної перевірки пам'яті Valgrind](/doc/sections/uk_UA/5-9-enabling-the-dynamic-memory-check-target-with-valgrind.md)
    1. [Вмикання підтримки генерування DEB-пакетів з cpack](/doc/sections/uk_UA/5-10-enabling-DEB-package-generation-with-cpack.md)
    1. [Вмикання підтримки генерації flatpak пакету](/doc/sections/uk_UA/5-11-enabling-the-flatpak-package-generation-support.md)
    1. [Вмикання підтримки запуску Docker-контейнера](/doc/sections/uk_UA/5-12-enabling-the-docker-container-build-and-run.md)
    1. [Вмикання перевірок під час виконання програми (sanitizers)](/doc/sections/uk_UA/5-13-enabling-sanitizers.md)
    1. [Вмикання інтеграції libcurl](/doc/sections/uk_UA/5-14-enabling-libcurl.md)
    1. [Вмикання підтримки профілювання з gprof](/doc/sections/uk_UA/5-15-enabling-gprof-profiler-analysis.md)
    1. [Вмикання підтримки профілювання за допомогою vagrind/callgrind](/doc/sections/uk_UA/5-16-enabling-valgrinds-callgrind-profiler-analysis.md)
    1. [Вмикання конвеєра Jenkins всередині Docker контейнера](/doc/sections/uk_UA/5-17-enabling-Jenkins-pipeline-inside-Docker-container.md)
    1. [Вмикання інтеграції бібліотеки nlohmann JSON](/doc/sections/uk_UA/5-18-enabling-the-nlohmann-json-library.md)
    1. [Вмикання пакувальника snap](/doc/sections/uk_UA/5-19-enabling-the-snap-package-manager.md)
    1. [Вмикання підтримки генерування пакунків FreeBSD pkg з cpack](/doc/sections/uk_UA/5-20-enabling-FreeBSD-pkg-package-generation-with-cpack.md)
    1. [Вмикання підтримки генерування WIX MSI-пакетів з cpack](/doc/sections/uk_UA/5-21-enabling-WIX-MSI-package-generation-with-cpack.md)
    1. [Вмикання підтримки генерування RPM-пакунків з cpack](/doc/sections/uk_UA/5-22-enabling-RPM-package-generation-with-cpack.md)
    1. [Вмикання інтеграції zlib](/doc/sections/uk_UA/5-23-enabling-the-zlib-library.md)
    1. [Вмикання інтеграції libpng](/doc/sections/uk_UA/5-24-enabling-the-libpng-library.md)
    1. [Вмикання інтеграції libjpeg](/doc/sections/uk_UA/5-25-enabling-the-libjpeg-library.md)
    1. [Вмикання інтеграції libwebp](/doc/sections/uk_UA/5-26-enabling-the-libwebp-library.md)
    1. [Вмикання інтеграції lunasvg (SVG)](/doc/sections/uk_UA/5-27-enabling-the-lunasvg-library.md)
    1. [Вмикання інтеграції giflib (GIF)](/doc/sections/uk_UA/5-28-enabling-the-giflib-library.md)
    1. [Вмикання інтеграції libtiff (TIFF)](/doc/sections/uk_UA/5-29-enabling-the-libtiff-library.md)
    1. [Вмикання інтеграції OpenEXR (EXR / HDR)](/doc/sections/uk_UA/5-30-enabling-the-openexr-library.md)
    1. [Вмикання інтеграції OpenJPEG (JPEG 2000)](/doc/sections/uk_UA/5-31-enabling-the-openjpeg-library.md)
    1. [Вмикання інтеграції libavif (AVIF)](/doc/sections/uk_UA/5-32-enabling-the-libavif-library.md)
    1. [Вмикання інтеграції libheif (HEIF/HEIC)](/doc/sections/uk_UA/5-33-enabling-the-libheif-library.md)
1. [Запуск головного виконуваного файлу](/doc/sections/uk_UA/6-run-the-executable.md)
    1. [Запуск через IDE](/doc/sections/uk_UA/6-1-IDE-run.md)
    1. Запуск з терміналу
        1. [Пошук згенерованого виконуваного бінарного файлу](/doc/sections/uk_UA/6-2-1-searching-for-the-generated-executable.md)
        1. [Запуск згенерованого виконуваного файлу](/doc/sections/uk_UA/6-2-2-starting-the-generated-executable.md)
    1. Запуск тестів
        1. [Запуск тестів за допомогою ctest](/doc/sections/uk_UA/6-3-1-run-tests-by-the-ctest.md)
        1. [Ручний запуск тестів](/doc/sections/uk_UA/6-3-2-manual-tests-run.md)
1. [Встановлення](/doc/sections/uk_UA/7-installing.md)
