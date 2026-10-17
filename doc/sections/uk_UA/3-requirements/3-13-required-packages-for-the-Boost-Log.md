## Обов'язкові пакунки для Boost.Log

Логером цієї гілки є бібліотека [Boost.Log](https://www.boost.org/doc/libs/release/libs/log/). Проект лінкує її спільні бібліотеки `log`, `log_setup`, `thread` та `filesystem` і не завантажує їхніх вихідних кодів, тож встановіть їхні файли розробника (ОС на базі GNU/Linux):

```
sudo apt install -y libboost-log-dev libboost-thread-dev libboost-filesystem-dev
```

Їх містить і пакунок `libboost-all-dev`, який встановлюють скрипти встановлення пакунків, у родині Red Hat вони називаються `boost-devel`, а у FreeBSD - `boost-libs`. Виконуваному файлу потрібні лише бібліотеки часу виконання Boost.Log, від яких залежить пакунок DEB (їх визначає інструмент `dpkg-shlibdeps`) і які додає пакунок snap.

Як проект веде журнал через неї, описує секція [Логер Boost.Log](/doc/sections/uk_UA/5-project-build/5-66-the-Boost-Log-logger.md).
