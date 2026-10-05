## Enabling the V8 JavaScript engine

In order to enable the [V8](https://v8.dev/) JavaScript engine for the project set an `ON` value to the `ENABLE_V8` CMake variable (it is the default one for the `appV8` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_V8=ON
cmake --build build --target all
```

The V8 builds with the Google toolchain of it's own only, which takes hours and tens of gigabytes, so unlike the other enablers the [cmake/enablers/scripting/template-project-v8-enabler.cmake](/cmake/enablers/scripting/template-project-v8-enabler.cmake) module fetches nothing through the Internet and looks for an already installed V8 instead. The Debian based distributions ship the V8 inside the [Node.js](https://nodejs.org/) shared library, so install it's development package (the `scripts/packages/install-ubuntu.sh` and the `scripts/packages/install-debian.sh` scripts do it too):

```
sudo apt install -y libnode-dev
```

The package puts the V8 headers into the `/usr/include/node` directory and names the `libnode.so` library the `libv8.so` and the `libv8_libplatform.so` one as well. The enabler provides the found V8 as the `V8::V8` target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} V8::V8)
```

### An own V8 build

Point the enabler at an own V8 build (see the [Building V8 with GN](https://v8.dev/docs/build-gn) and the [Getting started with embedding V8](https://v8.dev/docs/embed) guides) by presetting the cache variables the enabler searches with:

| Variable | What it holds |
| --- | --- |
| `V8_INCLUDE_DIR` | the directory of the `v8.h` header, the `include` one of the V8 sources |
| `V8_LIBRARY` | the V8 library, e.g. the `libv8_monolith.a` of a monolithic build |
| `V8_LIBPLATFORM_LIBRARY` | the V8 platform library, needless for a monolithic build |
| `TEMPLATE_APP_V8_COMPILE_DEFINITIONS` | the definitions the V8 headers need to match the build |

The V8 headers must see the very same pointer compression and sandbox definitions the V8 binary was built with. The Node.js builds need none of them, while a build with the default arguments needs both:

```
cmake -S . -B build \
  -DV8_INCLUDE_DIR=/path/to/v8/include \
  -DV8_LIBRARY=/path/to/v8/out/x64.release/obj/libv8_monolith.a \
  -DTEMPLATE_APP_V8_COMPILE_DEFINITIONS="V8_COMPRESS_POINTERS;V8_ENABLE_SANDBOX"
```

The V8 is built without the RTTI, so the enabler turns the `vptr` check of the [sanitizers](/doc/sections/en_US/5-project-build/code-quality/5-13-enabling-sanitizers.md) off for the targets linking the `V8::V8` one.

The V8 headers since the 13.x version (e.g. the `libnode-dev` of the Node.js 24) demand the C++20, so the enabler raises the targets linking the `V8::V8` one to the C++20 while the rest of the project keeps it's C++17.

### The components

The [src/V8](/src/V8) directory holds three small classes of the `v8i` namespace:

| Class | What it does |
| --- | --- |
| `V8Platform` | initializes the whole V8 once per process (the ICU data, the startup snapshot, the platform and the engine itself) and disposes it at the process exit, since the V8 is never initialized again after it's disposal |
| `V8Console` | replaces the `console` object of a context with the one writing into the project logger |
| `V8Controller` | initializes the V8 through the `V8Platform`, owns an isolate with a context of it's own and runs the JavaScript code inside of it |

The `init` call of the `v8i::V8Controller` class of the [src/V8/V8Controller.h](/src/V8/V8Controller.h) file takes the executable path, since the V8 builds which keep the ICU data and the startup snapshot in separate files look for them next to it. The `run` call compiles and runs the code under the given script name and returns the completion value converted to a string. The globals a run declares stay available to the later runs of the very same controller, while every controller keeps a context of it's own.

```
auto engine = v8i::V8Controller::create();

if (engine->init(argv[0])) {
  engine->run("var answer = 6 * 7", "first.js");

  // logs the "second.js:1 : The answer is 42" message and returns the "42"
  const auto result = engine->run("console.log('The answer is', answer); answer", "second.js");
}
```

Nothing throws: a compile error or an uncaught exception gets logged by the `LOGE` macro together with it's script location (e.g. `throwing.js:3 : Uncaught Error: boom`) and the `run` call returns the `std::nullopt`.

### The console

The `console` object methods log their arguments converted to strings and joined by the spaces through the `LOG_REAL_LOGGER` instance, so the messages reach the very same log file and the standard output the `LOGx` macros write into. A message carries the JavaScript file name and line of the call in place of the C++ ones:

| Method | Log level |
| --- | --- |
| `console.log`, `console.info` | info |
| `console.warn` | warning |
| `console.error` | error |
| `console.debug` | debug |
| `console.trace` | trace |

```
2026-10-05 18:25:16 INF 140370990078208 main.js:1 : Hello, V8! Insert your JavaScript code here!
```

The logger level filters the console messages as any other ones, so raise the `MAX_LOG_LEVEL` CMake variable to see the `console.debug` and the `console.trace` ones.

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file runs the `console.log("Hello, V8! Insert your JavaScript code here!")` code, so replace it with your own JavaScript.

### Packaging

The DEB package depends on the `libnode` one the executable links against through the `dpkg-shlibdeps` tool, since every distribution release names it by it's own ABI version (e.g. the `libnode109` or the `libnode127`). The snap stages the `libnode109` package of it's `core24` base, while the flatpak builds the Node.js shared library from it's sources first, which takes a while.
