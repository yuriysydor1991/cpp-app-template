## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appWhisperCPP` branch additionally needs the development files of the [whisper.cpp](https://github.com/ggml-org/whisper.cpp) speech recognition library and of the [SDL2](https://www.libsdl.org/) one it captures the microphone with:

```
sudo apt install -y libwhisper-dev libsdl2-dev
```

The `scripts/packages/install-ubuntu.sh` (or the `scripts/packages/install-debian.sh`) script installs them together with the rest of the required packages. The whisper.cpp package arrived with the Ubuntu 26.04 and the Debian forky releases, so on the older ones it's sources get fetched and built through the Internet instead. On RPM-based distributions the equivalent packages are `whisper-cpp-devel` and `SDL2-devel`; on FreeBSD they are `audio/whisper.cpp` and `devel/sdl20` from `pkg`. The speech recognition needs a model too, see the [Enabling the whisper.cpp speech recognition](/doc/sections/en_US/5-project-build/ai/5-58-enabling-the-whisper-cpp-speech-recognition.md) section.
