## Обов'язкові пакети для розробки з SDL3

Проект-шаблон залежить від бібліотеки [SDL3](https://wiki.libsdl.org/SDL3/FrontPage) разом з заголовковими файлами [OpenGL](https://www.opengl.org/). CMake конфігурує їх через `find_package(SDL3 REQUIRED)` і `find_package(OpenGL REQUIRED)` отож обидві бібліотеки мають бути присутніми в системі під час конфігурації.

### GNU/Лінукс (Debian/Ubuntu та похідні)

Мінімальний набір для конфігурації і побудови - пакет розробки SDL3 (`libsdl3-dev`) і файли розробки OpenGL (`libgl1-mesa-dev`):

```
sudo apt install -y libsdl3-dev libgl1-mesa-dev
```

Якщо застосунок використовує додаткові опціональні модулі SDL3 (завантаження картинок, рендеринг шрифтів) - встанови їх одразу:

```
sudo apt install -y libsdl3-dev libsdl3-doc \
  libsdl3-image0 libsdl3-image-dev \
  libsdl3-ttf0 libsdl3-ttf-dev
```

Якщо пакет `libsdl3-dev` ще відсутній у стабільних apt репозиторіях (наприклад на старих Debian / Ubuntu LTS), збери його з джерел:

```
git clone --depth 1 --branch release-3.2.10 https://github.com/libsdl-org/SDL.git
cmake -S SDL -B SDL/build -DCMAKE_BUILD_TYPE=Release -DSDL_STATIC=OFF -DSDL_SHARED=ON
cmake --build SDL/build --parallel
sudo cmake --install SDL/build
sudo ldconfig
```

### Інші дистрибутиви GNU/Лінукс

- **Fedora / RHEL / openSUSE**: `SDL3-devel` (+ опційно `SDL3_image-devel`, `SDL3_ttf-devel`) і `mesa-libGL-devel`.
- **Arch Linux**: `sdl3` (+ опційно `sdl3_image`, `sdl3_ttf`) і `mesa`.

### MS Windows

Використовуй пакетний менеджер [vcpkg](https://vcpkg.io/) або завантажуй прекомпільовані бінарники для розробки з [офіційної сторінки релізів SDL3](https://github.com/libsdl-org/SDL/releases). У vcpkg команда встановлення така:

```
vcpkg install sdl3 sdl3-image sdl3-ttf
```

Передавай toolchain-файл vcpkg у CMake під час конфігурації щоб виклик `find_package(SDL3)` знайшов бінарники:

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
```

### Перевірка встановлення SDL3

Швидкий спосіб переконатися що SDL3 доступний через `pkg-config` після встановлення:

```
pkg-config --modversion sdl3
```

Команда має вивести встановлену версію SDL3. Якщо вона повертає помилку, то і виклик `find_package(SDL3 REQUIRED)` у CMake впаде на етапі конфігурації.
