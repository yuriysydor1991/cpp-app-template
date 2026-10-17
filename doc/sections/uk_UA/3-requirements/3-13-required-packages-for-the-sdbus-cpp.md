## Обов'язкові пакунки для sdbus-c++

D-Bus сервер цієї гілки побудовано на бібліотеці [sdbus-c++](https://github.com/Kistler-Group/sdbus-cpp) з API версії 2.x. Встановіть її файли розробника там, де дистрибутив постачає версію 2.x (Ubuntu 26.04, Debian 13):

```
sudo apt install -y libsdbus-c++-dev pkg-config libsystemd-dev
```

Система без sdbus-c++ або зі старішою версією (1.x в Ubuntu 24.04, EPEL 9 чи Fedora до 42) отримує завантажені вихідні коди випуску `TEMPLATE_APP_SDBUSCXX_GIT_TAG` (за замовчуванням `v2.1.0`), зібрані статично у виконуваний файл, для чого потрібні інструмент `pkg-config` і файли `libsystemd-dev`. Жоден із завантажених файлів sdbus-c++ не встановлюється разом із проектом.

На Ubuntu 24.04 скрипт [scripts/packages/install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh) натомість збирає випуск `v2.1.0` з його вихідних кодів і встановлює в систему, тож конфігурація знаходить його там.

Параметр CMake `ENABLE_LIBSDBUSCXX` на цій гілці типово має значення `ON`: приклад `src/sdbuscxx` потребує бібліотеки, тож значення `OFF` зупиняє конфігурацію з поясненням, доки з файлу `src/CMakeLists.txt` не буде вилучено виклик `add_subdirectory(sdbuscxx)` разом з підкаталогом `src/sdbuscxx` і його використанням у файлі `src/app/applications/Application.cpp`.

Виконуваний файл займає ім'я `org.cppapptemplate.SimpleServer` на сеансовій шині і надає властивість `CurrentDate` інтерфейсу `org.cppapptemplate.SimpleServer1` об'єкта `/org/cppapptemplate/SimpleServer`, доки його не зупинять `Ctrl+C`, команда `kill` чи інший сигнал завершення. Встановлений файл `share/dbus-1/services/org.cppapptemplate.SimpleServer.service` дає сеансовій шині змогу запустити сервер під час першого виклику. Запитати запущений сервер можна інструментом `busctl`:

```
busctl --user introspect org.cppapptemplate.SimpleServer /org/cppapptemplate/SimpleServer
busctl --user get-property org.cppapptemplate.SimpleServer /org/cppapptemplate/SimpleServer org.cppapptemplate.SimpleServer1 CurrentDate
```

Без сеансової шини виконуваний файл завершується зі статусом помилки, а компонентний тест обміну пропускається, як і тоді, коли ім'я займає інший запущений сервер.
