## Enabling the SDL2 microphone capture

In order to capture the default microphone of the system through the audio subsystem of the [SDL2](https://www.libsdl.org/) library set an `ON` value to the `ENABLE_SDL2_AUDIO` CMake variable (it is the default one for the `appWhisperCPP` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_SDL2_AUDIO=ON
cmake --build build --target all
```

The whisper.cpp examples capture the microphone through the very same library. The [cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake](/cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake) module probes the system installed SDL2 first (the `libsdl2-dev` package, which the `scripts/packages` scripts install) and fetches the `TEMPLATE_APP_SDL2_GIT_TAG` tag (the `release-2.32.10` by default) of the `TEMPLATE_APP_SDL2_GIT` repository through the Internet otherwise. The found target lands in the `TEMPLATE_APP_SDL2_AUDIO_TARGET` variable, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} ${TEMPLATE_APP_SDL2_AUDIO_TARGET})
```

### The microphone

The `whisperi::Microphone` class of the [src/WhisperCPP/Microphone.h](/src/WhisperCPP/Microphone.h) file opens the default capture device with no callback, so the SDL2 queues the captured audio on a thread of it's own, converting it into the mono float samples of the requested rate, and every `read` call takes the samples queued since the previous one:

```
whisperi::Microphone microphone;

if (microphone.open(16000)) {
  const auto samples = microphone.read();
}
```

The `SDL_AUDIODRIVER` environment variable picks the audio driver (the `pipewire`, the `pulseaudio`, the `alsa` one etc.). The demand only `dummy` and `disk` drivers are picked by it alone: the first one captures the silence, while the second one captures the raw samples of the `SDL_DISKAUDIOFILEIN` file in the very format the application asks for (the 32 bit float mono samples of the 16 kHz rate here), so the tests use them in place of a real device:

```
SDL_AUDIODRIVER=disk SDL_DISKAUDIOFILEIN=speech.raw ./src/CppAppTemplate
```
