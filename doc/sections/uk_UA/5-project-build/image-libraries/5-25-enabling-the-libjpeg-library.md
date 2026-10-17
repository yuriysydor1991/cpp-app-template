## Вмикання інтеграції libjpeg

Для того щоб увімкнути бібліотеку [libjpeg-turbo](https://libjpeg-turbo.org/) (формат зображень JPG/JPEG) для проекту, використовуючи встановлену в системі версію, необхідно встановити значення `ON` для CMake змінної `ENABLE_LIBJPEG`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_LIBJPEG=ON
```

libjpeg-turbo не можна побудувати через CMake FetchContent (вона відмовляється від інтеграції через `add_subdirectory()`), отож вона шукається виключно в системі (встанови `libjpeg-dev` на Debian/Ubuntu, `libjpeg-turbo-devel` на Fedora/RHEL або `jpeg-turbo` на Homebrew та FreeBSD) - резервного механізму FetchContent немає і за відсутності пакета конфігурування зупиняється з помилкою, яка його називає. Дивись модуль `cmake/enablers/images/template-project-libjpeg-enabler.cmake` щодо цілі (`JPEG::JPEG`), яку слід прилінкувати до твоїх цільових об'єктів.
