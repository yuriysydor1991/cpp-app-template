## Обов'язкові пакунки для підключення до Firebird

Для того щоб мати можливість скомпілювати проект з клієнтською бібліотекою [Firebird](https://firebirdsql.org/) (fbclient) необхідно встановити відповідні файли розробника наступною командою (ОС на базі GNU/Linux):

```
sudo apt install -y firebird-dev
```

Якщо в системі цих файлів розробника немає, то модуль `cmake/enablers/template-project-firebird-enabler.cmake` завантажує сирці [Firebird](https://firebirdsql.org/) (дивіться змінні кешу CMake `TEMPLATE_APP_FIREBIRD_GIT` та `TEMPLATE_APP_FIREBIRD_GIT_TAG`) і збирає лише клієнтську бібліотеку разом з проектом, для чого потрібні наступні інструменти збирання та бібліотеки (ОС на базі GNU/Linux):

```
sudo apt install -y autoconf automake libtool-bin make unzip zlib1g-dev libicu-dev libncurses-dev
```

Параметр CMake `ENABLE_FIREBIRD` (типово `ON`) керує клієнтською бібліотекою. Якщо сконфігурувати проект з `-DENABLE_FIREBIRD=OFF`, то бібліотека fbclient не шукається і не завантажується, а проект збирається без неї: місце драйвера займає клас `DisabledFbClient`, тож виконуваний файл повідомляє, що підтримку Firebird вимкнено, і завершується зі статусом помилки.

Для встановлення самого сервера СКБД [Firebird](https://firebirdsql.org/) (разом з ним встановлюється і бібліотека часу виконання `libfbclient2`) можна використати наступну команду (Ubuntu 26.04 та Debian 13, що постачають файли розробника клієнта версії 4.0; на Ubuntu 24.04 встановіть пакунок `firebird3.0-server`):

```
sudo apt install -y firebird4.0-server
```

### Параметри підключення

Типово виконуваний файл підключається до псевдоніма зразкової бази даних `employee` локального сервера від імені користувача `SYSDBA` з паролем `masterkey`. Типові значення визначені у файлі `src/app/ApplicationContext.cpp` - **не забудьте змінити загальновідомі стандартні облікові дані!** Під час запуску їх перевизначають наступні змінні середовища:

| Змінна | Параметр | Типове значення |
|---|---|---|
| `FIREBIRD_DATABASE` | псевдонім або шлях до файлу бази даних | `employee` |
| `ISC_USER` | ім'я користувача | `SYSDBA` |
| `ISC_PASSWORD` | пароль | `masterkey` |
| `FIREBIRD_HOST` | вузол сервера (порожнє значення залишає локальне підключення) | порожнє |
| `FIREBIRD_PORT` | порт сервера, використовується разом з вузлом | порожнє (3050) |

Наприклад:

```
FIREBIRD_HOST=localhost FIREBIRD_DATABASE=employee ISC_USER=SYSDBA ISC_PASSWORD='my secret' ./CppAppTemplate
```

Серверні пакунки Debian та Ubuntu запитують пароль `SYSDBA` під час встановлення і зберігають його у файлі `/etc/firebird/<версія>/SYSDBA.password` у вигляді тих самих змінних оболонки `ISC_USER` та `ISC_PASSWORD` (змінити його можна командою `sudo dpkg-reconfigure firebird<версія>-server`). Файлу бази даних `employee` пакунки не містять: як створити його з доданого SQL-сценарію, описує файл `/usr/share/doc/firebird4.0-examples/examples/README.Debian` пакунка `firebird4.0-examples` (Firebird 4.0). Для підключення від імені окремого користувача створіть його обліковим записом `SYSDBA` в інструменті `isql-fb` і передайте через змінні `ISC_USER` та `ISC_PASSWORD`:

```
CREATE USER template_test_user PASSWORD 'template_test_password';
```
