## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appESpeakNG` branch additionally needs the development files of the [eSpeak NG](https://github.com/espeak-ng/espeak-ng) speech synthesis library, which the configure finds through the `pkg-config` tool, and of the [SDL2](https://www.libsdl.org/) one it plays the speech with:

```
sudo apt install -y pkg-config libespeak-ng-dev libsdl2-dev
```

The `scripts/packages/install-ubuntu.sh` (or the `scripts/packages/install-debian.sh`) script installs them together with the rest of the required packages. On RPM-based distributions the equivalent packages are `espeak-ng-devel`, `SDL2-devel` and `pkgconf-pkg-config`; on FreeBSD they are `audio/espeak-ng`, `devel/sdl20` and `devel/pkgconf` from `pkg`. See the [Enabling the eSpeak NG speech synthesis](/doc/sections/en_US/5-project-build/tts/5-67-enabling-the-eSpeak-NG-speech-synthesis.md) section for the GPL-3.0-or-later license of the library, which the distributed executable inherits.

The [scripts/packages](/scripts/packages) directory holds the scripts which install every package the project needs in one go. The [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) and [install-debian.sh](/scripts/packages/install-debian.sh) ones run the script of the running release - the [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), the [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) or the [install-debian-13.sh](/scripts/packages/install-debian-13.sh) one - since every release names and versions its packages its own way, and fail with the list of the supported releases on any other one. A dependency a release packages no usable version of is built by its script out of a pinned release tag of the dependency sources. The [install-redhat.sh](/scripts/packages/install-redhat.sh) script covers Fedora, RHEL and its rebuilds, and the [install-freebsd.sh](/scripts/packages/install-freebsd.sh) one covers FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
