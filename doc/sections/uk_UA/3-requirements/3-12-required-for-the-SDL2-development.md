## Обов'язкові пакети для розробки з SDL2

Проект-шаблон залежить від бібліотеки [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) разом з заголовковими файлами [OpenGL](https://www.opengl.org/). CMake отримує SDL2 через окремий enabler-модуль `cmake/enablers/template-project-SDL2-enabler.cmake`: спершу він шукає SDL2 у системі (`find_package(SDL2 QUIET)`), а якщо його не встановлено, клонує `libsdl-org/SDL` за тегом з `TEMPLATE_APP_SDL2_GIT_TAG` (за замовчуванням `release-2.32.10`) через **FetchContent** і збирає `SDL2::SDL2` з джерел разом з проектом як статичну бібліотеку, скомпоновану з бінарним файлом (власної бібліотеки SDL2 проект не встановлює). OpenGL все ще шукається у системі через `find_package(OpenGL REQUIRED)`.

### Системний SDL2 чи побудова через FetchContent

Встановлений у системі SDL2 завжди має перевагу. Щоб усе ж зібрати зафіксовані джерела на машині зі встановленим `libsdl2-dev`, прихови системний пакет від пошуку стандартною CMake змінною `CMAKE_DISABLE_FIND_PACKAGE_SDL2`. Переключи URL або зафіксуй конкретну ревізію через рядкові cache-змінні `TEMPLATE_APP_SDL2_GIT` (URL) і `TEMPLATE_APP_SDL2_GIT_TAG` (git-тег / гілка / sha), наприклад:

```
cmake -S . -B build \
  -DCMAKE_DISABLE_FIND_PACKAGE_SDL2=ON \
  -DTEMPLATE_APP_SDL2_GIT_TAG=release-2.32.10
```

Побудова SDL2 з джерел компілює відео-підсистеми лише для тих віконних систем, файли розробки яких вона знаходить, тож встанови їх до конфігурації (наприклад `libx11-dev libxext-dev libwayland-dev libxkbcommon-dev libegl-dev` на Debian/Ubuntu), інакше застосунок завершиться з помилкою "No available video device".

CMake опція `ENABLE_SDL2` (за замовчуванням `ON`) призначена для проектів, що відмовляються від інтеграції з SDL2: сирці шаблону (`src/SDL2`, використання `SDL2Controller` у класі `Application` та їхні тести) використовують SDL2 безумовно, тож її значення `OFF` працює лише разом з їх видаленням.

### GNU/Лінукс (Debian/Ubuntu та похідні)

Мінімальний набір для конфігурації і побудови із системним SDL2 - пакет розробки SDL2 (`libsdl2-dev`) і файли розробки OpenGL (`libgl1-mesa-dev`):

```
sudo apt install -y libsdl2-dev libgl1-mesa-dev
```

Сам шаблон не використовує жодного з супутніх модулів SDL2. Якщо застосунок використовуватиме їх (завантаження картинок, рендеринг шрифтів, мікшування звуку, мережа) - встанови їх одразу:

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
vcpkg install sdl2
```

Додавай порти супутніх модулів (`sdl2-image`, `sdl2-mixer`, `sdl2-net`, `sdl2-ttf`) лише тоді, коли застосунок їх використовує. Передавай toolchain-файл vcpkg у CMake під час конфігурації щоб виклик `find_package(SDL2)` знайшов бінарники:

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
```

### Перевірка встановлення SDL2

Швидкий спосіб переконатися що SDL2 доступний через `pkg-config` після встановлення:

```
pkg-config --modversion sdl2
```

Команда має вивести встановлену версію SDL2. Якщо вона повертає помилку, то і пошук `find_package(SDL2 QUIET)` у CMake не знайде SDL2, і конфігурація перейде до побудови через FetchContent.
