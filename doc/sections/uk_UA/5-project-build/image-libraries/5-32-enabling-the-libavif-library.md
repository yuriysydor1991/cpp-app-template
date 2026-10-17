## Вмикання інтеграції libavif (AVIF)

Для того щоб увімкнути бібліотеку [libavif](https://github.com/AOMediaCodec/libavif) (формат зображень AVIF / AV1) для проекту, використовуючи встановлену версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_LIBAVIF`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_LIBAVIF=ON
```

Для власне кодування/декодування AVIF потрібен кодек; для побудови через FetchContent увімкни один з них із системною бібліотекою кодека (наприклад `-DAVIF_CODEC_AOM=SYSTEM` або `-DAVIF_CODEC_DAV1D=SYSTEM`) або зі значенням `LOCAL`, щоб завантажити та побудувати також і кодек. Побудова через FetchContent залишає необов'язкове прискорення libyuv вимкненим (`AVIF_LIBYUV=OFF`), встанови `-DAVIF_LIBYUV=SYSTEM`, щоб використати встановлену в системі. Дивись модуль `cmake/enablers/images/template-project-libavif-enabler.cmake` щодо цілі (`avif`), яку слід прилінкувати до твоїх цільових об'єктів.
