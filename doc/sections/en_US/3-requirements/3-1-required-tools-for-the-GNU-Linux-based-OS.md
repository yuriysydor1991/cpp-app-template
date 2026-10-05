## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appV8` branch additionally needs the [V8](https://v8.dev/) JavaScript engine headers and library, which the Debian based distributions ship inside the [Node.js](https://nodejs.org/) shared library development package:

```
sudo apt install -y libnode-dev
```

The `scripts/packages/install-ubuntu.sh` (or the `scripts/packages/install-debian.sh`) script installs it together with the rest of the required packages. There is no Internet fallback for the V8, since it builds with the Google toolchain of it's own only, so look for the own V8 build details at the [Enabling the V8 JavaScript engine](/doc/sections/en_US/5-project-build/scripting/5-57-enabling-the-V8-JavaScript-engine.md) section.
