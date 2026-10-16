## Вмикання інтеграції бібліотеки liboai

Неофіційна C++17 бібліотека [liboai](https://github.com/d7ead/liboai) для [OpenAI API](https://platform.openai.com/docs/api-reference/chat) вмикається у цій гілці CMake-змінною `ENABLE_LIBOAI`, яка за замовчуванням має значення `ON`. Бібліотека є обов'язковою для гілки, адже програма звертається до ChatGPT саме через неї, тому крок конфігурування CMake зупиняється з помилкою, якщо змінній встановлено значення `OFF`. Щоб побудувати проект без неї, видаліть директорію `src/liboai` разом з її використанням у класах `app::Application` та `app::ApplicationHelpPrinter`.

Використовується встановлена у системі бібліотека, якщо її знайдено, інакше береться копія з git-репозиторію. Сам репозиторій та його теґ задаються CMake-змінними `TEMPLATE_APP_LIBOAI_GIT` та `TEMPLATE_APP_LIBOAI_GIT_TAG`:

```
cmake -S . -B build -DTEMPLATE_APP_LIBOAI_GIT_TAG=main
```

Бібліотека запитує пакети libcurl та nlohmann JSON командою `find_package`. Встановлені у системі використовуються, якщо їх знайдено, як описано у секції [Необхідні пакети для liboai](/doc/sections/uk_UA/3-requirements/3-12-required-packages-for-the-liboai.md), а кожен відсутній завантажується з git-репозиторію та теґу, заданих CMake-змінними `TEMPLATE_APP_CURL_GIT`/`TEMPLATE_APP_CURL_GIT_TAG` (libcurl) або `TEMPLATE_APP_NLOHMANN_GIT`/`TEMPLATE_APP_NLOHMANN_GIT_TAG` (nlohmann JSON). Завантажені копії доходять до викликів `find_package` бібліотеки liboai лише з CMake версії 3.24 або новішим.

### Запит до ChatGPT

Згенерований виконуваний файл ставить [ChatGPT](https://openai.com/chatgpt/) питання, задане параметром командного рядка `--question` (або `-q`), і виводить отриману відповідь:

```
./build/src/CppAppTemplate --token <ваш-токен-openai-api> --question "У чому сенс податків?"
```

Токен береться зі змінної середовища `OPENAI_API_KEY`, якщо параметр `--token` (або `-t`) не задано, що тримає його поза командним рядком процесу, видимим кожному користувачу машини:

```
export OPENAI_API_KEY=<ваш-токен-openai-api>

./build/src/CppAppTemplate --question "У чому сенс податків?"
```

За замовчуванням запитується модель `gpt-4o-mini`. Будь-яка інша, доступна для використаного токена, задається параметром `--model` (або `-m`):

```
./build/src/CppAppTemplate --model gpt-4o --question "У чому сенс податків?"
```

Виконуваний файл завершується з ненульовим статусом і описом помилки, якщо токен відхилено або відповіді не отримано. Без питання він лише виводить підказку про те, як його задати, тому компонентні тести проходять і без доступного токена.

### Структура підсистеми

Клас `liboaii::OAIController` з директорії `src/liboai` загортає бібліотеку: він приймає токен (методи `set_token` та `set_token_from_env`) і ставить одне питання методом `ask`, перетворюючи винятки бібліотеки на записані у журнал помилки та порожню відповідь. Клас `app::Application` керує ним за значеннями, які клас `app::CommandLineParser` розміщує в екземплярі `app::ApplicationContext`.
