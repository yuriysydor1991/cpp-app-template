## Enabling the eSpeak NG speech synthesis

In order to enable the [eSpeak NG](https://github.com/espeak-ng/espeak-ng) speech synthesis library (the compact formant synthesizer of more than a hundred languages and accents) for the project set an `ON` value to the `ENABLE_ESPEAK_NG` CMake variable (it is the default one for the `appESpeakNG` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_ESPEAK_NG=ON
cmake --build build --target all
```

The application of this branch is built around the eSpeak NG, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

The [cmake/enablers/tts/template-project-espeak-ng-enabler.cmake](/cmake/enablers/tts/template-project-espeak-ng-enabler.cmake) module takes the system installed eSpeak NG through the `espeak-ng` module of the `pkg-config` tool, since the library reads the voices data of it's installation at the run time. Install it's development package (the `scripts/packages` scripts do it):

```
sudo apt install -y pkg-config libespeak-ng-dev
```

On RPM-based distributions the package is the `espeak-ng-devel` one, on FreeBSD the `audio/espeak-ng` one. Without the library the configure fails with a message naming them, while a custom installation is found through the `PKG_CONFIG_PATH` environment variable pointing at it's `espeak-ng.pc` file. The enabler provides the `ESpeakNG::espeak-ng` target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} ESpeakNG::espeak-ng)
```

| Variable | What it holds |
| --- | --- |
| `PROJECT_TTS_TEXT` | the text the application speaks while the `--text` (or `-t`) command line parameter gives none, the `Hello, eSpeak NG! Insert your text here!` one by default |
| `PROJECT_TTS_VOICE` | the voice the application speaks with while the `--voice` (or `-s`) command line parameter gives none, the `en` one by default |

### The license

The eSpeak NG is licensed under the [GPL-3.0-or-later](https://github.com/espeak-ng/espeak-ng/blob/master/COPYING) license. The executable links the library, so the executable distributed to the others (in a package, an image or as is) is a combined work with it and has to be distributed under the terms of the GPL-3.0 (or a later version) as a whole: with it's complete corresponding sources and the same rights granted to it's users. The own sources of the project may keep a GPL compatible license of their own, while a project which can not distribute it's executable that way picks a speech engine of another license instead. The packages of the branch (the DEB, the flatpak, the snap etc.) carry the library or depend on it, so they fall under these terms as well.

### The voices

The eSpeak NG names it's voices by the language codes (`en`, `uk`, `de`, `fr` etc.), by the accent ones (`en-us`, `en-gb-scotland` etc.) or by the full ones (`gmw/en-US`), and adds a variant after the plus sign (`en+f3` for a female one). The `espeak-ng --voices` command lists the installed voices, the `espeak-ng --voices=uk` one the voices of a single language. The library speaks every voice at the 22.05 kHz rate.

The very first synthesis initializes the library through the data path of it's installation, while the `ESPEAK_DATA_PATH` environment variable points at another `espeak-ng-data` directory (or at the directory holding it):

```
ESPEAK_DATA_PATH=/opt/espeak-ng/share ./src/CppAppTemplate --voice uk --text "Привіт!"
```

### The components

The [src/ESpeakNG](/src/ESpeakNG) directory holds the single `espeakng::ESpeakNGController` class, the speech engine of the branch. It implements the `tts::ISpeechSynthesizer` interface of the engine neutral [src/TTS](/src/TTS) sources:

| Class | What it does |
| --- | --- |
| `tts::Speech` | keeps the synthesized mono 16-bit samples with their rate and duration |
| `tts::ISpeechSynthesizer` | the interface of the speech engines: speaks the given text with the given voice into the `tts::Speech`, the `create` call gives the engine the build links in |
| `tts::WavWriter` | writes the `tts::Speech` into the 16-bit PCM mono WAV file |
| `tts::AudioPlayer` | plays the `tts::Speech` through the default audio playback device, see the [Enabling the SDL2 audio playback](/doc/sections/en_US/5-project-build/audio/5-68-enabling-the-SDL2-audio-playback.md) section |
| `espeakng::ESpeakNGController` | synthesizes the speech with the eSpeak NG |

The `synthesize` call of the controller initializes the library on the very first call (in the synchronous mode, where the call returns with the whole speech collected), selects the voice and synthesizes the UTF-8 text, giving the `std::nullopt` on a failure: the initialization one, the unknown voice one or the synthesis one, each logged through the `LOGE` macro. The controller destruction terminates the library, which keeps a single state per process, so keep a single controller at a time:

```
auto synthesizer = tts::ISpeechSynthesizer::create();

if (const auto speech = synthesizer->synthesize("Привіт, світе!", "uk")) {
  tts::WavWriter::create()->write(*speech, "speech.wav");
}
```

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file speaks the text and the voice of the command line, writing the speech into the WAV file of the `--output` (or `-o`) parameter or playing it otherwise. It knows the interfaces of the `src/TTS` sources alone, so another engine takes the place of the eSpeak NG by a `src/<engine>` directory of it's own, which defines the `tts::ISpeechSynthesizer::create` call, and an enabler of it: the `appRHVoice`, the `appPiperTTS` and the `appSherpaONNX` branches do exactly that.

### The tests

The `UTEST_ESpeakNGController` test drives the controller over a mock of the eSpeak NG library calls, so every failure of the library is covered, while the `CTEST_ESpeakNGController` and the `CTEST_app` ones synthesize the English and the Ukrainian speech with the real library, check the written WAV files and play the speech through the `dummy` audio driver of the SDL2, so no sound card takes part.

### Packaging

The DEB package depends on the eSpeak NG and the SDL2 ones the executable links against through the `dpkg-shlibdeps` tool, and the `libespeak-ng1` package brings the voices data along. The flatpak builds the `1.52.0` release of the eSpeak NG from it's sources with the voices data into the `/app/share/espeak-ng-data` directory and takes the SDL2 of the freedesktop runtime, while the snap stages the eSpeak NG, it's data and the SDL2 of the Ubuntu archive and points the `ESPEAK_DATA_PATH` variable at the staged data. The flatpak plays the speech through the PulseAudio socket and writes the `--output` files into the home directory, while the snap plays it through the `audio-playback` interface.
