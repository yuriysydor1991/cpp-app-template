## Обов'язкові пакети для розробки з SDL2

Проект-шаблон залежить від бібліотеки [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) разом з заголовковими файлами [OpenGL](https://www.opengl.org/). CMake конфігурує їх через `find_package(SDL2 REQUIRED)` і `find_package(OpenGL REQUIRED)` отож обидві бібліотеки мають бути присутніми в системі під час конфігурації.

### GNU/Лінукс (Debian/Ubuntu та похідні)

Мінімальний набір для конфігурації і побудови - пакет розробки SDL2 (`libsdl2-dev`) і файли розробки OpenGL (`libgl1-mesa-dev`):

```
sudo apt install -y libsdl2-dev libgl1-mesa-dev
```

Якщо застосунок використовує додаткові опціональні модулі SDL2 (завантаження картинок, рендеринг шрифтів, мікшування звуку, мережа) - встанови їх одразу:

```
sudo apt install -y libsdl2-dev libsdl2-doc \
  libsdl2-image-2.0-0 libsdl2-image-dev \
  libsdl2-mixer-2.0-0 libsdl2-mixer-dev \
  libsdl2-net-2.0-0 libsdl2-net-dev \
  libsdl2-ttf-dev
```

### Інші дистрибутиви GNU/Лінукс

- **Fedora / RHEL / openSUSE**: `SDL2-devel` (+ опційно `SDL2_image-devel`, `SDL2_mixer-devel`, `SDL2_net-devel`, `SDL2_ttf-devel`) і `mesa-libGL-devel`.
- **Arch Linux**: `sdl2` (+ опційно `sdl2_image`, `sdl2_mixer`, `sdl2_net`, `sdl2_ttf`) і `mesa`.

### MS Windows

Використовуй пакетний менеджер [vcpkg](https://vcpkg.io/) або завантажуй прекомпільовані бінарники для розробки з [офіційної сторінки релізів SDL2](https://github.com/libsdl-org/SDL/releases). У vcpkg команда встановлення така:

```
vcpkg install sdl2 sdl2-image sdl2-mixer sdl2-net sdl2-ttf
```

Передавай toolchain-файл vcpkg у CMake під час конфігурації щоб виклик `find_package(SDL2)` знайшов бінарники:

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
```

### Перевірка встановлення SDL2

Швидкий спосіб переконатися що SDL2 доступний через `pkg-config` після встановлення:

```
pkg-config --modversion sdl2
```

Команда має вивести встановлену версію SDL2. Якщо вона повертає помилку, то і виклик `find_package(SDL2 REQUIRED)` у CMake впаде на етапі конфігурації.
