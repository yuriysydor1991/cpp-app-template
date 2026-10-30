## Building the WebAssembly binary for the browsers

The project binary turns into a [WebAssembly](https://webassembly.org/) page the web browsers run once the project gets configured with the [Emscripten](https://emscripten.org/) compiler toolchain, which the `emcmake` command of the Emscripten hands over to the CMake configure step, so no CMake option has to be set:

```
# Inside the source root directory

emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release
cmake --build build-wasm
```

The [cmake/enablers/template-project-webassembly-enabler.cmake](/cmake/enablers/template-project-webassembly-enabler.cmake) module makes the build produce two files inside the `build-wasm/src` directory instead of the native executable: the `CppAppTemplate.js` loader, which embeds the WebAssembly module, and the `CppAppTemplate.html` page out of the [misc/webassembly/webassembly.html.in](/misc/webassembly/webassembly.html.in) template, which runs the loader and prints the output of the binary, every log message among it. The module stays idle during a configure without the Emscripten, so the same source tree keeps building the native binary, its tests, analyzers and packages.

The [scripts/build/webassembly-release.sh](/scripts/build/webassembly-release.sh) script performs both steps at once, as the [Quick build scripts](/doc/sections/en_US/5-project-build/5-36-quick-build-scripts.md) section tells.

### Installing the Emscripten

The Debian 13 and the Ubuntu 26.04 package the Emscripten:

```
sudo apt install -y emscripten
```

The other systems (and the users of the latest Emscripten) install the [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html) instead, whose `emsdk_env.sh` script puts the `emcmake` command into the `PATH` of the current shell:

```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

### Running the page

The loader carries the module inside, so the browser runs the page opened right from the disk, with no web server:

```
# Inside the source root directory

xdg-open build-wasm/src/CppAppTemplate.html
```

The page hands its URL query to the `main` function as the command line arguments, so the `CppAppTemplate.html?--version` address prints the version, while the `&` characters separate several arguments: `CppAppTemplate.html?--log-file&app.log`. A page of your own has to keep the UTF-8 encoding declaration of the template, since the loader of the Emscripten 4.0.18 and newer embeds the module as the UTF-8 text.

The [Node.js](https://nodejs.org/) runs the loader as a command line application too:

```
node build-wasm/src/CppAppTemplate.js --version
```

### Installing the page

The install step copies the page next to the loader into the `PROJECT_BINARY_INSTALLATION_DIR` directory, so a web server gets both of them, for example:

```
emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release -DPROJECT_BINARY_INSTALLATION_DIR=.
cmake --build build-wasm
cmake --install build-wasm --prefix /var/www/html/CppAppTemplate
```

### Limitations

The browser runs the binary inside its sandbox, so the binary gets no OS signals and sees an in-memory file system, which keeps the log file as well. The libraries the binary links have to be built by the Emscripten too: its [ports](https://emscripten.org/docs/compiling/Building-Projects.html#emscripten-ports) (the `-sUSE_SDL=2` one, for example) or the sources fetched and compiled by the configure, since the system installed native libraries never link into the WebAssembly binary. The unit and the component tests run with the native build, as they rely on the threads and the build directory files the Emscripten build of the tests lacks.

The module modifies the `PROJECT_BINARY_NAME` target only, so it fits the other branches of the template as it is: copy the module and the page template together with the `include` line of the module in the [cmake/template-project-feature-enabler-post.cmake](/cmake/template-project-feature-enabler-post.cmake) file to build their binaries for the browsers.
