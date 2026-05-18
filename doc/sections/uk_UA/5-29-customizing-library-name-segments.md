## Налаштування складових імені встановлюваної бібліотеки

Імʼя бібліотеки, яке бачать проекти-споживачі (бінарник бібліотеки, субдиректорія
`include/<name>/` для публічних заголовків, файл pkg-config і директорія CMake
package з простором імен імпортованої цілі) виводиться з трьох опціональних
Meson-опцій. Вони дозволяють паралельним встановленням різних версій бібліотеки
співіснувати у системі - наприклад `include/CppAppTemplate-0.11.0-dev/` поруч з
`include/CppAppTemplate-0/`.

| Опція | За замовчуванням | Ефект |
|---|---|---|
| `-DLIB_INCLUDE_MINOR_IN_NAME=true` | `false` | Додає `.<minor>` до імені бібліотеки |
| `-DLIB_INCLUDE_MICRO_IN_NAME=true` | `false` | Додає `.<micro>` (вмикає прапорець minor неявно) |
| `-DLIB_NAME_SUFFIX='-dev'` | `''` | Додає довільний завершальний суфікс |

Приклади імен бібліотеки для проекту `0.11.0`:

| Прапорці конфігурації | Імʼя бібліотеки |
|---|---|
| (немає) | `CppAppTemplate-0` |
| `-DLIB_INCLUDE_MINOR_IN_NAME=true` | `CppAppTemplate-0.11` |
| `-DLIB_INCLUDE_MINOR_IN_NAME=true -DLIB_INCLUDE_MICRO_IN_NAME=true` | `CppAppTemplate-0.11.0` |
| `-DLIB_NAME_SUFFIX='-dev'` | `CppAppTemplate-0-dev` |
| `-DLIB_INCLUDE_MINOR_IN_NAME=true -DLIB_INCLUDE_MICRO_IN_NAME=true -DLIB_NAME_SUFFIX='-dev'` | `CppAppTemplate-0.11.0-dev` |

Однакове імʼя послідовно використовується для кожного встановлюваного артефакту:

- `<libdir>/lib<NAME>.so.<version>` (бінарник спільної бібліотеки),
- `<prefix>/include/<NAME>/*.h` (субдиректорія публічних заголовків),
- `<libdir>/pkgconfig/<NAME>.pc` (файл pkg-config - проекти-споживачі на Meson використовують `dependency('<NAME>')`),
- `<libdir>/cmake/<NAME>/` + імпортована ціль `<NAME>::<NAME>` (проекти-споживачі на CMake використовують `find_package(<NAME> CONFIG)`).

Виведення імʼя реалізоване у `meson/template-project-misc-variables-declare/meson.build`
і доступне як Meson-змінна `PROJECT_LIBRARY_NAME`, яку використовує решта системи побудови.
