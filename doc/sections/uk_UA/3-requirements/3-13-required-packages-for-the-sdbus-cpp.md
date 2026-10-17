## Обов'язкові пакунки для sdbus-c++

Виклики D-Bus цієї гілки виконує бібліотека [sdbus-c++](https://github.com/Kistler-Group/sdbus-cpp) з API версії 2.x. Встановіть її файли розробника там, де дистрибутив постачає версію 2.x (Ubuntu 26.04, Debian 13):

```
sudo apt install -y libsdbus-c++-dev pkg-config libsystemd-dev
```

Система без sdbus-c++ або зі старішою версією (1.x в Ubuntu 24.04, EPEL 9 чи Fedora до 42) отримує завантажені вихідні коди випуску `TEMPLATE_APP_SDBUSCXX_GIT_TAG` (за замовчуванням `v2.1.0`), зібрані статично у виконуваний файл, для чого потрібні інструмент `pkg-config` і файли `libsystemd-dev`. Жоден із завантажених файлів sdbus-c++ не встановлюється разом із проектом.

На Ubuntu 24.04 скрипт [scripts/packages/install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh) натомість збирає випуск `v2.1.0` з його вихідних кодів і встановлює в систему, тож конфігурація знаходить його там.

Параметр CMake `ENABLE_LIBSDBUSCXX` на цій гілці типово має значення `ON`: приклад `src/sdbuscxx` потребує бібліотеки, тож значення `OFF` зупиняє конфігурацію з поясненням, доки з файлу `src/CMakeLists.txt` не буде вилучено виклик `add_subdirectory(sdbuscxx)` разом з підкаталогом `src/sdbuscxx` і його використанням у файлі `src/app/applications/Application.cpp`.

Виконуваний файл читає властивості `Hostname`, `PrettyHostname` та `OperatingSystemPrettyName` служби `org.freedesktop.hostname1` (`systemd-hostnamed`) на системній шині. Без системної шини чи без такої служби він завершується зі статусом помилки, а живі компонентні тести пропускаються. Ті самі властивості можна перевірити інструментом `busctl`:

```
busctl get-property org.freedesktop.hostname1 /org/freedesktop/hostname1 org.freedesktop.hostname1 Hostname
```
