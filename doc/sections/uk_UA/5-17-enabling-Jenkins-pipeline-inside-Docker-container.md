## Вмикання конвеєра Jenkins всередині Docker контейнера

Для того щоб увімкнути підтримку конвеєра [Jenkins](https://www.jenkins.io/) всередині спеціально виділеного Docker контейнера необхідно побудувати ціль `jenkins-pipeline-docker-run` за допомогою команд:

```
# в середині кореневої директорії проекту

# Конфігурування проекту для підтримки цілей Docker разом з Jenkins
meson setup build -DENABLE_DOCKER=true -DENABLE_JENKINS_DOCKER_PIPELINE=true

# Побудова і запуск контейнера для конвеєрів Jenkins
# або його перезапуск
meson compile -C build jenkins-pipeline-docker-run
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

Після успішної інсталяції і конфігурації [Jenkins](https://www.jenkins.io/) необхідно створити у його Web-панелі завдання типу *Pipeline* з визначенням *Pipeline script from SCM*, вказати репозиторій та гілку проекту і встановити *Script Path* у значення `misc/Jenkinsfile`.

Усі Meson скрипти побудови контейнера для конвеєрів перевірки [Jenkins](https://www.jenkins.io/) розміщуються у файлі [meson/enablers/dockerers/template-project-docker-Jenkins-pipeline-runner-target/meson.build](/meson/enablers/dockerers/template-project-docker-Jenkins-pipeline-runner-target/meson.build). Порт для Web доступу контейнера Docker до конфігурації конвеєрів перевірки [Jenkins](https://www.jenkins.io/) може бути змінено за допомогою встановлення нового значення для Meson-параметра `JENKINS_PIPELINES_PANEL_HTTP_PORT`.

Цілі шукають образ і контейнер при кожному своєму запуску, отож повторна побудова цілі `jenkins-pipeline-docker-run` використовує вже побудований образ і перезапускає попередньо створений контейнер.

### Скрипти запуску

Директорія [scripts/docker](/scripts/docker) містить скорочення, які виконують обидві наведені вище команди, отож увесь запуск виконується однією командою:

| Скрипт | Запускає Meson-ціль |
| --- | --- |
| [jenkins-run.sh](/scripts/docker/jenkins-run.sh) | `jenkins-pipeline-docker-run` |
| [jenkins-build.sh](/scripts/docker/jenkins-build.sh) | `jenkins-pipeline-docker-build` |

```
# в середині кореневої директорії проекту

scripts/docker/jenkins-run.sh
```

Кожен з них конфігурує директорію `build/release` з параметрами `ENABLE_DOCKER` і `ENABLE_JENKINS_DOCKER_PIPELINE` у значенні `true` і потім будує потрібну ціль, отож жодної власної команди `docker` не виконується. Meson-ціль `jenkins-pipeline-docker-run` залежить від цілі `jenkins-pipeline-docker-build`, а отже скрипт [jenkins-run.sh](/scripts/docker/jenkins-run.sh) будує і образ теж, а скрипт [jenkins-build.sh](/scripts/docker/jenkins-build.sh) потрібен лише для побудови образу без запуску інтерактивного контейнера.

Усі додаткові параметри скриптів передаються кроку `meson setup`, тоді як їхній прапорець `--rebuild` встановлює Meson-параметр `JENKINS_PIPELINE_FORCE_REBUILD`, котрий стирає контейнер і образ та будує образ наново із повторно завантаженим базовим образом Dockerfile і без використання кешу побудови, отож нічого від попереднього образу не залишається:

```
# в середині кореневої директорії проекту

scripts/docker/jenkins-run.sh --rebuild
```

Контейнер публікує порт Web-панелі під час свого створення, отож нове значення `JENKINS_PIPELINES_PANEL_HTTP_PORT` дістається вже створеного контейнера лише разом з прапорцем `--rebuild`:

```
# в середині кореневої директорії проекту

# зміна порту Web-панелі Jenkins у контейнері
scripts/docker/jenkins-run.sh --rebuild -DJENKINS_PIPELINES_PANEL_HTTP_PORT=9090
```

### Інструменти контейнера

Образ [misc/Dockerfile.Jenkins.pipeline.meson](/misc/Dockerfile.Jenkins.pipeline.meson) містить інструменти, які викликають стадії [misc/Jenkinsfile](/misc/Jenkinsfile): `git`, `meson` разом з `ninja-build`, `g++`, `pkg-config`, пакети розробки GoogleTest / GoogleMock, `clang-format`, `clang-tidy` та `cppcheck`, а також інструменти необов'язкових стадій пакувальників, які постачає його базовий дистрибутив Debian: `rpm` для стадії `RUN_RPM_PACKAGER` (стадії `RUN_DEB_PACKAGER` потрібен лише `dpkg-deb`, наявний на кожній системі на базі Debian) та `doxygen` разом з `graphviz` для побудови документації. Стадії `RUN_FREEBSD_PACKAGER` та `RUN_WIX_PACKAGER` призначені лише для FreeBSD та MS Windows відповідно.

Те саме завдання виконується і на власному примірнику [Jenkins](https://www.jenkins.io/), якщо його агент має наведені вище інструменти - інструменти стадій побудови, тестування та перевірки коду встановлюють скрипти встановлення пакетів [scripts/packages](/scripts/packages).
