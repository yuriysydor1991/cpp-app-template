## wxWidgets через FetchContent

Бібліотека wxWidgets не вважається встановленою на машині для побудови. Повторно використовуваний модуль `cmake/enablers/template-project-wxwidgets-enabler.cmake` спершу шукає готовий CMake-пакунок wxWidgets, а інакше завантажує і будує його з вихідних кодів за допомогою механізму CMake [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) (побудова з вихідних кодів делегується спільному помічнику `template_project_default_3rdparty_enabler()`). У будь-якому разі він надає цілі `wx::core` та `wx::base`, з якими лінкується компонент.

Поведінкою керують наступні опції і кеш-змінні:

- `ENABLE_WXWIDGETS` (типово `ON`) - встанови `OFF` щоб повністю прибрати інтеграцію з wxWidgets.
- `TEMPLATE_APP_WXWIDGETS_GIT` / `TEMPLATE_APP_WXWIDGETS_GIT_TAG` (типово `v3.3.2`) - репозиторій вихідних кодів і тег (версія) wxWidgets для завантаження; зміни тег щоб будувати з новішим випуском wxWidgets.

Пошук виконується у режимі CONFIG через `find_package(wxWidgets)`: якщо вже доступний CMake-пакунок wxWidgets, що надає цілі `wx::core` / `wx::base` - системне встановлення (наприклад, те, що попередньо встановлюють Dockerfile'и проєкту) або окремий модуль wxWidgets [пакунку Flatpak](/doc/sections/uk_UA/5-11-enabling-the-flatpak-package-generation-support.md) - він використовується як є і нічого не завантажується; інакше wxWidgets завантажується і будується з вихідних кодів. Модуль `FindwxWidgets` з постачання CMake (режим MODULE) навмисно не використовується для пошуку, бо він лише заповнює `wxWidgets_LIBRARIES` і не визначає цих імпортованих цілей.

На GNU/Linux wxWidgets будує свій бекенд GTK, отож для побудови через FetchContent необхідні пакунки розробника GTK (див. секцію [вимог](/doc/sections/uk_UA/3-1-required-tools-for-the-GNU-Linux-based-OS.md)). Перша конфігурація клонує і будує wxWidgets, що може зайняти певний час; наступні конфігурації використовують вже заповнену директорію побудови.
