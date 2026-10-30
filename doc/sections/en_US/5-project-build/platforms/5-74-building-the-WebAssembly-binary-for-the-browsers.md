## Building the WebAssembly binary for the browsers

The project binary turns into a [WebAssembly](https://webassembly.org/) page the web browsers run once the project gets configured with the [Emscripten](https://emscripten.org/) compiler toolchain, which the `emcmake` command of the Emscripten hands over to the CMake configure step, so no CMake option has to be set:

```
# Inside the source root directory

emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release
cmake --build build-wasm
```

The [cmake/enablers/template-project-webassembly-enabler.cmake](/cmake/enablers/template-project-webassembly-enabler.cmake) module makes the build produce three files instead of the native executable: the `CppAppTemplate.html` page, the `CppAppTemplate.js` loader and the `CppAppTemplate.wasm` module, all of them inside the `build-wasm/src` directory. The module stays idle during a configure without the Emscripten, so the same source tree keeps building the native binary, its tests, analyzers and packages.

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

The browsers refuse to load the WebAssembly module of a page opened as a local `file://` one, so the page needs a web server. The [emrun](https://emscripten.org/docs/compiling/Running-html-files-with-emrun.html) command of the Emscripten serves the directory of the page, opens the page in the default browser and prints the output and the exit code of the binary in the terminal:

```
# Inside the source root directory

emrun build-wasm/src/CppAppTemplate.html
```

The page hands its URL query, split at the `&` characters, to the `main` function as the command line arguments, so the `http://localhost:6931/CppAppTemplate.html?--version` address prints the version, and so does the `emrun` command with the arguments after the `--` one:

```
emrun build-wasm/src/CppAppTemplate.html -- --version
```

The [Node.js](https://nodejs.org/) runs the loader as a command line application too:

```
node build-wasm/src/CppAppTemplate.js --version
```

### Installing the page

The install step copies the loader and the module next to the page into the `PROJECT_BINARY_INSTALLATION_DIR` directory, so a web server gets all three of them, for example:

```
emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release -DPROJECT_BINARY_INSTALLATION_DIR=.
cmake --build build-wasm
cmake --install build-wasm --prefix /var/www/html/CppAppTemplate
```

### Limitations

The browser runs the binary inside its sandbox, so the binary gets no OS signals and sees an in-memory file system, which keeps the log file as well. The libraries the binary links have to be built by the Emscripten too: its [ports](https://emscripten.org/docs/compiling/Building-Projects.html#emscripten-ports) (the `-sUSE_SDL=2` one, for example) or the sources fetched and compiled by the configure, since the system installed native libraries never link into the WebAssembly binary. The unit and the component tests run with the native build, as they rely on the threads and the build directory files the Emscripten build of the tests lacks.

The module modifies the `PROJECT_BINARY_NAME` target only, so it fits the other branches of the template as it is: copy the module together with its `include` line of the [cmake/template-project-feature-enabler-post.cmake](/cmake/template-project-feature-enabler-post.cmake) file to build their binaries for the browsers.
