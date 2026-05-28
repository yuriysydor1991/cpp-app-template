## Обов'язкові пакети для розробки з SFML

Проект-шаблон залежить від мультимедійної бібліотеки [SFML](https://www.sfml-dev.org/) (модулі `graphics`, `window` та `system`). CMake-скрипт `template-project-SFML-enabler` спочатку шукає встановлену в системі бібліотеку через `find_package(SFML COMPONENTS graphics window system)`, а якщо її немає - прозоро завантажує і будує SFML з вихідних кодів з апстрім git-репозиторію за допомогою механізму CMake `FetchContent` (типово зафіксовано на теґу `2.6.2`).

Тож загальносистемна SFML є **необов'язковою**: встанови її щоб пришвидшити крок конфігурації, або дозволь резервному механізму `FetchContent` побудувати її за тебе (для чого додатково потрібні заголовкові файли X11/OpenGL/FreeType, перелічені нижче).

### GNU/Лінукс (Debian/Ubuntu та похідні)

Найшвидший шлях - встановити пакет розробки SFML, щоб системний пошук був успішним і побудова з вихідних кодів не знадобилась:

```
sudo apt install -y libsfml-dev
```

Якщо ж ти волієш (або змушений) дозволити резервному `FetchContent` побудувати SFML з вихідних кодів, встанови натомість набір інструментів разом із залежностями для побудови SFML:

```
sudo apt install -y git g++ cmake \
  libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev \
  libgl1-mesa-dev libfreetype-dev
```

### Інші дистрибутиви GNU/Лінукс

- **Fedora / RHEL / openSUSE**: `SFML-devel` (або набір інструментів плюс `libX11-devel`, `libXrandr-devel`, `libXcursor-devel`, `libXi-devel`, `systemd-devel`, `mesa-libGL-devel` та `freetype-devel` для побудови з вихідних кодів).
- **Arch Linux**: `sfml` (або `libx11`, `libxrandr`, `libxcursor`, `libxi`, `systemd-libs`, `mesa` та `freetype2` для побудови з вихідних кодів).

### MS Windows

Використовуй пакетний менеджер [vcpkg](https://vcpkg.io/) або завантаж прекомпільовані бінарники для розробки з [офіційної сторінки завантажень SFML](https://www.sfml-dev.org/download.php). У vcpkg команда встановлення така:

```
vcpkg install sfml
```

Передавай toolchain-файл vcpkg у CMake під час конфігурації, щоб виклик `find_package(SFML)` знайшов бінарники:

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
```

Якщо ні системної SFML, ні vcpkg немає, резервний механізм `FetchContent` все одно побудує SFML з вихідних кодів, за умови що встановлено набір інструментів C++ для платформи.

### Налаштування SFML-енейблера

- `-DENABLE_SFML=OFF` вимикає всю інтеграцію з SFML.
- `-DTEMPLATE_APP_SFML_GIT_TAG=<теґ>` обирає іншу ревізію SFML для побудови через `FetchContent` (типово `2.6.2`).

### Перевірка встановлення SFML

Швидкий спосіб переконатися що системна SFML доступна через `pkg-config`:

```
pkg-config --modversion sfml-graphics
```

Команда має вивести встановлену версію SFML. Якщо вона повертає помилку, то пошук `find_package(SFML ...)` у CMake не знайде системної SFML і буде використано резервний механізм `FetchContent`.
