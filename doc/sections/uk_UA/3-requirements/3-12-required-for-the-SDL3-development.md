## Обов'язкові пакети для розробки з SDL3

Проект-шаблон залежить від бібліотеки [SDL3](https://wiki.libsdl.org/SDL3/FrontPage) разом з заголовковими файлами [OpenGL](https://www.opengl.org/). CMake отримує SDL3 через окремий enabler-модуль `cmake/enablers/template-project-SDL3-enabler.cmake`: спершу він шукає SDL3 у системі (`find_package(SDL3 QUIET)`), а якщо його не встановлено, клонує `libsdl-org/SDL` за тегом з `TEMPLATE_APP_SDL3_GIT_TAG` (за замовчуванням `release-3.2.10`) через **FetchContent** і збирає `SDL3::SDL3` з джерел разом з проектом як статичну бібліотеку, скомпоновану з бінарним файлом (власної бібліотеки SDL3 проект не встановлює). OpenGL все ще шукається у системі через `find_package(OpenGL REQUIRED)`.

### Системний SDL3 чи побудова через FetchContent

Встановлений у системі SDL3 завжди має перевагу. Щоб усе ж зібрати зафіксовані джерела на машині зі встановленим `libsdl3-dev`, прихови системний пакет від пошуку стандартною CMake змінною `CMAKE_DISABLE_FIND_PACKAGE_SDL3`. Переключи URL або зафіксуй конкретну ревізію через рядкові cache-змінні `TEMPLATE_APP_SDL3_GIT` (URL) і `TEMPLATE_APP_SDL3_GIT_TAG` (git-тег / гілка / sha), наприклад:

```
cmake -S . -B build \
  -DCMAKE_DISABLE_FIND_PACKAGE_SDL3=ON \
  -DTEMPLATE_APP_SDL3_GIT_TAG=release-3.2.10
```

Побудова SDL3 з джерел компілює відео-підсистеми лише для тих віконних систем, файли розробки яких вона знаходить, тож встанови їх до конфігурації, інакше застосунок завершиться з помилкою "No available video device". На Debian/Ubuntu:

```
sudo apt install -y libx11-dev libxext-dev libxrandr-dev libxcursor-dev \
  libxi-dev libxfixes-dev libxss-dev libxtst-dev libwayland-dev \
  libxkbcommon-dev libegl-dev libdecor-0-dev libdbus-1-dev libudev-dev
```

CMake опція `ENABLE_SDL3` (за замовчуванням `ON`) призначена для проектів, що відмовляються від інтеграції з SDL3: сирці шаблону (`src/SDL3`, використання `SDL3Controller` у класі `Application` та їхні тести) використовують SDL3 безумовно, тож її значення `OFF` працює лише разом з їх видаленням.

Нижче перелічено варіанти системного встановлення.

### GNU/Лінукс (Debian/Ubuntu та похідні)

Мінімальний набір для конфігурації і побудови з системним SDL3 - пакет розробки SDL3 (`libsdl3-dev`, доступний починаючи з Debian 13 та Ubuntu 25.04) і файли розробки OpenGL (`libgl1-mesa-dev`):

```
sudo apt install -y libsdl3-dev libgl1-mesa-dev
```

Сам шаблон не використовує жодного з додаткових модулів SDL3. Якщо твій застосунок їх використовуватиме (завантаження картинок, рендеринг шрифтів) - встанови їх одразу:

```
sudo apt install -y libsdl3-dev libsdl3-doc \
  libsdl3-image0 libsdl3-image-dev \
  libsdl3-ttf0 libsdl3-ttf-dev
```

Якщо пакет `libsdl3-dev` відсутній у apt репозиторіях (наприклад в Ubuntu 24.04), або дозволь побудові через FetchContent вище зробити це, або збери та встанови його з джерел (зі встановленими вище пакетами розробки віконних систем):

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
vcpkg install sdl3
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

Команда має вивести встановлену версію SDL3. Якщо вона повертає помилку, то і пошук `find_package(SDL3 QUIET)` у CMake не знайде SDL3, тож конфігурація перейде до побудови через FetchContent.
