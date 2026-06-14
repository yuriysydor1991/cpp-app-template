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

Усі CMake скрипти побудови контейнера для конвеєрів перевірки [Jenkins](https://www.jenkins.io/) розміщуються у файлі з відносним шляхом cmake/dockerers/template-project-docker-Jenkins-pipeline-runner-target.cmake. Відповідний базовий примірник скрипта конвеєра перевірки шаблонного проекту розміщений за відносним шляхом misc/Jenkinsfile котрий повинен бути вказаним для конфігурації конвеєра побудови у Web-панелі [Jenkins](https://www.jenkins.io/). Порт для Web доступу контейнера Docker до конфігурації конвеєрів перевірки [Jenkins](https://www.jenkins.io/) може бути змінено за допомогою встановлення нового значення для CMake-змінної `JENKINS_PIPELINES_PANEL_HTTP_PORT`.

Файл за відносним шляхом cmake/dockerers/template-project-docker-Jenkins-pipeline-runner-target.cmake містить рецепти побудови Docker контейнера для конвеєрів перевірки [Jenkins](https://www.jenkins.io/) що за замовчуванням перезапустить попередньо побудований контейнер для конвеєрів перевірки.

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
