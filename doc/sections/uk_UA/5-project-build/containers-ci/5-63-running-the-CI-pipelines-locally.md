## Локальний запуск конвеєрів CI

Конвеєри [GitHub Actions](/doc/sections/uk_UA/5-project-build/containers-ci/5-47-the-GitHub-Actions-CI-pipeline.md) та [GitLab CI/CD](/doc/sections/uk_UA/5-project-build/containers-ci/5-48-the-GitLab-CI-pipeline.md) запускаються на кожен push, отож push до віддаленого сховища, яке віддзеркалює проект на обидва сервіси, запускає обидва конвеєри одразу - а конвеєр, зламаний цим push, лишається червоним на обох серверах, доки наступний push його не виправить. Цілі локальних конвеєрів запускають ті самі файли конвеєрів один раз на локальній машині, кожне завдання у власному Docker-контейнері, отож зламаний конвеєр видно ще до push:

| Конвеєр | Інструмент запуску | Параметр CMake | CMake-ціль |
| --- | --- | --- | --- |
| [.github/workflows/ci.yml](/.github/workflows/ci.yml) | [act](https://github.com/nektos/act) | `ENABLE_GITHUB_ACTIONS_DOCKER_PIPELINE` | `github-actions-pipeline-docker-run` |
| [.gitlab-ci.yml](/.gitlab-ci.yml) | [gitlab-ci-local](https://github.com/firecow/gitlab-ci-local) | `ENABLE_GITLAB_CI_DOCKER_PIPELINE` | `gitlab-ci-pipeline-docker-run` |

Обидва інструменти самі читають файли конвеєрів, отож немає другої копії стадій, яку треба тримати узгодженою, а зміна самого файлу конвеєра теж перевіряється:

```
# в середині кореневої директорії проекту

# Конфігурування проекту з підтримкою Docker та обох цілей локальних конвеєрів
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_DOCKER=ON \
  -DENABLE_GITHUB_ACTIONS_DOCKER_PIPELINE=ON -DENABLE_GITLAB_CI_DOCKER_PIPELINE=ON

# Одноразовий запуск кожного конвеєра
cmake --build build --target github-actions-pipeline-docker-run
cmake --build build --target gitlab-ci-pipeline-docker-run
```

Ціль завершується помилкою, коли не вдається хоч одне завдання її конвеєра, так само як конвеєр стає червоним на сервері.

### Вимоги

- [Docker](/doc/sections/uk_UA/3-requirements/3-10-optional-for-docker-container-runs.md), всередині якого виконуються завдання;
- виконуваний файл [act](https://github.com/nektos/act) для конвеєра GitHub Actions;
- виконуваний файл [gitlab-ci-local](https://github.com/firecow/gitlab-ci-local) разом з `rsync`, яким він копіює проект до контейнерів завдань, для конвеєра GitLab CI/CD;
- доступ до мережі, оскільки завдання завантажують свої образи, свої пакунки `apt` та дії (actions) робочого процесу.

Прапорець `--local-pipelines` [скриптів встановлення пакунків](/scripts/packages) встановлює їх усі додатково до пакунків проекту. Жоден дистрибутив не пакує ні `gitlab-ci-local`, ні `act`, отож `gitlab-ci-local` встановлюється з apt-репозиторію його проекту, а `act` з архіву його випуску, перевіреного за контрольними сумами, що їх публікує випуск:

```
# в середині кореневої директорії проекту

scripts/packages/install-debian.sh --local-pipelines
```

Скрипт [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) так само приймає цей прапорець. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) встановлює обидва інструменти з архівів їхніх випусків, а на RHEL та його перезбірках, які не мають Docker, ще й Docker з репозиторію сайту Docker. Вже встановлений Docker - `docker-ce` з сайту Docker чи snap - залишається як є. Щойно встановлений сервіс Docker все ще потребує [налаштування](/doc/sections/uk_UA/3-requirements/3-10-optional-for-docker-container-runs.md), яке відкриває доступ до нього звичайному користувачу. FreeBSD не має рушія Docker для Linux-контейнерів завдань, тож скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) відхиляє цей прапорець.

Крок конфігурації зупиняється з повідомленням, що називає відсутній інструмент, отож нічого не запускається наполовину.

### Перевіряється закомічена вершина гілки

Кожен запуск клонує закомічену вершину поточної гілки до власного робочого простору всередині директорії побудови - `github-actions-pipeline-workspace` та `gitlab-ci-pipeline-workspace` - і запускає конвеєр там, отож перевіряє саме те, що публікує push:

- незакомічені зміни лишаються поза запуском - запуск перелічує їх у попередженні - тож закомітьте їх перед запуском;
- невідстежувані файли та дерева побудови вихідного дерева не потрапляють до контейнерів завдань;
- стан, журнали та артефакти, які лишають по собі інструменти запуску, лишаються поза вихідним деревом.

Клон знімається на кроці побудови, отож коміти, зроблені після кроку конфігурації, теж потрапляють до запуску. CMake-змінна `LOCAL_PIPELINE_BRANCH` обирає іншу локальну гілку, отож одна робоча копія запускає конвеєри будь-якої гілки шаблону без власного перемикання гілки - від'єднаний HEAD теж мусить назвати свою гілку саме так:

```
# в середині кореневої директорії проекту

scripts/docker/pipelines-run.sh -DLOCAL_PIPELINE_BRANCH=appQt6
```

Файли конвеєрів теж беруться з клонованої гілки, отож запуск бере рядок `DEPENDENCIES` саме цієї гілки.

### Образ виконавця GitHub Actions

Інструмент `act` запускає кожне завдання у контейнері образу, зіставленого з міткою `runs-on` завдання. Мітка зчитується з робочих процесів гілки, а ціль `github-actions-pipeline-docker-build` будує образ [misc/Dockerfiles/Dockerfile.GitHub.Actions.pipeline.in](/misc/Dockerfiles/Dockerfile.GitHub.Actions.pipeline.in) поверх образу `ubuntu` того самого випуску - `ubuntu:26.04` для виконавця `ubuntu-26.04`, того самого образу, всередині якого виконується конвеєр GitLab CI/CD.

Образ виконавця GitHub містить сотні попередньо встановлених інструментів, тоді як завдання шаблону встановлюють свій набір інструментів самостійно, отож локальний образ містить лише те, що робочий процес вважає наявним: `sudo`, через який завдання викликають `apt-get`, `git` перевірки clang-format та середовище Node.js 24 для дій на JavaScript. Завдання, яке покладається на інструмент, що випадково встановлений у виконавці GitHub, локально завершиться помилкою, отож локальний запуск суворіший з двох.

Кожен шар образу кешується, отож після першого запуску побудова триває секунди. CMake-змінна `GITHUB_ACTIONS_PIPELINE_FORCE_REBUILD` будує його наново з повторно завантаженим базовим образом і без використання кешу.

Звіти JUnit, які вивантажує завдання `Debug build & tests`, потрапляють до директорії `github-actions-pipeline-artifacts` директорії побудови - сховища сервера артефактів `act`.

### Запуск GitLab CI/CD

Інструмент `gitlab-ci-local` бере образ завдань безпосередньо з [.gitlab-ci.yml](/.gitlab-ci.yml), отож власний образ не будується. Конвеєр запускається як конвеєр гілки, оскільки правила `workflow` бачать гілку, яку містить робочий простір.

Звіти JUnit `reports` завдання `build-and-test` не мають локального відповідника, оскільки інструмент повертає лише `artifacts:paths` завдання - натомість невдалий тест друкується до журналу завдання викликом `ctest --output-on-failure`.

### Параметри

| CMake-змінна | Типове значення | Що робить |
| --- | --- | --- |
| `LOCAL_PIPELINE_BRANCH` | поточна гілка | локальна гілка, закомічену вершину якої перевіряють обидва конвеєри |
| `LOCAL_PIPELINE_RUN_CPPCHECK` | `OFF` | встановлює вхідний параметр `run_cppcheck` конвеєра GitHub Actions та змінну `RUN_CPPCHECK` конвеєра GitLab CI/CD, що запускають їхню стадію `cppcheck` |
| `LOCAL_PIPELINE_MAX_PARALLEL_JOBS` | усі завдання одразу | кількість завдань, які запуск стартує одночасно - кожне завдання будує усіма ядрами машини самостійно, отож чотири завдання конвеєра навантажують машину вчетверо |
| `GITHUB_ACTIONS_PIPELINE_JOB` | усі завдання | єдиний ідентифікатор завдання, яким обмежується запуск GitHub Actions, наприклад `code-format` |
| `GITLAB_CI_PIPELINE_JOBS` | усі завдання | розділені пробілами назви завдань, якими обмежується запуск GitLab CI/CD, наприклад `code-format release` |
| `GITHUB_ACTIONS_PIPELINE_FORCE_REBUILD` | `OFF` | будує образ виконавця наново, див. вище |
| `GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL` | та, яку називають робочі процеси | мітка `runs-on`, яку заміщує образ виконавця, обов'язкова, коли робочі процеси гілки називають більше однієї |
| `GITHUB_ACTIONS_PIPELINE_NODE_MAJOR` | `24` | лінійка випусків Node.js образу виконавця |

### Скрипти запуску

Директорія [scripts/docker](/scripts/docker) містить скорочення, які виконують обидва наведені вище кроки конфігурації та побудови, отож запуск виконується однією командою:

| Скрипт | Запускає CMake-ціль |
| --- | --- |
| [pipelines-run.sh](/scripts/docker/pipelines-run.sh) | `github-actions-pipeline-docker-run`, потім `gitlab-ci-pipeline-docker-run` |
| [github-actions-run.sh](/scripts/docker/github-actions-run.sh) | `github-actions-pipeline-docker-run` |
| [github-actions-build.sh](/scripts/docker/github-actions-build.sh) | `github-actions-pipeline-docker-build` |
| [gitlab-ci-run.sh](/scripts/docker/gitlab-ci-run.sh) | `gitlab-ci-pipeline-docker-run` |

```
# в середині кореневої директорії проекту

# обидва конвеєри - перевірка перед push
scripts/docker/pipelines-run.sh

# лише перевірка clang-format конвеєра GitHub Actions
scripts/docker/github-actions-run.sh -DGITHUB_ACTIONS_PIPELINE_JOB=code-format

# конвеєр GitLab CI/CD з його необов'язковою стадією cppcheck
scripts/docker/gitlab-ci-run.sh -DLOCAL_PIPELINE_RUN_CPPCHECK=ON
```

Кожен з них конфігурує директорію `build/release` з параметром `ENABLE_DOCKER` та параметром свого конвеєра у значенні `ON` і потім будує потрібну ціль, отож жодної власної команди `docker`, `act` чи `gitlab-ci-local` не виконується. Скрипти приймають ті ж самі параметри, що і [Швидкі скрипти побудови](/doc/sections/uk_UA/5-project-build/5-36-quick-build-scripts.md), оскільки саме їх вони і викликають. Скрипт [pipelines-run.sh](/scripts/docker/pipelines-run.sh) зупиняється на першому невдалому конвеєрі, а прапорець `--rebuild` скриптів, що запускають конвеєр GitHub Actions, встановлює CMake-змінну `GITHUB_ACTIONS_PIPELINE_FORCE_REBUILD`:

```
# в середині кореневої директорії проекту

scripts/docker/github-actions-run.sh --rebuild
```

### Чим локальний запуск відрізняється від віддаленого

- `act` виконує завдання від імені користувача `root`, тоді як виконавець GitHub виконує їх від імені непривілейованого користувача з `sudo`, отож тест, який розраховує на заборонений доступ до файлу, поводиться інакше;
- запуск одноразовий, отож скасуванню застарілих конвеєрів - групі `concurrency` робочого процесу та завданням `interruptible` конвеєра GitLab CI/CD - нічого скасовувати;
- перевірки шаблону та перевірки пакувальників з [misc/Jenkinsfile](/misc/Jenkinsfile) лишаються за [контейнером конвеєра Jenkins](/doc/sections/uk_UA/5-project-build/containers-ci/5-17-enabling-Jenkins-pipeline-inside-Docker-container.md), так само як і на віддалених серверах.
