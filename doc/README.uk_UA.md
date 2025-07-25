**Твій охайний шаблон для С++ програми**

# Ціль проекту-шаблону

Проект-шаблон призначений для пришвидшення процесу побудови програми на стадії започаткування проекту за допомогою готової початкової структури програми. Отож розробник може одразу перейти до реалізації конкретної програми з мінімальними затратами на базову структуру.

Полегшує вийти за рамки коду - створюй складні і готові до поставки **програмний продукти** швидко!

Дозволяє стрімке створення завершеного **програмного продукту** - на противагу звичайного куска коду чи простої програми.

**Створи форк і одразу реалізуй програму!**

Переглянь доступні гілки у репозиторії проекту-шаблону і використай найбільш підходящий варіант або комбінуй декілька гілок їх з'єднанням щоб створити найкращу структуру шаблону для вдоволення потреб:

- гілка `main` розміщена за адресою [головна сторінка проеку](https://github.com/yuriysydor1991/cpp-app-template) (**поточна**) один файл з функцією `main` і з усіма можливими інтеграціями для генерації одного бінарного виконуваного файлу.
- гілка `app` розміщена за адресою [app](https://github.com/yuriysydor1991/cpp-app-template/tree/app) яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу.
- гілка `applib` розміщена за адресою [applib](https://github.com/yuriysydor1991/cpp-app-template/tree/applib) яка складається з класів банарного виконуваного файлу з додатковими інфраструктурними класами для генерації підключаємої бібліотеки і заголовкових файлів (доступні для встановлення), що призначені для поширення коду бібліотеки для повторного перевикористання іншими бінарнами файлами.
- гілка `lib` розміщена ща адресою [lib](https://github.com/yuriysydor1991/cpp-app-template/tree/lib) і яка призначена для предоставляння початкової інфраструктури для реалізації бібліотеки разом з заголовковими підключаємими файлами і документацією за необхідності.
- гілка `appQt6` розміщена за адресою [appQt6](https://github.com/yuriysydor1991/cpp-app-template/tree/appQt6) яка містить загальні класи для генерації бінарного виконуваного файлу разом з структурою заданою для розробки віконної програми на базі Qt6 разом з QML.
- гілка `appGtkmm3` розміщена за адресою [appGtkmm3](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3) яка містить загальні класи для генерації бінарного виконуваного файлу разом з структурою заданою для розробки віконної програми на базі GTKmm-3.0 s C++.
- гілка `appGtkmm3Glade` розміщена за адресою [appGtkmm3Glade](https://github.com/yuriysydor1991/cpp-app-template/tree/appGtkmm3Glade) яка містить загальні класи для генерації бінарного виконуваного файлу разом з структурою заданою для розробки віконної програми на базі C++ з GTKmm-3.0 і [Glade](https://en.wikipedia.org/wiki/Glade_Interface_Designer) - програми для створення візульних інтерфейсів.
- гілка `appFreeGlut` розміщена за адресою [appFreeGlut](https://github.com/yuriysydor1991/cpp-app-template/tree/appFreeGlut) яка містить загальні класи для генераці одинарного бінарного виконуваного файлу разом з початковою інфраструктурою для розробки у OpenGL 3D разом з FreeGlut.
- гілка `appSDL2` розміщена за адресою [appSDL2](https://github.com/yuriysydor1991/cpp-app-template/tree/appSDL2) яка містить загальні класи для генераці одинарного бінарного виконуваного файлу разом з початковою інфраструктурою для розробки у OpenGL 3D разом з [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) і набагато більше!
- гілка `appMeson` розміщена за адресою [appMeson](https://github.com/yuriysydor1991/cpp-app-template/tree/appMeson) яка містить загальні інфраструктурні класи програми для генераці одинарного бінарного виконуваного файлу разом з системою побудови [Meson](https://mesonbuild.com/).
- гілка `appWt4` розміщена за адресою [appWt4](https://github.com/yuriysydor1991/cpp-app-template/tree/appWt4) шаблон з інфраструктурою для швидкого старту реалізації Web-програми на основі [Wt C++](https://www.webtoolkit.eu/wt) фулстек фреймворку.
- гілка `appPgSQLxx` розміщена за адресою [appPgSQLxx](https://github.com/yuriysydor1991/cpp-app-template/tree/appPgSQLxx) котра містить інфраструктуру для швидкого старту розробки застосунку з використанням СУБД [PostgreSQL](https://en.wikipedia.org/wiki/PostgreSQL)
- гілка `appBoostBeast` розміщена за адресою [appBoostBeast](https://github.com/yuriysydor1991/cpp-app-template/tree/appBoostBeast) котра містить інфраструктуру для швидкого старту розробки Web-програми з використанням швидкого HTTP сервера [Beast](https://www.boost.org/libs/beast) від Boost.
- гілка `appMySQLCppConn` розміщена за адресою [appMySQLCppConn](https://github.com/yuriysydor1991/cpp-app-template/tree/appMySQLCppConn) котра містить інфраструктуру для швидкого старту розробки застосунку з використанням СУБД [MySQL](https://uk.wikipedia.org/wiki/MySQL)
- гілка `appSQLiteCpp3` розміщена за адресою [appSQLiteCpp3](https://github.com/yuriysydor1991/cpp-app-template/tree/appSQLiteCpp3) котра містить інфраструктуру для швидкого старту розробки застосунку з використанням СУБД [SQLite](https://en.wikipedia.org/wiki/SQLite) через бібліотеку [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp)
- гілка `appMongoDBCpp4` розміщена за адресою [appMongoDBCpp4](https://github.com/yuriysydor1991/cpp-app-template/tree/appMySQLCppConn) котра містить інфраструктуру для швидкого старту розробки застосунку з використанням NoSQL СУБД [MongoDB](https://en.wikipedia.org/wiki/MongoDB)
- гілка `appLog4Cpp5` розміщена за адресою [appLog4Cpp5](https://github.com/yuriysydor1991/cpp-app-template/tree/appLog4Cpp5) котра містить інфраструктуру для швидкого старту розробки застосунку з використанням багатофункціональної бібліотеки логування повідомлень [log4cpp](https://log4cpp.sourceforge.net/)
- гілка `appBoostLog` розміщена за адресою [appBoostLog](https://github.com/yuriysydor1991/cpp-app-template/tree/appBoostLog) котра містить інфраструктуру для швидкого старту розробки застосунку з використанням бібліотеки логування повідомлень [Boost.Log](https://www.boost.org/doc/libs/latest/libs/log/doc/html/index.html)
- гілка `appCURL` розміщена за адресою [appCURL](https://github.com/yuriysydor1991/cpp-app-template/tree/appCURL) котра містить інфраструктуру для швидкого старту розробки застосунку з використанням бібліотеки-клієнта [CURL](https://en.wikipedia.org/wiki/CURL) для завантажень даних з мережі і яка підтримує багато протоколів (включаючи HTTP).

Редагуй поточний файл `README.md` і `CHANGELOG.md` щоб документація відповідала впровадженому коду. Для перекладів даного файлу `README.md`:
- `uk_UA` за відносною адресою doc/README.uk_UA.md

Більше за посиланням [kytok.org.ua](http://www.kytok.org.ua/)

💵 Підтримай проект за посиланням [http://kytok.org.ua/page/pozertvy](http://kytok.org.ua/page/pozertvy)

# Клонування С++ проекту-шаблону

Щоб негайно розпочати реалізування нової програми склонуй поточний проекту у свою локальну директорію, виконавши наступну команду в терміналі (для GNU/Linux):

```
git clone https://github.com/yuriysydor1991/cpp-app-template.git
```

або

```
git clone https://gitlab.com/yuriysydor1991/cpp-app-template.git
```

Після успішного виконання даної команди у поточній відкритій директорї повинна з'явитись нова під директорія `cpp-app-template`. Отож відкрий її за допомогою команди `cd cpp-app-template`.

# Створення форку і заміна оригінального репозиторію

Для того щоб увесь вміст проекту-шаблону скопіювати у свій чистий новостворений `git`-репозиторій (**без жодних файлів** на подобі `README.md`, `.gitignore`, `LICENCE` або будь-яких інших), склонуй поточний проект-шаблон `cpp-app-template` у свою локальну директорію і виконай заміну посилання оригінального рипозиторію на власний всередині директорії проекту-шаблону:

```
# Заміни наступний URL на власний з нового репозиторію

git remote set-url origin https://github.com/yuriysydor1991/cpp-app-template.git
```

Заміни оригінальне посилання проекту-шаблону `https://github.com/yuriysydor1991/cpp-app-template.git` на власний від свого новоствореного `git`-репозиторію.

Для того щоб перевірити чи замінився URL для проекту-шаблону (куди будуть надсилатись усі зміни) необхідно виконати наступну команду:

```
git remote -v
```

Після виконання якої у терміналі повинно висвітлитись нове посилання на новий проект.

Тепер можна скопіювати усі зміни до нового розміщення, виконуючи наступну команду:

```
git push
```

Створення форку може бути виконаним через Web-панель інтерфейсу git.

# Вимоги

Дана секція містить список усіх вимог до пакунків, програм чи інструментів які повинні бути встановленими у системі для того щоб побудувати проект-шаблон чи виконати інші функції.

## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

## Обов'язкові інструменти для ОС на базі MS Windows

Для того щоб мати можливість розробляти і будувати проект необхідно завантажити MSVC інсталятор з сторінки [https://visualstudio.microsoft.com/downloads/](https://visualstudio.microsoft.com/downloads/) і увімкнути встановлення інструменти для нативної розробки для C++.

Окремо інсталятор на кожен необхідний проект можна завантажити з окремих джерел (**можлива необхідність пошуку і встановлення інших пакунків**):
- Система вірсіювання Git за адресою [https://git-scm.com/downloads/win](https://git-scm.com/downloads/win)
- Система побудови CMake за адресою [https://cmake.org/download/](https://cmake.org/download/)
- Пакунки Windows 10 SDK за адресою [https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/)

## Необов'язкові пакети для тестів

Якщо необхідно побудувати і виконати доступні тести необхідно встановити GTest або забезпечити доступ до мережі Інтернет у випадку самостійного встановлення скриптами системи збірки CMake проекту-шаблону. Для встановлення необхідно виконати команду:

```
sudo apt install -y googletest
```

Більш детально у секції [тести проекту](#тести-проекту).

## Необов'язкові пакети для створення документації

Якщо необхідно генерувати документацію за допомогою інструменту Doxygen з коментарів файлів вихідного джерельного коду необхідно виконати команду:

```
sudo apt install -y doxygen graphviz
```

Переглянь секцію [Побудова документації](#побудова-документації) як увімкнути підтримку побудови/встановлення документації.

## Необов'язкові пакети для форматування коду

Для підтримки автоматичного форматування коду за допомогою наявної CMake-цілі `clang-format` відповідний інструмент `clang-format` повинен бути встановленим наступною командою (для GNU/Linux систем):

```
sudo apt install -y clang-format
```

Переглянь деталі конфігурації у секції [Вмикання підтримки форматування коду](#вмикання-підтримки-форматування-коду).

## Необов'язкові пакети для статичного аналізатора коду cppcheck

Для того щоб виконувати статичний аналіз коду за допомогою команди `cppcheck` встановіть її наступною командою:

```
sudo apt install -y cppcheck
```

Більш детальніше у секції [Вмикання підтримки цілі статичного аналізатора коду cppcheck](#вмикання-підтримки-цілі-статичного-аналізатора-коду-cppcheck).

## Необов'язкові пакети для статичного аналізатора коду clang-tidy

Для того щоб виконувати статичний аналіз коду за допомогою команди `clang-tidy` встановіть її наступною командою:

```
sudo apt install -y clang-tidy
```

Більш детальніше у секції [Вмикання підтримки статичного аналізатора коду clang-tidy](#вмикання-підтримки-статичного-аналізатора-коду-clang-tidy).

## Необов'язкові пакет для перевірки використання пам'яті за допомогю Valgrind

Для того щоб виконувати перевірку динамічного використання пам'яті за допомогою команди `valgrind` необхідно встановити її за допомогою наступної команди:

```
sudo apt install -y valgrind
```

Біль детально у секції [Вмикання цілі динамічної перевірки пам'яті Valgrind](#вмикання-цілі-динамічної-перевірки-памяті-valgrind).

## Необов'язковий програми для генерації пакету flatpak

Для того щоб мати змогу генерувати пакет flatpak з ресурсів проекту необхідно встановити інструменти `flatpak` і `flatpak-builder`:

```
sudo apt install -y flatpak flatpak-builder
```

Також знадобиться один з цільових SDK який може бути встановленим за допомогою команди подібної на наступну:

```
flatpak install runtime/org.freedesktop.Sdk/x86_64/20.08
```

Необіхдно замінити `runtime/org.freedesktop.Sdk/x86_64/20.08` власним варіантом обраного SDK. У документації до flatpak можна визначити як переглянути усі доступні варіанти.

Деталі у секції [#Вмикання підтримки генерації flatpak пакету](#вмикання-підтримки-генерації-flatpak-пакету)

## Необов'язкові пакети для запуску контейнера Docker

Для того щоб мати змогу будувати і запускати контейнери Docker разом з побудовою проекту шаблону його необхідно встановити за допомогою команди (ОС на базі GNU/Linux):

```
sudo apt install -y docker.io docker-buildx
```

Наступним кроком являється конфігурування сервісу Docker для прослуховування на локальному інтерфейсі для TCP підключень:

```
sudo systemctl edit docker 
```

Після відкриття конфігураційного файлу сервісу Docker необхідно вставити в його кінець наступні рядки:

```
[Service]
ExecStart=
ExecStart=/usr/bin/dockerd -H fd:// -H tcp://127.0.0.1:2375
ExecReload=/bin/kill -s HUP $MAINPID
```

Після чого зберегти файл і закрити. Тепер потрібно перезавантажити сервіси командами:

```
sudo systemctl daemon-reload
sudo systemctl restart docker.service
```

Для перевірки того чи сервіс Docker працює коректно можна спробувати локально запустити спеціальний контейнер `hello-world`:

```
DOCKER_HOST="tcp://127.0.0.1:2375" docker run hello-world
```

Можна додати рядок `export DOCKER_HOST="tcp://127.0.0.1:2375"` до файлу конфігурації Bash поточного користувача ОС `.bashrc` щоб уникнути вказування змінної середовища `DOCKER_HOST` у кожну команду запуску програми Docker:

```
echo 'export DOCKER_HOST="tcp://127.0.0.1:2375"' >> ~/.bashrc
```

Деталі у секції [Вмикання підтримки запуску Docker-контейнера](#вмикання-підтримки-запуску-docker-контейнера)

# Структура проекту

## Реалізуй код одразу!

Щоб одразу приступити до реалізації конкретної програми необхідно перейти до файлу `main.cpp`, який призначений для утримання початкового коду реалізації програми. Більш точно новий код повинен бути розміщений у функції `int main(int argc, char** argv)`.

**Але пам'ятаємо про принципи хорошого коду SOLID і його декомпозицію!**

Рекомендується створити нові окремі директоріх у проекті котрі будуть розміщувати додаткові реалізовані компоненти програми і включити їх до реалізації функції `main`. На противагу розміщення усього коду тільки всередині функції `main` (для тривіального проекту це може бути оправданим).

## Зміна назви проекту і головного виконуваного файлу

Після клонування і копіювання проекту-шаблону необхідно замінити назву проекту і його основного бінарного виконуваного файлу у корінному файлі `CMakeLists.txt`, запроваджуючи нове значення для CMake-змінних `PROJECT_NAME` і/або  `PROJECT_BINARY_NAME`. Рекомендується виконувати заміну назв для того щоб нова програма предаставляла новий конкретний проект замість назви за замовчуванням - `CppAppTemplate` і запобіганню конфліктів під час встановлення виконуваного файлу у цільову систему.

## Версіювання і інші параметри проекту

Під час конфігурації файлів побудови проекту файли побудови `CMakeLists.txt` системи CMake відслідковують поточний хеш коміту проекту, ім'я проекту, дату конфігурації і версію проекту. Дані параметри проекту передаються у файл кодової конфігурації проекту що знаходиться за шляхом `src/app/project-global-decls.h.in`. Файл `src/app/project-global-decls.h.in` буде скомпільовано системою CMake під час конфігурації проекту у кореневу директорію побудови проекту у якості `project-global-decls.h`. Клас `ApplicationVersionPrinter` включає даний файл кодової конфігурації проекту і використовує надану з нього інформацію для відображення відповідного повідомлення версії програми у термінал. Зазвичай, даний код виконується під час виклику основного бінарного виконуваного файлу проекту з прапорцями командного рядка на подобі `-v` або `--version`. Після друку версії і іншої допоміжної інформації у відкритий термінал, реалізація за замовчуванням класу `ApplicationVersionPrinter` повертає нульовий стан виконання програми (індикатор успішного безпомилкового виконання) і після чого виконуваний бінарний файл завершує свою роботу.

## Тести проекту

Проект-шаблон вже "з коробки" містить деякі прості примірники тестів. Спираючись на них, можна реалізовувати повноцінні тести нововпровадженого коду.

Більш детально у секції [Побудова проекту](#побудова-проекту) про те як увімкнути підтримку побудови тестів за допомогою CMake.

### Фреймворк тестів Google Test

На даний момент приклади тестів опираються на фреймворк GTest. Фреймворк GTest стає доступним у проекті за допомогою команд CMake на подобі `FetchContent_Declare`/`FetchContent_MakeAvailable` (за допомогою доступу до мережі Інтернет) у випадку, якщо система не предоставляє фреймворк тестування.

Звісно, скрипти `CMakeLists.txt` визначають чи у ОС побудови проекту присутній фреймворк тестування GTest тільки якщо самі тести проекту-шаблону увімкнені прапорцем `ENABLE_UNIT_TESTS`. Використання фреймворку тестування GTest присутнього у системі можна вимкнути встановленням відповідного значення для CMake-змінної `GTEST_TRY_SYSTEM_PROBE`.

Детальніше у файлі відповідальному за встановлення джерела GTest за шляхом `cmake/template-project-GTest-enabler.cmake` де також можна змінити версію фреймворку тестування тощо.

## Розширення

Так як проект-шаблон ще розробляється то у майбутньому будуть впроваджені нові можливості.

# Побудова проекту

## Побудова за допомогою IDE

Звісно якщо використовуване інтегроване середовище розробки, себто IDE, підтримує інтеграцію з системою побудови CMake, тоді можна просто натиснути відповідні кнопки "Побудувати" і/або "Запустити" які розміщені десь у вікні середовища, і готово! Не потрібно виконувати команди конфігурації, побудови, пошуку виконуваного файлу і його виконання. Усе виконується автоматично самим середовищем автоматичної побудови.

## Побудова проекту-шаблону через командний рядок

Проект використовує систему побудови CMake - отож команди побудови мають бути знайомими більшосі C++ розробників на планеті!

Звісно, проект-шаблон спочатку потребує клонування за допомогою команди `git clone <URL>` і його коренева директорія повинна бути відкритою у використовуваному IDE. Після чого можна виконати команди:

```
# всередині кореневої директорії проекту-шаблону

mkdir -vp build && cd build && cmake ../ && cmake --build . --target all
```

Яка у свою чергу створить директорію `build` (директорія вже додана до файлу `.gitignore`), конфігурує проект використовуючи доступну у ОС версію системи побудови CMake (детальніше у секції [Вимоги](#вимоги) даного документу), і на кінець, будує усі цілі доступні у проекті-шаблоні.

## Вмикання тестів

### Вмикання юніт-тестів

Для того щоб зробити юніт тестування доступним (для побудови і запуску) необхідно перекорфігурувати проект-шаблон з увімкненою опцією `ENABLE_UNIT_TESTS` за допомогою команди (для GNU/Linux):

```
# у кореневій директорії проекту

mkdir -vp build && cd build && cmake ../ -DENABLE_UNIT_TESTS=ON && cmake --build . --target all
```

### Запобігання використання GTest з ОС

Для вимкнення використання ресурсів наявного фреймворку GTest необхідно встановити відповідне значення для CMake-змінної `GTEST_TRY_SYSTEM_PROBE` за допомогою команди конфігурування проекту (для GNU/Linux):

```
# з кореневої директорії проекту-шаблону

mkdir -vp build && cd build && cmake ../ -DENABLE_UNIT_TESTS=ON -DGTEST_TRY_SYSTEM_PROBE=OFF && cmake --build . --target all
```

Під час виконання команди система побудови проекту спробує встановити GTest тільки у межах поточного проекту через мережу Інтернет з версією вказаною у файлі `cmake/template-project-GTest-enabler.cmake`.

## Побудова документації

На даний момент доступна побудова документації за допомогою програми Doxygen з наявних коментарів вихідного джерельного коду проекту.

Для того щоб зробити доступною ціль для побудови документації за допомогою Doxygen під час його конфігурації необхідно встановити змінну `ENABLE_DOC_DOXYGEN` у значення `ON` (для ОС на базі GNU/Linux):

```
# з кореневої директорії проекту-шаблону

mkdir -vp build && cd build && cmake ../ -DENABLE_DOC_DOXYGEN=ON
```

Яка в свою чергу створить директорію з назвою `build` всередині кореневої директорію проекту-шаблону, відкриє її за допомогою команди `cd` і сконфігурує проект з увімкненою ціллю для побудови Doxygen документації.

На кінкець можна побудувати документацію виконуючи команду:

```
# всередині директорії побудови проекту

cmake --build . --target Doxygen-doc
```

Яка у свою чергу створює директорію `doc/CppAppTemplate-html` (вже додана до файлу `.gitignore`) що буде містити зібрану документацію у вигляді HTML-сторінок і ресурсів до них. Для того щоб відкрити і оглянути згенеровану документацію необхідно відкрити файл який лежить за шляхом `doc/CppAppTemplate-html/index.html` від кореня проекту. Директорія `CppAppTemplate-html` змінить назву у відповідності до зміни назви головного виконуваного файлу проекту-шаблону за допомогою встановлення нового значення для змінної `PROJECT_BINARY_NAME` у файлі `cmake/template-project-misc-variables-declare.cmake` або змінну `DOXYGEN_OUT_HTML_NAME` яка визначає ім'я для цілої цільової директорії для згенерованої HTML-документації.

Файл `doc/Doxyfile.in` від кореня проекту містить усі параметри конфігурації які можуть бути зміненими для зміни виводу документації.

## Вмикання підтримки встановлення документації

Наявна можливість підтримки встановлення документації за допомогою встановлення змінних `ENABLE_DOC_DOXYGEN` і `DOXYGEN_DO_INSTALL` у значення `ON` під час конфігурування прокету-шаблону за допомогою команди:

```
# inside the project build directory

cmake ../ -DENABLE_DOC_DOXYGEN=ON -DDOXYGEN_DO_INSTALL=ON
```

Змінна `DOXYGEN_OUT_HTML_NAME` сконфігурує назву для директорії HTML документації (передається до файлу `Doxyfile`).

## Вмикання підтримки форматування коду

Для того щоб зробити доступною ціль `clang-format` необхідно встановити змінну `ENABLE_CLANGFORMAT` у значення `ON` під час конфігурації проекту-шаблону (для GNU/Linux ОС):

```
# всередині кореня проекту-шаблону

mkdir -vp build && cd build && cmake ../ -DENABLE_CLANGFORMAT=ON
```

Для того щоб виконати форматування коду усього проекту-шаблону у відповідності до стандартів вказаних у файлі `misc/.clang-format` необхідно виконати наступну команду:

```
# всередині директорії побудови проекту-шаблона

cmake --build . --target clang-format
```

Деталі цілі `clang-format` можна перегляну у файлі `cmake/template-project-clang-format-target.cmake` субмодуля системи CMake.

## Вмикання підтримки цілі статичного аналізатора коду cppcheck

Для того щоб зробити доступною для виконання ціль статичного аналізу за допомогою `cppcheck` необхідно сконфігурувати проект з увімкненою опцією `ENABLE_CPPCHECK`:

```
# всередині кореневої директорії проекту-шаблону

mkdir -vp build && cd build && cmake ../ -DENABLE_CPPCHECK=ON
```

І для безпосереднього виконання статичного аналізу коду необхідно викликати ціль `cppcheck` для побудови:

```
# всередині директорії побудови проекту-шаблону

cmake --build . --target cppcheck
```

Деталі цілі `cppcheck` можна перегляну і/або змінити у файлі `cmake/template-project-cppcheck-target.cmake` системи збірки CMake.

## Вмикання підтримки статичного аналізатора коду clang-tidy

Для того щоб увімкнути статичну перевірку коду кожної одиниці транслювання або ж кожного файлу `*.cpp` у проекті за допомогою програми `clang-tidy` необхідно увімкнути її під час конфігурування системи побудови проекту, встановлюючи змінну `ENABLE_CLANG_TIDY` у значення `ON` у команді конфігурації:

```
# всередині кореневої директорії проекту-шаблону

mkdir -vp build && cd build && cmake ../ -DENABLE_CLANG_TIDY=ON
```

Щоб виконати статичний аналіз коду для будь-якої CMake-цілі необхідно запустити її побудову і команда `clang-tidy` автоматично перевірить кожну одиницю транслювання:

```
# inside the project build directory

cmake --build . --target all
```

Щоб переглянути докладну інформацію по статичному аналізатору `clang-tidy` необхідно переглянути файли `cmake/template-project-clang-tidy-target.cmake`, `misc/.clang-tidy` і документацію до відповідної використовуваної вермії `clang-tidy`.

**Попередження** Виконання статичного аналізу коду за допомогою `clang-tidy` може значно збільшити час побудови цілей.

## Вмикання цілі динамічної перевірки пам'яті Valgrind

Для того щоб увімкнути для побудови ціль `valgrind` необхідно сконфігурувати проект з увімкненою опцією `ENABLE_VALGRIND` на подобі наступної команди (для GNU/Linux ОС і подібних):

```
# всередині кореневої директорії проекту

mkdir -vp build && cd build && cmake ../ -DENABLE_VALGRIND=ON
```

Для виконання динамічної перевірки пам'яті у виконуваного файлу проекту необхідно виконати наступну команду:


```
# всередині директорії побудови проекту-шаблону

cmake --build . --target valgrind
```

Деталі цілі `valgrind` можуть бути переглянутими і/або зміненими у файлі що лежить за шляхом `cmake/template-project-valgrind-target.cmake`.

**Попередження! Ціль запустить на виконання головний виконуваний файл проекту.** Динамічна перевірка пам'яті виконуваного файлу проекту-шаблону вимагає запуск програми і повний прохід виконання. Необхідно забезпечити кінечність виконання програми щоб запобігти невизначено довгий час перевірки.

## Вмикання підтримки генерування DEB-пакетів з cpack

Для того щоб мати змогу згенерувати `deb`-пакет необіхдно сконфігурувати проект для підтримки команди `cpack` за допомогою змінної `ENABLE_DEB`:

```
# всередині кореневої директорії проекту 

mkdir -vp build && cd build && cmake ../ -DENABLE_DEB=ON
```

Наступним кроком буде збирання або компіляція усіх необхідних файлів які повинні входити у `deb`-пакет:

```
# всередині директорії побудови проекту-шаблону

cmake --build . --target all
```

На кінець, необіхдно виконати команду `cpack` всередині директорії побудови проекту-шаблону:

```
# всередині директорії побудови проекту-шаблону

cpack
```

Згенерований пакет повинен згенеруватись всередині кореня директорії побудови проекту. Наприклад, якщо ім'я проекту було не зміненим і його версія 0.8.0 тоді назва пакету може виглядати наступним чином: `CppAppTemplate-0.8.0-Linux.deb`.

Для того щоб переглянути або змінити параметри створення `deb`-пакетів необхідно відвідати файл `cmake/template-project-deb-enabler.cmake`.

## Вмикання підтримки генерації flatpak пакету

Для того щоб увімкнути підтримку генерації пакету постачання flatpak на даному проекті-шаблоні необхідно сконфігурувати систему побудови з увімкненим параметром `ENABLE_FLATPAK` (для GNU/Linux подібних ОС):

```
# всередині кореневої директорії проекту 

mkdir -vp build && cd build && cmake ../ -DENABLE_FLATPAK=ON
```

Успішно виконана команда у свою чергу увімкне ціль для побудови під назвою `flatpak`.

На кінець, щоб згенерувати пакет розповсюдження flatpak необхідно побудувати ціль `flatpak`:

```
# всередині директорії побудови проекту-шаблону

cmake --build . --target flatpak
```

У разі успішної побудови цілі буде створено файл під назвою `CppAppTemplate-0.9.0.flatpak` у кореневій директорії побудови проекту шаблону. Для того щоб преглянути або/і змінити ціль побудови пакету flatpak необхідно відвідати файли `cmake/template-project-flatpak-target.cmake` або `misc/flatpak.conf.json.in`.

Необхідно звернутися до документації програми flatpak для того щоб дізнитись як встановлювати або запускати програми котрі розповсюджуються у вигляді пакету flatpak. Для не змінених паарметрів поточного проекту вони можуть виглядати наступним чином:

```
# для встановлення (версія може змінитись)
# всередині директорії побудови проекту-шаблону 
flatpak install --user CppAppTemplate-0.9.0.flatpak

# для запуску встановленої програми
flatpak run ua.org.kytok.template.CppAppTemplate
```

## Вмикання підтримки запуску Docker-контейнера

Щоб увімкнути і запустити Docker контейнер разом з цільовим бінарним виконуваним файлом поточного проекту-шаблону необхідно встановити у значення `ON` змінну `ENABLE_DOCKER` за допомогою команди:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_DOCKER=ON
```

Після чого можна запустити побудову контейнера Docker і слідуючий запуск цільового виконуваного файлу проекту за допомогою комнади (CMake-ціль `docker-single-run`):

```
# в середині кореневої директорії проекту

cmake --build build --target docker-single-run 
```

Для деталей CMake-цілі побудови `docker-single-run` слід звернутись до файлу `cmake/dockerers/template-project-docker-single-runner-target.cmake`.

## Вмикання перевірок під час виконання програми (sanitizers)

Для того щоб увімкнути додаткові перевірки під час виконання програми необхідно сконфігурувати проект з увімкнуною змінною `ENABLE_SANITIZERS`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_SANITIZERS=ON
```

Для вмикання загальних перевірок. Деталі і список прапорців перевірок у файлі `cmake/template-project-sanitizers.cmake`.

Також присутня можливість вмикання перевірок виконання потоків на предмет помилок і спотвернення даних (data rises) насутпною командою:

```
cmake -S . -B build -DENABLE_SANITIZERS_THREADS=ON
```

Не слід поєднювати `ENABLE_SANITIZERS` і `ENABLE_SANITIZERS_THREADS`.

Будь-які знахідки увімкненими перевірками будуть друкуватись у стандартні потоки вводу програми (stdout/stderr).

## Вмикання інтеграції libcurl

Для того щоб увімкнути підтримку [libcurl](https://uk.wikipedia.org/wiki/CURL) для проекту, використовуючи встановлену версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_LIBCURL`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_LIBCURL=ON
```

# Запуск головного виконуваного файлу

## Запуск через IDE

Звісно якщо використовуване інтегроване середовище розробки, себто IDE, підтримує інтеграцію з системою побудови CMake, тоді можна просто натиснути відповідні кнопки "Побудувати" і/або "Запустити" які розміщені десь у вікні середовища, і готово! Не потрібно виконувати команди конфігурації, побудови, пошуку виконуваного файлу і його виконання. Усе виконується автоматично самим середовищем автоматичної побудови.

## Запуск з терміналу

### Пошук згенерованого виконуваного бінарного файлу

Для того щоб знайти згенерований виконуваний файл у директорію побудови можна виконати наступну команду пошуку (для GNU/Linux ОС і подібних):

```
find . -name 'CppAppTemplate'
```

Ім'я `CppAppTemplate` являється ім'ям головного виконуваного бінарного файлу за замовчуванням. Його необхідно замінити у разі заміни ім'я за умовчанням у кореневому файлі `CMakeLists.txt` (змінні `PROJECT_NAME` або `PROJECT_BINARY_NAME`).

### Запуск згенерованого виконуваного файлу

Якщо виконуваний бінарний файл скомпільований і наявний у директорії побудови проекту його можна запустити з терміналу використовуючи шлях знайдений з попередньої секції командою:

```
# наприклад, з директорії побудови

./src/CppAppTemplate
```

І ще раз, ім'я `CppAppTemplate` являється ім'ям головного виконуваного бінарного файлу за замовчуванням. Його необхідно замінити у разі заміни ім'я за умовчанням у кореневому файлі `CMakeLists.txt` (змінні `PROJECT_NAME` або `PROJECT_BINARY_NAME`).

## Запуск тестів

### Запуск тестів за допомогою ctest

Якщо розробник увімкнув цілі побудови тестів за допомогою змінної `ENABLE_UNIT_TESTS` і після успішної їх побудови, можна пустити на виконання усі наявні тести з допомогою команди `ctest` з директорії побудови проекту:

```
# run from the project build directory

ctest
```

Як альтернатива, можна виконати команду `ctest` з будь-якого розміщення у файловій системі за допомогою абсолютного шляху до директорії побудови проекту-шаблону (для GNU/Linux ОС і подібних):

```
ctest --tests-dir /шлях/до/директорії/побудови/проекту
```

# Встановлення

Для виконання встановлення необхідно виконати команди інсталяції всередині директорії побудови.

## Встановлення в директорію по замовчуванню

Для того щоб встановити побудований бінарний файл і усі супутні файли у системні директорії по замовчуванню необхідно виконати наступні команди у терміналі (для GNU/Linux):

```
# встановлює побудований бінарний файлу у /usr/local/bin/ наприклад
# виконати з директорії побудови проекту

sudo cmake --install .
```

Зазвичай цільова директорія по замовчуванню є `/usr/local/bin/` (на Unix-подібних системах) яка може бути недоступною у змінній середовища `PATH`.

## Встановлення у директорію по вибору

Для того щоб встановити згенерований бінарний виконуваний файл у доступну для виконання системну директорію необхідно додати параметр `--prefix` до команди, яка показана вище, наприклад:

```
# заміни шлях /usr/bin власним за потреби
# виконувати з директорії побудови проекту

sudo cmake --install . --prefix "/usr/bin"
```

Необхідно переглянути значення змінної середовища `PATH` для обрання найбільш підходящої директорії для встановлення у поточній цільовій ОС (необхідно виконати команду `echo $PATH` у терміналі). Як альтернатива, будь-який шлях може бути вказаний.

## Встановлення документації

Якщо проект був сконфігурований для підтримки встановлення згенерованої документації командою, яка може виглядати наступним чином:

```
# з директорії побудови проекту

cmake ../ -DENABLE_DOC_DOXYGEN=ON -DDOXYGEN_DO_INSTALL=ON
```

Команда інсталяції (наприклад, та яка показана у секції [Встановлення в директорію по замовчуванню](#встановлення-в-директорію-по-замовчуванню)) встановить згенеровану HTML документацію у відповідні директорії.
