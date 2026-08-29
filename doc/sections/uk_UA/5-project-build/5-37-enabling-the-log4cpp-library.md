## Вмикання інтеграції бібліотеки log4cpp

Бібліотека [log4cpp](https://log4cpp.sourceforge.net/) виконує усе логування гілки `appLog4Cpp5`, тому CMake змінна `ENABLE_LOG4CPP` за замовчуванням має значення `ON` і побудова не потребує жодного додаткового параметру для неї:

```
# в середині кореневої директорії проекту

cmake -S . -B build
cmake --build build --target all
```

Модуль [cmake/enablers/template-project-log4cpp-enabler.cmake](/cmake/enablers/template-project-log4cpp-enabler.cmake) шукає встановлену у системі бібліотеку за допомогою `pkg-config`, оскільки autotools побудова log4cpp постачає лише файл `log4cpp.pc`. Якщо встановленої у системі бібліотеки не знайдено, то натомість завантажуються вихідні коди теґу `TEMPLATE_APP_LOG4CPP_GIT_TAG` із репозиторію `TEMPLATE_APP_LOG4CPP_GIT`, тому машина без встановленого [пакету розробки log4cpp](/doc/sections/uk_UA/3-requirements/3-11-required-packages-for-the-log4cpp.md) все одно конфігурує та збирає проект.

CMake побудову завантажених вихідних кодів модуль доповнює заголовком `log4cpp/config.h` зі значеннями для POSIX, директоріями заголовків бібліотеки та бібліотекою потоків для компонування, оскільки усе це записує саме крок конфігурування autotools. Статична бібліотека та заголовки такої побудови також потрапляють до встановлення проекту, тоді як встановлена у системі бібліотека лише компонується.

Обидва шляхи надають один і той самий ціль `LOG4CPP::log4cpp`, тому компонуйте її до своїх цілей:

```
target_link_libraries(${PROJECT_BINARY_NAME} LOG4CPP::log4cpp)
```

Модуль [src/log/CMakeLists.txt](/src/log/CMakeLists.txt) компонує її до виконуваного файлу проекту, а [src/log/log4cpp5-init/CMakeLists.txt](/src/log/log4cpp5-init/CMakeLists.txt) — до об'єктної бібліотеки `TemplateLog4Cpp5ControllerObj`, тому вихідні коди `log4cpp5i::Log4Cpp5Init` бачать заголовки обох шляхів.

Значення `OFF` залишає гілку взагалі без бібліотеки логування для компонування, тому встановлюйте його лише разом із заміною логера log4cpp5 на власний.
