## Побудова бінарного файлу WebAssembly для браузерів

Бінарний файл проекту стає сторінкою [WebAssembly](https://webassembly.org/), яку виконують веб-браузери, щойно проект сконфігуровано набором інструментів компілятора [Emscripten](https://emscripten.org/), який команда `emcmake` цього ж Emscripten передає кроку конфігурації CMake, тож встановлювати жодну опцію CMake не потрібно:

```
# в середині кореневої директорії проекту

emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release
cmake --build build-wasm
```

Модуль [cmake/enablers/template-project-webassembly-enabler.cmake](/cmake/enablers/template-project-webassembly-enabler.cmake) змушує побудову створити всередині каталогу `build-wasm/src` замість нативного виконуваного файлу два файли: завантажувач `CppAppTemplate.js`, який містить у собі модуль WebAssembly, та сторінку `CppAppTemplate.html` з шаблону [misc/webassembly/webassembly.html.in](/misc/webassembly/webassembly.html.in), яка запускає завантажувач і друкує вивід бінарного файлу, зокрема всі повідомлення журналу. Під час конфігурації без Emscripten модуль нічого не робить, отож те саме дерево сирців і надалі будує нативний бінарний файл, його тести, аналізатори та пакунки.

Скрипт [scripts/build/webassembly-release.sh](/scripts/build/webassembly-release.sh) виконує обидва кроки однією командою, як описує розділ [Швидкі скрипти побудови](/doc/sections/uk_UA/5-project-build/5-36-quick-build-scripts.md).

### Встановлення Emscripten

Debian 13 та Ubuntu 26.04 постачають Emscripten пакунком:

```
sudo apt install -y emscripten
```

Інші системи (і користувачі найновішого Emscripten) натомість встановлюють [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html), чий скрипт `emsdk_env.sh` додає команду `emcmake` до `PATH` поточної оболонки:

```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

### Запуск сторінки

Завантажувач містить модуль у собі, тож браузер виконує сторінку, відкриту прямо з диска, без жодного веб-сервера:

```
# в середині кореневої директорії проекту

xdg-open build-wasm/src/CppAppTemplate.html
```

Сторінка передає свій URL-запит функції `main` як аргументи командного рядка, отож адреса `CppAppTemplate.html?--version` друкує версію, а символи `&` розділяють кілька аргументів: `CppAppTemplate.html?--log-file&app.log`. Власна сторінка має зберегти оголошення кодування UTF-8 з шаблону, адже завантажувач Emscripten 4.0.18 і новіших вбудовує модуль як текст UTF-8.

[Node.js](https://nodejs.org/) також запускає завантажувач як застосунок командного рядка:

```
node build-wasm/src/CppAppTemplate.js --version
```

### Встановлення сторінки

Крок встановлення копіює сторінку поруч із завантажувачем до каталогу `PROJECT_BINARY_INSTALLATION_DIR`, тож веб-сервер отримує обидва файли, наприклад:

```
emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release -DPROJECT_BINARY_INSTALLATION_DIR=.
cmake --build build-wasm
cmake --install build-wasm --prefix /var/www/html/CppAppTemplate
```

### Обмеження

Браузер виконує бінарний файл у своїй пісочниці, тож бінарний файл не отримує сигналів ОС і бачить файлову систему в пам'яті, яка зберігає й файл журналу. Бібліотеки, з якими компонується бінарний файл, також мають бути побудовані Emscripten: його [порти](https://emscripten.org/docs/compiling/Building-Projects.html#emscripten-ports) (наприклад, `-sUSE_SDL=2`) або сирці, завантажені та скомпільовані конфігурацією, адже встановлені в системі нативні бібліотеки ніколи не компонуються з бінарним файлом WebAssembly. Юніт- та компонентні тести виконуються з нативною побудовою, оскільки вони покладаються на потоки та файли каталогу побудови, яких бракує побудові тестів з Emscripten.

Модуль змінює лише ціль `PROJECT_BINARY_NAME`, тож він підходить іншим гілкам шаблону без змін: скопіюйте модуль і шаблон сторінки разом з рядком `include` модуля у файлі [cmake/template-project-feature-enabler-post.cmake](/cmake/template-project-feature-enabler-post.cmake), щоб будувати їхні бінарні файли для браузерів.
