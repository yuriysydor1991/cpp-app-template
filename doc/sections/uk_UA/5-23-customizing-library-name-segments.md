## Налаштування складових імені встановлюваної бібліотеки

Гілка `applib` створює головний виконуваний файл застосунку **і** окрему спільну
бібліотеку, проти якої можуть лінкуватись проекти-споживачі. Імʼя бібліотеки,
яке вони бачать (бінарник бібліотеки, субдиректорія `include/<name>/` для
публічних заголовків, директорія CMake package і простір імен імпортованої цілі
що експортується через `install(EXPORT ...)`) виводиться з трьох опціональних
CMake-опцій. Вони дозволяють паралельним встановленням різних версій бібліотеки
співіснувати у системі - наприклад `include/CppAppTemplate-0.11.0-dev/` поруч з
`include/CppAppTemplate-0/`. Імʼя головного виконуваного файлу застосунку не
змінюється і далі формується через `PROJECT_BINARY_NAME`.

| Опція | За замовчуванням | Ефект |
|---|---|---|
| `-DLIB_INCLUDE_MINOR_IN_NAME=ON` | `OFF` | Додає `.<minor>` до імені бібліотеки |
| `-DLIB_INCLUDE_MICRO_IN_NAME=ON` | `OFF` | Додає `.<micro>` (вмикає прапорець minor неявно) |
| `-DLIB_NAME_SUFFIX=-dev` | `""` | Додає довільний завершальний суфікс |

Приклади імен бібліотеки для проекту `0.11.0`:

| Прапорці конфігурації | Імʼя бібліотеки |
|---|---|
| (немає) | `CppAppTemplate-0` |
| `-DLIB_INCLUDE_MINOR_IN_NAME=ON` | `CppAppTemplate-0.11` |
| `-DLIB_INCLUDE_MINOR_IN_NAME=ON -DLIB_INCLUDE_MICRO_IN_NAME=ON` | `CppAppTemplate-0.11.0` |
| `-DLIB_NAME_SUFFIX=-dev` | `CppAppTemplate-0-dev` |
| `-DLIB_INCLUDE_MINOR_IN_NAME=ON -DLIB_INCLUDE_MICRO_IN_NAME=ON -DLIB_NAME_SUFFIX=-dev` | `CppAppTemplate-0.11.0-dev` |

Приклад поєднаної конфігурації:

```
# всередині кореневої директорії проекту

cmake -S . -B build \
  -DLIB_INCLUDE_MINOR_IN_NAME=ON \
  -DLIB_INCLUDE_MICRO_IN_NAME=ON \
  -DLIB_NAME_SUFFIX=-dev
cmake --build build
cmake --install build --prefix /usr/local
```

Однакове імʼя послідовно використовується для кожного встановлюваного артефакту бібліотеки:

- `<libdir>/lib<NAME>.so.<version>` (бінарник спільної бібліотеки),
- `<prefix>/include/<NAME>/*.h` (субдиректорія публічних заголовків, оголошена через `INSTALL_INTERFACE` цілі бібліотеки),
- `<libdir>/cmake/<NAME>/` + імпортована ціль `<NAME>::<NAME>` згенерована через `install(EXPORT ...)` - проекти-споживачі на CMake використовують `find_package(<NAME> CONFIG)`.

Головний виконуваний файл застосунку (`PROJECT_BINARY_NAME`, за замовчуванням `CppAppTemplate`) не зачіпається цими опціями і встановлюється за шляхом `<prefix>/<PROJECT_BINARY_INSTALLATION_DIR>/`.

Виведення імʼя реалізоване у [cmake/template-project-misc-variables-declare.cmake](/cmake/template-project-misc-variables-declare.cmake) і доступне як CMake cache-змінна `PROJECT_LIBRARY_NAME`, яку використовує решта системи побудови. Вмикання `LIB_INCLUDE_MICRO_IN_NAME` без `LIB_INCLUDE_MINOR_IN_NAME` спричиняє попередження на стадії конфігурування, а прапорець minor вмикається неявно щоб згенероване імʼя залишалось синтаксично коректним.
