## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appWhisperCPP` branch additionally needs the development files of the [whisper.cpp](https://github.com/ggml-org/whisper.cpp) speech recognition library and of the [SDL2](https://www.libsdl.org/) one it captures the microphone with:

```
sudo apt install -y libwhisper-dev libsdl2-dev curl
```

The `scripts/packages/install-ubuntu.sh` (or the `scripts/packages/install-debian.sh`) script installs them together with the rest of the required packages. The whisper.cpp package arrived with the Ubuntu 26.04 and the Debian forky releases, so on the older ones it's sources get fetched and built through the Internet instead. On RPM-based distributions the equivalent packages are `whisper-cpp-devel` and `SDL2-devel`; on FreeBSD they are `audio/whisper.cpp` and `devel/sdl20` from `pkg`. The configure downloads the speech recognition model with the `curl` (or the `wget`) tool, see the [Enabling the whisper.cpp speech recognition](/doc/sections/en_US/5-project-build/ai/5-58-enabling-the-whisper-cpp-speech-recognition.md) section.

The [scripts/packages](/scripts/packages) directory holds the scripts which install every package the project needs in one go. The [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) and [install-debian.sh](/scripts/packages/install-debian.sh) ones run the script of the running release - the [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), the [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) or the [install-debian-13.sh](/scripts/packages/install-debian-13.sh) one - since every release names and versions its packages its own way, and fail with the list of the supported releases on any other one. A dependency a release packages no usable version of is built by its script out of a pinned release tag of the dependency sources. The [install-redhat.sh](/scripts/packages/install-redhat.sh) script covers Fedora, RHEL and its rebuilds, and the [install-freebsd.sh](/scripts/packages/install-freebsd.sh) one covers FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
