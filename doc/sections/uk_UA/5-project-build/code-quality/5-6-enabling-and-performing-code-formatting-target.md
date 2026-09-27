## Вмикання підтримки форматування коду

Для того щоб зробити доступною ціль `clang-format` необхідно встановити змінну `ENABLE_CLANGFORMAT` у значення `ON` під час конфігурації проекту-шаблону (для GNU/Linux ОС):

```
# всередині кореня проекту-шаблону

mkdir -vp build && cd build && cmake ../ -DENABLE_CLANGFORMAT=ON
```

Для того щоб виконати форматування коду усього проекту-шаблону у відповідності до стандартів вказаних у файлі `misc/.clang-format` необхідно виконати наступну команду:

```
# всередині директорії побудови проекту-шаблона

cmake --build . --target clang-format
```

Деталі цілі `clang-format` можна перегляну у файлі `cmake/template-project-clang-format-target.cmake` субмодуля системи CMake.

Скрипт [debug-clang-format.sh](/scripts/build/debug-clang-format.sh) із секції [Швидкі скрипти побудови](/doc/sections/uk_UA/5-project-build/5-36-quick-build-scripts.md) однією командою конфігурує директорію `build/debug` з параметром `ENABLE_CLANGFORMAT` і будує в ній ціль `clang-format` (для GNU/Linux ОС і подібних):

```
# в середині кореневої директорії проекту

scripts/build/debug-clang-format.sh
```
