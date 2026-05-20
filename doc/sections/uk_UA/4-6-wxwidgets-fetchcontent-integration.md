## wxWidgets через FetchContent

Бібліотека wxWidgets не вважається встановленою на машині для побудови. Тому повторно використовуваний модуль `cmake/enablers/template-project-wxwidgets-enabler.cmake` завантажує і будує wxWidgets з вихідних кодів за допомогою механізму CMake [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) і надає цілі `wx::core` та `wx::base`, з якими лінкується компонент.

Поведінкою керують наступні опції і кеш-змінні:

- `ENABLE_WXWIDGETS` (типово `ON`) - встанови `OFF` щоб повністю прибрати інтеграцію з wxWidgets.
- `WXWIDGETS_TRY_SYSTEM_PROBE` (типово `ON`) - якщо у системі вже встановлено wxWidgets з підтримкою CMake-пакету, він використовується як є і нічого не завантажується.
- `TEMPLATE_APP_WXWIDGETS_GIT` / `TEMPLATE_APP_WXWIDGETS_GIT_TAG` - репозиторій вихідних кодів і тег (версія) wxWidgets для завантаження; зміни тег щоб будувати з новішим випуском wxWidgets.

На GNU/Linux wxWidgets будує свій бекенд GTK, отож для побудови через FetchContent необхідні пакунки розробника GTK (див. секцію [вимог](/doc/sections/uk_UA/3-1-required-tools-for-the-GNU-Linux-based-OS.md)). Перша конфігурація клонує і будує wxWidgets, що може зайняти певний час; наступні конфігурації використовують вже заповнену директорію побудови.
