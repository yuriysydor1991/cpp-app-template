## Вмикання конвеєра Jenkins всередині Docker контейнера

Для того щоб увімкнути підтримку конвеєра [Jenkins](https://www.jenkins.io/) всередині спеціально виділеного Docker контейнера необхідно побудувати ціль `jenkins-pipeline-docker-run` за допомогою команд:

```
# в середині кореневої директорії проекту

# Конфігурування проекту для підтримки цілей Docker разом з Jenkins
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_DOCKER=ON -DENABLE_JENKINS_DOCKER_PIPELINE=ON

# Побудова і запуск контейнера для конвеєрів Jenkins
# або його перезапуск
cmake --build build --target jenkins-pipeline-docker-run
```

Після чого необхідно знайти і запам'ятати пароль до [Jenkins](https://www.jenkins.io/) Web-інтерфейсу у логах першого запуску Jenkins системи, який може виглядати наступним чином:

```
# ...

*************************************************************
*************************************************************
*************************************************************

Jenkins initial setup is required. An admin user has been created and a password generated.
Please use the following password to proceed to installation:

aefdc6a4a2214c298c821236c739165c

This may also be found at: /var/jenkins_home/secrets/initialAdminPassword

*************************************************************
*************************************************************
*************************************************************

# ...
```

Необхідно відвідати локальну адресу `http://127.0.0.1:8080` (порт може змінюватись) за допомогою використовуваного браузера щоб завершити початкову інсталяцію і конфігурацію [Jenkins](https://www.jenkins.io/) системи на Web-сторінках його GUI.

Після успішної інсталяції і конфігурації [Jenkins](https://www.jenkins.io/) необхідно створити відповідний конвеєр перевірки проекту всередині Web-панелі [Jenkins](https://www.jenkins.io/).

Усі CMake скрипти побудови контейнера для конвеєрів перевірки [Jenkins](https://www.jenkins.io/) розміщуються у файлі з відносним шляхом cmake/enablers/dockerers/template-project-docker-Jenkins-pipeline-runner-target.cmake. Відповідний базовий примірник скрипта конвеєра перевірки шаблонного проекту розміщений за відносним шляхом misc/Jenkinsfile котрий повинен бути вказаним для конфігурації конвеєра побудови у Web-панелі [Jenkins](https://www.jenkins.io/). Порт для Web доступу контейнера Docker до конфігурації конвеєрів перевірки [Jenkins](https://www.jenkins.io/) може бути змінено за допомогою встановлення нового значення для CMake-змінної `JENKINS_PIPELINES_PANEL_HTTP_PORT`.

Файл за відносним шляхом cmake/enablers/dockerers/template-project-docker-Jenkins-pipeline-runner-target.cmake містить рецепти побудови Docker контейнера для конвеєрів перевірки [Jenkins](https://www.jenkins.io/) що за замовчуванням перезапустить попередньо побудований контейнер для конвеєрів перевірки.

### Вміст образу

Образ доповнює `jenkins/jenkins:lts` усім, що потребують конвеєри перевірки кожної гілки шаблонного проекту, отож один контейнер обслуговує їх усі:

- інструментарій і аналізатори: `build-essential`, `cmake`, `meson` разом з `ninja-build`, `clang-format`, `clang-tidy`, `cppcheck`, `valgrind`, `doxygen` разом з `graphviz` та пакунки розробки GoogleTest і GoogleMock;
- пакунки розробки кожної бібліотеки, з якою компонується гілка - Qt6 разом з модулями QML, QtCharts, Qt Location та WebView / WebEngine, Gtkmm-3 і Gtkmm-4 разом з libadwaita та WebKitGTK, SDL2, SDL3, SFML, FreeGLUT, Vulkan, OpenCV, CFITSIO разом з WCSLIB, PLplot, giza, Boost, libcurl, nlohmann JSON, PostgreSQL, MySQL, Firebird та інші;
- бібліотеки, для яких дистрибутив не постачає пакунка, побудовані з їх первинних джерел: wxWidgets, Wt, SQLiteCpp, драйвери MongoDB для C і C++, MatPlot++ та sdbus-c++;
- пакувальники: `flatpak` разом з `flatpak-builder`, `appimagetool`, `rpm` та `dpkg-dev` зі складу `build-essential`.

Пакувальники snap, FreeBSD pkg та WIX MSI залишились поза образом: перший потребує власних systemd та LXD, другий - `cpack`, зібраного з `libpkg`, а третій - хоста MS Windows.

### Перевірки пакувальників

Параметри побудови `RUN_FLATPAK_PACKAGER`, `RUN_APPIMAGE_PACKAGER`, `RUN_DEB_PACKAGER` та `RUN_RPM_PACKAGER` конвеєра [misc/Jenkinsfile](/misc/Jenkinsfile) будують пакунок і завершують побудову невдачею, якщо файл пакунка не з'явився, отож контейнер перевіряє пакувальники гілки так само, як перевіряє її тести. Усі вони вимкнені за замовчуванням - потрібні вмикаються на сторінці *Build with Parameters* відповідного завдання.

`flatpak-builder` виконує побудову всередині пісочниці [bubblewrap](https://github.com/containers/bubblewrap), а середовище виконання AppImage монтує себе через FUSE, що заборонено типовими профілями контейнера, отож ціль `jenkins-pipeline-docker-run` запускає контейнер із пристроєм `/dev/fuse`, можливістю `SYS_ADMIN` та незабороняючими профілями seccomp і AppArmor.

Кожна пара середовища виконання та SDK, яку називають flatpak-маніфести гілок, встановлюється до образу, отож жоден запуск конвеєра не завантажує їх повторно. Цей перелік є CMake-змінною `JENKINS_PIPELINE_FLATPAK_RUNTIMES`, і кожна пара коштує образу гігабайтів, отож його варто скоротити до потрібних гілок:

```
# в середині кореневої директорії проекту

scripts/docker/jenkins-run.sh \
  -DJENKINS_PIPELINE_FLATPAK_RUNTIMES="org.freedesktop.Platform//24.08 org.freedesktop.Sdk//24.08"
```

Вони потрапляють до користувацької інсталяції користувача `jenkins` - тієї самої, з якою працює ціль `flatpak` кожної гілки, - котру змінна оточення `FLATPAK_USER_DIR` образу утримує за шляхом `/var/flatpak`, поза томом `/var/jenkins_home`, який відкидав би її при кожному запуску контейнера.

### Швидкодія побудови образу і конвеєрів

- увесь набір пакунків встановлюється однією транзакцією `apt`, а кеші BuildKit зберігають архіви і переліки пакунків, отож повторна побудова образу перевстановлює їх без повторного завантаження;
- кожна побудована з джерел бібліотека клонується поверхнево, будується і стирається в межах одного шару, отож ані джерела, ані дерева побудови не потрапляють до образу;
- образ містить `ccache` і спрямовує до нього змінні оточення `CMAKE_C_COMPILER_LAUNCHER` та `CMAKE_CXX_COMPILER_LAUNCHER`, отож крок конфігурування кожної гілки підхоплює його, а повторні побудови конвеєра перетворюються на влучання в кеш;
- вбудований вузол утримує двох виконавців, отож паралельні стадії тестів конвеєра справді виконуються паралельно, а побудови цих двох усе ще залишають робочу машину придатною до використання;
- побудова образу отримує порожню директорію як свій контекст і бере експортовані завдання з дерева, що конфігурується, отож ані двійкове дерево не передається до служби Docker, ані клон опублікованої гілки не потрібен.

### Експортування та імпортування конфігурацій завдань Jenkins

Встановлення значення `ON` для CMake-змінної `JENKINS_CLI_JAR_TARGETS` вмикає керування завданнями [Jenkins](https://www.jenkins.io/) за допомогою клієнта [Jenkins CLI](https://www.jenkins.io/doc/book/managing/cli/). Повний шлях до клієнта `jenkins-cli.jar` (котрий можна завантажити з Web-панелі запущеної системи [Jenkins](https://www.jenkins.io/)) необхідно вказати у CMake-змінній `JENKINS_CLI_JAR_PATH` разом із обліковими даними `JENKINS_CLI_LOGIN` та `JENKINS_CLI_SECRET`. Під час кроку конфігурування CMake кожне завдання запущеного примірника [Jenkins](https://www.jenkins.io/) експортуватиметься як XML-конфігурація у файли `<build>/Jenkins-exported-jobs/<назва-завдання>.xml`.

Експортовані XML-конфігурації завдань можуть бути імпортовані назад до сервера [Jenkins](https://www.jenkins.io/) додатковим встановленням значення `ON` для CMake-змінної `JENKINS_CLI_IMPORT_JOBS`:

```
# в середині кореневої директорії проекту
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_DOCKER=ON \
    -DJENKINS_CLI_JAR_TARGETS=ON -DJENKINS_CLI_IMPORT_JOBS=ON \
    -DJENKINS_CLI_JAR_PATH=/шлях/до/jenkins-cli.jar \
    -DJENKINS_CLI_LOGIN=admin -DJENKINS_CLI_SECRET=пароль \
    -DJENKINS_IMPORT_SERVER_URL=http://127.0.0.1:8080/
```

Під час кроку конфігурування CMake кожен файл `*.xml` із директорії, вказаної у CMake-змінній `JENKINS_IMPORT_JOBS_DIR` (за замовчуванням директорія експорту `<build>/Jenkins-exported-jobs`), імпортується до цільового сервера [Jenkins](https://www.jenkins.io/), вказаного у CMake-змінній `JENKINS_IMPORT_SERVER_URL` (за замовчуванням локальний контейнер конвеєра за адресою `http://127.0.0.1:${JENKINS_PIPELINES_PANEL_HTTP_PORT}/`). Відсутнє на цільовому сервері завдання створюється, а вже наявне — оновлюється, тому цільовий сервер [Jenkins](https://www.jenkins.io/) може відрізнятися від того, з якого завдання було експортовано. Відповідний CMake-скрипт розміщений за відносним шляхом cmake/enablers/dockerers/template-project-docker-Jenkins-import-jobs-from-xml.cmake.

### Скрипти запуску

Директорія [scripts/docker](/scripts/docker) містить скорочення, які виконують обидві наведені вище команди, отож увесь запуск виконується однією командою:

| Скрипт | Запускає CMake-ціль |
| --- | --- |
| [jenkins-run.sh](/scripts/docker/jenkins-run.sh) | `jenkins-pipeline-docker-run` |
| [jenkins-build.sh](/scripts/docker/jenkins-build.sh) | `jenkins-pipeline-docker-build` |

```
# в середині кореневої директорії проекту

scripts/docker/jenkins-run.sh
```

Кожен з них конфігурує директорію `build/release` з параметрами `ENABLE_DOCKER` і `ENABLE_JENKINS_DOCKER_PIPELINE` у значенні `ON` і потім будує потрібну ціль, отож жодної власної команди `docker` не виконується. CMake-ціль `jenkins-pipeline-docker-run` залежить від цілі `jenkins-pipeline-docker-build`, а отже скрипт [jenkins-run.sh](/scripts/docker/jenkins-run.sh) будує і образ теж, а скрипт [jenkins-build.sh](/scripts/docker/jenkins-build.sh) потрібен лише для побудови образу без запуску інтерактивного контейнера.

Скрипти приймають ті ж самі параметри, що і [Швидкі скрипти побудови](/doc/sections/uk_UA/5-project-build/5-36-quick-build-scripts.md), оскільки саме їх вони і викликають:

```
# в середині кореневої директорії проекту

# зміна порту Web-панелі Jenkins у контейнері
scripts/docker/jenkins-run.sh -DJENKINS_PIPELINES_PANEL_HTTP_PORT=9090
```

Рішення про повторне використання чи перебудову вже побудованого образу і вже створеного контейнера приймає CMake-скрипт на кроці конфігурації, отож параметр `--no-reconfigure` зберігає рішення попереднього запуску конфігурації.

Прапорець `--rebuild` обох скриптів встановлює CMake-змінну `JENKINS_PIPELINE_FORCE_REBUILD`, котра стирає контейнер і образ та будує образ наново із повторно завантаженим базовим образом Dockerfile і без використання кешу побудови, отож нічого від попереднього образу не залишається:

```
# в середині кореневої директорії проекту

scripts/docker/jenkins-run.sh --rebuild
```

Прапорець `--renew-container` скрипта [jenkins-run.sh](/scripts/docker/jenkins-run.sh) встановлює CMake-змінну `JENKINS_PIPELINE_RENEW_CONTAINER`, котра зупиняє і стирає лише контейнер, залишає образ незмінним та запускає новий контейнер із нього, отож конвеєр отримує домівку Jenkins свіжого контейнера без годин, потрібних на побудову образу:

```
# в середині кореневої директорії проекту

scripts/docker/jenkins-run.sh --renew-container
```
