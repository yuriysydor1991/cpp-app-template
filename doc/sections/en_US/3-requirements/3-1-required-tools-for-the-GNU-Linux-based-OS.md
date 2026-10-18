## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appPiperTTS` branch additionally needs the git and the internet access, since the configure builds the [Piper](https://github.com/OHF-Voice/piper1-gpl) speech synthesis library from it's sources, the development files of the [onnxruntime](https://onnxruntime.ai/) it runs the voices with, where the system packages it, and of the [SDL2](https://www.libsdl.org/) one it plays the speech with:

```
sudo apt install -y git libonnxruntime-dev libsdl2-dev
```

The `scripts/packages/install-ubuntu.sh` (or the `scripts/packages/install-debian.sh`) script installs them together with the rest of the required packages. The Ubuntu 24.04 has no `libonnxruntime-dev` package, so the build downloads the prebuilt onnxruntime there. On RPM-based distributions the equivalent packages are `onnxruntime-devel` and `SDL2-devel`; on FreeBSD they are `misc/onnxruntime` and `devel/sdl20` from `pkg`. See the [Enabling the Piper speech synthesis](/doc/sections/en_US/5-project-build/tts/5-70-enabling-the-Piper-speech-synthesis.md) section for the GPL-3.0-or-later license of the library, which the distributed executable inherits, and for the licenses of the voices.

The [scripts/packages](/scripts/packages) directory holds the scripts which install every package the project needs in one go. The [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) and [install-debian.sh](/scripts/packages/install-debian.sh) ones run the script of the running release - the [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), the [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) or the [install-debian-13.sh](/scripts/packages/install-debian-13.sh) one - since every release names and versions its packages its own way, and fail with the list of the supported releases on any other one. A dependency a release packages no usable version of is built by its script out of a pinned release tag of the dependency sources. The [install-redhat.sh](/scripts/packages/install-redhat.sh) script covers Fedora, RHEL and its rebuilds, and the [install-freebsd.sh](/scripts/packages/install-freebsd.sh) one covers FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
