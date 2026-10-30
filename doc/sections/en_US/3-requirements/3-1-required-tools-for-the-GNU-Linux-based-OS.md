## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appSherpaONNXSTT` branch additionally needs the development files of the [SDL2](https://www.libsdl.org/) library it captures the microphone with, while the configure fetches and builds the [sherpa-onnx](https://github.com/k2-fsa/sherpa-onnx) speech recognition library itself (with the `git` tool and the internet access). The sherpa-onnx runs the models with the [onnxruntime](https://github.com/microsoft/onnxruntime) of the distribution where one is packaged, and downloads it's own prebuilt one otherwise:

```
sudo apt install -y libonnxruntime-dev libsdl2-dev
```

The Ubuntu 24.04 packages no onnxruntime, so the `libsdl2-dev` package alone is needed there. The `scripts/packages/install-ubuntu.sh` (or the `scripts/packages/install-debian.sh`) script installs them together with the rest of the required packages. On Fedora the equivalent packages are `onnxruntime-devel` and `SDL2-devel` (the RHEL packages no onnxruntime); on FreeBSD they are `misc/onnxruntime` and `devel/sdl20` from `pkg`. See the [Enabling the sherpa-onnx speech recognition](/doc/sections/en_US/5-project-build/ai/5-75-enabling-the-sherpa-onnx-speech-recognition.md) section for the model the configure downloads and for the licenses of the library and of the model.

The [scripts/packages](/scripts/packages) directory holds the scripts which install every package the project needs in one go. The [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) and [install-debian.sh](/scripts/packages/install-debian.sh) ones run the script of the running release - the [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), the [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) or the [install-debian-13.sh](/scripts/packages/install-debian-13.sh) one - since every release names and versions its packages its own way, and fail with the list of the supported releases on any other one. A dependency a release packages no usable version of is built by its script out of a pinned release tag of the dependency sources. The [install-redhat.sh](/scripts/packages/install-redhat.sh) script covers Fedora, RHEL and its rebuilds, and the [install-freebsd.sh](/scripts/packages/install-freebsd.sh) one covers FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
