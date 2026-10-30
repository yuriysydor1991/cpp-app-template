## Побудова бінарного файлу WebAssembly для браузерів

Бінарний файл проекту стає сторінкою [WebAssembly](https://webassembly.org/), яку виконують веб-браузери, щойно проект сконфігуровано набором інструментів компілятора [Emscripten](https://emscripten.org/), який команда `emcmake` цього ж Emscripten передає кроку конфігурації CMake, тож встановлювати жодну опцію CMake не потрібно:

```
# в середині кореневої директорії проекту

emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release
cmake --build build-wasm
```

Модуль [cmake/enablers/template-project-webassembly-enabler.cmake](/cmake/enablers/template-project-webassembly-enabler.cmake) змушує побудову створити замість нативного виконуваного файлу три файли: сторінку `CppAppTemplate.html`, завантажувач `CppAppTemplate.js` та модуль `CppAppTemplate.wasm`, усі всередині каталогу `build-wasm/src`. Під час конфігурації без Emscripten модуль нічого не робить, отож те саме дерево сирців і надалі будує нативний бінарний файл, його тести, аналізатори та пакунки.

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

Браузери відмовляються завантажувати модуль WebAssembly сторінки, відкритої як локальна `file://`, тож сторінці потрібен веб-сервер. Команда [emrun](https://emscripten.org/docs/compiling/Running-html-files-with-emrun.html) з Emscripten роздає каталог сторінки, відкриває сторінку у браузері за замовчуванням та друкує у терміналі вивід і код завершення бінарного файлу:

```
# в середині кореневої директорії проекту

emrun build-wasm/src/CppAppTemplate.html
```

Сторінка передає свій URL-запит, розділений символами `&`, функції `main` як аргументи командного рядка, отож адреса `http://localhost:6931/CppAppTemplate.html?--version` друкує версію, як і команда `emrun` з аргументами після `--`:

```
emrun build-wasm/src/CppAppTemplate.html -- --version
```

[Node.js](https://nodejs.org/) також запускає завантажувач як застосунок командного рядка:

```
node build-wasm/src/CppAppTemplate.js --version
```

### Встановлення сторінки

Крок встановлення копіює завантажувач і модуль поруч зі сторінкою до каталогу `PROJECT_BINARY_INSTALLATION_DIR`, тож веб-сервер отримує всі три файли, наприклад:

```
emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release -DPROJECT_BINARY_INSTALLATION_DIR=.
cmake --build build-wasm
cmake --install build-wasm --prefix /var/www/html/CppAppTemplate
```

### Обмеження

Браузер виконує бінарний файл у своїй пісочниці, тож бінарний файл не отримує сигналів ОС і бачить файлову систему в пам'яті, яка зберігає й файл журналу. Бібліотеки, з якими компонується бінарний файл, також мають бути побудовані Emscripten: його [порти](https://emscripten.org/docs/compiling/Building-Projects.html#emscripten-ports) (наприклад, `-sUSE_SDL=2`) або сирці, завантажені та скомпільовані конфігурацією, адже встановлені в системі нативні бібліотеки ніколи не компонуються з бінарним файлом WebAssembly. Юніт- та компонентні тести виконуються з нативною побудовою, оскільки вони покладаються на потоки та файли каталогу побудови, яких бракує побудові тестів з Emscripten.

Модуль змінює лише ціль `PROJECT_BINARY_NAME`, тож він підходить іншим гілкам шаблону без змін: скопіюйте модуль разом з його рядком `include` файлу [cmake/template-project-feature-enabler-post.cmake](/cmake/template-project-feature-enabler-post.cmake), щоб будувати їхні бінарні файли для браузерів.
