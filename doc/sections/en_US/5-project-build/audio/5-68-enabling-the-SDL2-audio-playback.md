## Enabling the SDL2 audio playback

In order to play the synthesized speech through the default audio playback device of the system with the audio subsystem of the [SDL2](https://www.libsdl.org/) library set an `ON` value to the `ENABLE_SDL2_AUDIO` CMake variable (it is the default one for the text to speech branches):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_SDL2_AUDIO=ON
cmake --build build --target all
```

The [cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake](/cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake) module probes the system installed SDL2 first (the `libsdl2-dev` package, which the `scripts/packages` scripts install) and fetches the `TEMPLATE_APP_SDL2_GIT_TAG` tag (the `release-2.32.10` by default) of the `TEMPLATE_APP_SDL2_GIT` repository through the Internet otherwise. The found target lands in the `TEMPLATE_APP_SDL2_AUDIO_TARGET` variable, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} ${TEMPLATE_APP_SDL2_AUDIO_TARGET})
```

### The player

The `tts::AudioPlayer` class of the [src/TTS/AudioPlayer.h](/src/TTS/AudioPlayer.h) file opens the default playback device for the mono 16-bit samples of the speech rate with no callback, so the SDL2 plays the queued speech on a thread of it's own, converting it into whatever the device plays. The `play` call waits till the device plays the speech out, or till the given check asks to stop, which the Application ties to the Ctrl+C keys:

```
const tts::Speech speech{samples, 22050};

tts::AudioPlayer::create()->play(speech, [] { return false; });
```

The speech goes through the same player whatever engine synthesizes it, so the text to speech branches share the class.

The `SDL_AUDIODRIVER` environment variable picks the audio driver (the `pipewire`, the `pulseaudio`, the `alsa` one etc.). The demand only `dummy` and `disk` drivers are picked by it alone: the first one plays the speech into nowhere at the real time pace, while the second one writes the played samples into the `SDL_DISKAUDIOFILE` file (the `sdlaudio.raw` one by default) with the `SDL_DISKAUDIODELAY` milliseconds in between of the device buffers, so the tests use them in place of a real device:

```
SDL_AUDIODRIVER=dummy ./src/CppAppTemplate
SDL_AUDIODRIVER=disk SDL_DISKAUDIOFILE=speech.raw ./src/CppAppTemplate
```

The SDL3 based [sdl2-compat](https://github.com/libsdl-org/sdl2-compat) library, which replaces the SDL2 on some of the newer distributions, writes the `SDL_AUDIO_DISK_OUTPUT_FILE` file instead, at the pace of the `SDL_AUDIO_DISK_TIMESCALE` factor, and converts the speech into the format of it's own device for it.
