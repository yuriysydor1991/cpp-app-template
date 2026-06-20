## Вмикання інтеграції zlib

Для того щоб увімкнути бібліотеку стиснення [zlib](https://www.zlib.net/) (deflate, gzip, zip) для проекту, використовуючи встановлену версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_ZLIB`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_ZLIB=ON
```

Дивись модуль `cmake/enablers/compression/template-project-zlib-enabler.cmake` щодо цілей (`ZLIB::ZLIB` для системної версії, `zlibstatic`/`zlib` для побудови через FetchContent), які слід прилінкувати до твоїх цільових об'єктів.
