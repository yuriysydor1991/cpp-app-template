## Обов'язкові пакунки для підключення до Firebird

Для того щоб мати можливість скомпілювати проект з клієнтською бібліотекою [Firebird](https://firebirdsql.org/) (fbclient) необхідно встановити відповідні файли розробника наступною командою (ОС на базі GNU/Linux):

```
sudo apt install -y firebird-dev
```

Якщо в системі цих файлів розробника немає, то модуль `cmake/enablers/template-project-firebird-enabler.cmake` завантажує сирці [Firebird](https://firebirdsql.org/) (дивіться змінні кешу CMake `TEMPLATE_APP_FIREBIRD_GIT` та `TEMPLATE_APP_FIREBIRD_GIT_TAG`) і збирає лише клієнтську бібліотеку разом з проектом, для чого потрібні наступні інструменти збирання та бібліотеки (ОС на базі GNU/Linux):

```
sudo apt install -y autoconf automake libtool-bin make unzip zlib1g-dev libicu-dev libncurses-dev
```

Для встановлення самого сервера СКБД [Firebird](https://firebirdsql.org/) (разом з ним встановлюється і бібліотека часу виконання `libfbclient2`) можна використати наступну команду (ОС на базі GNU/Linux, суфікс версії може відрізнятись у різних дистрибутивах):

```
sudo apt install -y firebird3.0-server
```

Стандартні облікові дані, що використовує шаблон (`SYSDBA` / `masterkey`), і стандартну зразкову базу даних `employee` можна змінити у класі `ApplicationContext` або перевизначити для власного розгортання - **не забудьте змінити загальновідомі стандартні облікові дані!**
