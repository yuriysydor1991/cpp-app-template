## Конвеєр CI/CD GitLab

Конвеєр [.gitlab-ci.yml](/.gitlab-ci.yml) повторює стадії побудови, тестування та перевірки коду конвеєра [misc/Jenkinsfile](/misc/Jenkinsfile) у [GitLab CI/CD](https://docs.gitlab.com/ci/), отож відгалуження проекту на [GitLab](https://gitlab.com/) отримує ті самі перевірки без власного примірника [Jenkins](https://www.jenkins.io/). Вмикати для цього нічого не потрібно: конвеєр запускається на кожен push та на кожен merge request, а також вручну зі сторінки *Pipelines* проекту. Його правила `workflow` тримають один push при одному конвеєрі - конвеєрі merge request, доки той відкритий, та конвеєрі гілки в іншому разі.

Його завдання поділяють єдину стадію `check`, отож усі виконуються паралельно, кожне у власному контейнері:

| Завдання | Що виконує |
| --- | --- |
| `code-format` | конфігурує з `-DENABLE_CLANGFORMAT=ON`, будує ціль `clang-format` і завершується помилкою, коли форматувальник змінив хоч один відстежуваний файл |
| `build-and-test` | конфігурує побудову Debug із санітайзерами, юніт- та компонентними тестами, будує її та запускає набори `UTEST_` та `CTEST_` через `ctest` |
| `clang-tidy` | конфігурує з `-DENABLE_CLANG_TIDY=ON` і будує, отож перевірки виконуються під час компіляції |
| `release` | будує конфігурацію Release та встановлює її до префіксу всередині каталогу побудови |

Кожен запуск `ctest` записує звіт JUnit XML, який завдання передає GitLab як свій звіт тестування, тож невдалий тест видно на вкладці *Tests* сторінки конвеєра без читання журналів. Завдання позначені `interruptible`, отож новий push до гілки скасовує ще не завершений конвеєр її попереднього коміту, доки в проекті увімкнено налаштування *Auto-cancel redundant pipelines*.

### Образ та залежності гілки

Завдання виконуються всередині образу [ubuntu:26.04](https://hub.docker.com/_/ubuntu) - того самого випуску, до якого прив'язаний виконавець [робочого процесу GitHub Actions](/doc/sections/uk_UA/5-project-build/containers-ci/5-47-the-GitHub-Actions-CI-pipeline.md), отож обидва конвеєри беруть ті самі пакунки. Образ містить голу систему, отож завдання встановлює увесь свій набір інструментів самотужки єдиним рядком `apt-get install` у `before_script`: `TOOLS`, потрібні кожному завданню, `JOB_TOOLS` самого завдання та `DEPENDENCIES` гілки:

```
variables:
  BUILDDIR: build
  BDJUNITOUT: junit-out
  # The tools every job needs on top of the bare image.
  TOOLS: build-essential cmake g++ git ca-certificates pkg-config
  # The development packages of the branch specific libraries.
  DEPENDENCIES: libasound2-dev libsamplerate0-dev libudev-dev libgles-dev libxcursor-dev libxi-dev libxrandr-dev libxss-dev
```

Саме остання змінна - єдиний рядок, яким різняться гілки шаблону, отож проект, який долучає власну бібліотеку, дописує туди її пакунок розробки.

### Параметри ручного запуску

Сторінка *Run pipeline* проекту запускає конвеєр із попередньо заповненими змінними, що віддзеркалюють параметри [misc/Jenkinsfile](/misc/Jenkinsfile):

| Змінна | Відповідник у Jenkins | Що запускає |
| --- | --- | --- |
| `RUN_CPPCHECK` | `RUN_CPPCHECK` | побудову цілі `cppcheck` у завданні `build-and-test` |

Типово лишається `false`, оскільки перевірка коштує хвилин часу виконавця, за які платив би кожен push.

### Що лишається конвеєру Jenkins

Перевірки шаблону з [misc/Jenkinsfile](/misc/Jenkinsfile) - розділи документації та їхні посилання у README, посилання markdown, зовнішні URL документації, зареєстровані enabler-модулі та зареєстровані тести - не мають тут відповідника, як і його перевірки пакувальників: конвеєр обмежується стадіями, які покриває звичайний контейнер, тоді як пакувальники потребують середовищ виконання та інструментів, які містить [контейнер конвеєра Jenkins](/doc/sections/uk_UA/5-project-build/containers-ci/5-17-enabling-Jenkins-pipeline-inside-Docker-container.md).
