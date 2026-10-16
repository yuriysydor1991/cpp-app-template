## Встановлення файлів розробки бібліотеки

Встановлена динамічна бібліотека обслуговує дві різні аудиторії. Для запуску
програми, яку вже злінковано з бібліотекою, достатньо лише версійованого
бінарного файлу, який динамічний завантажувач знаходить через SONAME. Для
побудови *нової* програми з даною бібліотекою додатково необхідні файли
розробки: публічні заголовкові файли, файли інтеграції з системою CMake і
неверсійоване символьне посилання `lib<ім'я>.so`, яке шукає прапорець
лінкування `-l<ім'я>`.

Дистрибутиви розділяють ці дві групи на окремі пакунки - пакунок часу виконання
і пакунок `-dev` / `-devel`. Опція `LIB_INSTALL_DEV_FILES` дозволяє даному
проекту встановити або увесь набір, або лише половину часу виконання.

| Опція | За умовчанням | Дія |
|---|---|---|
| `-DLIB_INSTALL_DEV_FILES=ON` | `ON` | Встановлює бібліотеку часу виконання разом з файлами розробки |
| `-DLIB_INSTALL_DEV_FILES=OFF` | | Встановлює лише бібліотеку часу виконання |

Встановлення лише файлів часу виконання:

```
# у кореневій директорії проекту

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DLIB_INSTALL_DEV_FILES=OFF
cmake --build build
cmake --install build --prefix /usr/local
```

Що саме встановлює кожен з режимів для проекту `CppAppTemplate` версії `0.12.0`:

| Встановлюваний артефакт | `ON` | `OFF` |
|---|---|---|
| `<libdir>/libCppAppTemplate-0.12.so.0.12.0` - бінарний файл бібліотеки | так | так |
| `<libdir>/libCppAppTemplate-0.12.so.0` - символьне посилання SONAME для завантажувача | так | так |
| `<libdir>/libCppAppTemplate-0.12.so` - символьне посилання для лінкера | так | ні |
| `<prefix>/include/CppAppTemplate-0.12/*.h` - публічні заголовкові файли | так | ні |
| `<libdir>/cmake/CppAppTemplate-0.12/*.cmake` - інтеграція з `find_package` | так | ні |
| символи зневадження, якщо проект їх встановлює | так | ні |

`<libdir>` - це директорія `<prefix>/${CMAKE_INSTALL_LIBDIR}` модуля CMake
[GNUInstallDirs](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html):
типово `<prefix>/lib`, `<prefix>/lib64` на 64-бітних дистрибутивах на основі RPM
і `/usr/lib/<multiarch>` (наприклад, `/usr/lib/x86_64-linux-gnu`) для префікса
`/usr` у Debian та Ubuntu.

Встановлені файли `CppAppTemplate-0.12Config.cmake` і
`CppAppTemplate-0.12ConfigVersion.cmake` дозволяють проекту-споживачу на CMake
запитати бібліотеку за її іменем і версією:

```
find_package(CppAppTemplate-0.12 0.12 CONFIG REQUIRED)
target_link_libraries(consumer PRIVATE CppAppTemplate-0.12::CppAppTemplate-0.12)
```

Приймається лише та сама другорядна (minor) версія, бо публічний простір імен
бібліотеки (`CppAppTemplate012`) змінюється з кожною другорядною версією. Якщо
префікс встановлення не системний, його необхідно передати через змінну
`CMAKE_PREFIX_PATH`.

Виконуваний файл проекту знаходить встановлену бібліотеку через RUNPATH
`$ORIGIN/<шлях від bin до libdir>` (`$ORIGIN/../lib`, `$ORIGIN/../lib/x86_64-linux-gnu`
тощо), тож він запускається з будь-якого префікса встановлення без
`LD_LIBRARY_PATH` чи кешу `ldconfig`. Дивись файл [src/CMakeLists.txt](/src/CMakeLists.txt).

Даний шаблон не встановлює власних окремих файлів символів зневадження -
побудова у режимі `Debug` утримує інформацію зневадження всередині самого
бінарного файлу бібліотеки. Дана опція є саме тим місцем, де слід обмежити таке
правило встановлення, якщо похідний проект його додасть.

Вимкнення опції жодним чином не змінює те, що саме *будується* - прибираються
лише правила встановлення. Тому одне і те саме дерево побудови може бути
встановленим обома способами без переконфігурації.

Опція оголошена у [cmake/template-project-misc-variables-declare.cmake](/cmake/template-project-misc-variables-declare.cmake) і використовується у [src/lib/CMakeLists.txt](/src/lib/CMakeLists.txt) і [src/lib/facade/CMakeLists.txt](/src/lib/facade/CMakeLists.txt).

Дивись також розділ [Налаштування складових імені встановлюваної бібліотеки](/doc/sections/uk_UA/5-project-build/compression/5-23-customizing-library-name-segments.md), який визначає `<NAME>` для кожного з перелічених вище артефактів.
