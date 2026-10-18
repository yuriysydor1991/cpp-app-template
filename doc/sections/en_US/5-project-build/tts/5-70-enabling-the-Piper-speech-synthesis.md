## Enabling the Piper speech synthesis

In order to enable the [Piper](https://github.com/OHF-Voice/piper1-gpl) speech synthesis library (the fast local neural text to speech of the many languages, the `libpiper` C/C++ library of it) for the project set an `ON` value to the `ENABLE_PIPER` CMake variable (it is the default one for the `appPiperTTS` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_PIPER=ON
cmake --build build --target all
```

The application of this branch is built around the Piper, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

No system packages the `libpiper`, so the [cmake/enablers/tts/template-project-piper-enabler.cmake](/cmake/enablers/tts/template-project-piper-enabler.cmake) module builds it from the sources of the `v1.8.0` release (the `TEMPLATE_APP_PIPER_GIT` and the `TEMPLATE_APP_PIPER_GIT_TAG` variables) as a separate CMake project inside the `<build>/piper` directory, away from the project warnings and checks. The `libpiper` build fetches and builds the pinned [espeak-ng](https://github.com/espeak-ng/espeak-ng) it phonemizes the text with statically along with it's `espeak-ng-data`, so it needs the git and the internet access. The [onnxruntime](https://onnxruntime.ai/) runs the voices: the enabler takes the system installed one through it's CMake package, while the `libpiper` build downloads the prebuilt `1.22.0` one of the GNU/Linux (x86-64, ARM), the MS Windows or the macOS otherwise. Install it's development package where the system has one (the `scripts/packages` scripts do it):

```
sudo apt install -y libonnxruntime-dev
```

The Debian 13 and the Ubuntu 26.04 package it as the `libonnxruntime-dev`, the Fedora as the `onnxruntime-devel`, the FreeBSD as the `misc/onnxruntime` (the prebuilt one is no FreeBSD option), while the Ubuntu 24.04 has none and takes the downloaded one. The onnxruntime of the Ubuntu 26.04 prints the harmless `Schema error` lines into the standard error while a voice loads. A custom onnxruntime installation is found through the `CMAKE_PREFIX_PATH` variable. The espeak-ng limits it's data paths to 160 characters, so keep the build directory path below 90 characters or so, or the espeak-ng data compilation aborts with the `buffer overflow detected` message. The enabler provides the `Piper::piper` target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} Piper::piper)
```

| Variable | What it holds |
| --- | --- |
| `PROJECT_TTS_TEXT` | the text the application speaks while the `--text` (or `-t`) command line parameter gives none, the `Hello, Piper! Insert your text here!` one by default |
| `PROJECT_TTS_VOICE` | the voice model the application speaks with while the `--voice` (or `-s`) command line parameter gives none, the downloaded `<build>/voices/<TEMPLATE_APP_PIPER_VOICE>.onnx` one if empty |
| `TEMPLATE_APP_PIPER_VOICE` | the voice the configure downloads, the `en_US-lessac-medium` one by default |
| `ENABLE_PIPER_VOICE_DOWNLOAD` | downloads the `TEMPLATE_APP_PIPER_VOICE` voice into the `<build>/voices` directory while configuring, `ON` by default |
| `TEMPLATE_APP_PIPER_VOICES_URL` | the pinned revision of the [rhasspy/piper-voices](https://huggingface.co/rhasspy/piper-voices) repository the voice is downloaded from |

### The license

The Piper is licensed under the [GPL-3.0-or-later](https://github.com/OHF-Voice/piper1-gpl/blob/main/COPYING) license, the espeak-ng it builds in under the GPL-3.0-or-later as well. The executable links the library, so the executable distributed to the others (in a package, an image or as is) is a combined work with it and has to be distributed under the terms of the GPL-3.0 (or a later version) as a whole: with it's complete corresponding sources and the same rights granted to it's users. The own sources of the project may keep a GPL compatible license of their own, while a project which can not distribute it's executable that way picks a speech engine of another license instead. The packages of the branch (the DEB, the flatpak, the snap etc.) carry the library, so they fall under these terms as well, while the onnxruntime is licensed under the MIT license.

Every voice has a license of it's own, the one of the dataset it is trained on, which the `MODEL_CARD` file beside the voice in the voices repository names: the `en_US-lessac-medium` voice is trained on the [Lessac Blizzard 2013](https://www.cstr.ed.ac.uk/projects/blizzard/2013/lessac_blizzard2013/license.html) dataset of it's own license terms, the `uk_UA-ukrainian_tts-medium` one on the CC0 dataset. Review the license of the voice before distributing it or the speech of it. The voices are no part of the packages of the branch.

### The voices

The Piper voice is the `.onnx` model with the `.onnx.json` config of the same name beside it, named by the language, the region, the name and the quality (`en_US-lessac-medium`). The configure downloads the `TEMPLATE_APP_PIPER_VOICE` voice into the `<build>/voices` directory, checking the SHA256 checksums of the known voices, so the application of the build directory speaks with it. The `--voice` (or `-s`) parameter takes the path of any other voice, e.g. the Ukrainian `uk_UA-ukrainian_tts-medium` one:

```
cmake -S . -B build -DTEMPLATE_APP_PIPER_VOICE=uk_UA-ukrainian_tts-medium
cmake --build build
./build/src/CppAppTemplate --voice build/voices/uk_UA-ukrainian_tts-medium.onnx --text "Привіт, світе!"
```

The [VOICES.md](https://github.com/OHF-Voice/piper1-gpl/blob/main/docs/VOICES.md) file lists the voices and their samples. The medium quality voices speak at the 22.05 kHz rate, while the speech takes the rate of the voice config. The installed application has no voice of it's own, so it needs the `--voice` parameter (or a `PROJECT_TTS_VOICE` path given to the configure).

The controller hands the `espeak-ng-data` directory beside the loaded `libpiper` over to the library (the `<build>/piper/lib` one of the build directory or the `<prefix>/lib/<project>` one of the installation), so the build directory and the relocated installations (the DEB, the snap, the AppImage etc.) find it alike, while the `ESPEAK_DATA_PATH` environment variable takes it's place when it is missing. The `libpiper` initializes the espeak-ng so, that a missing data ends the whole process with the `Error processing file` message of the espeak-ng.

### The components

The [src/PiperTTS](/src/PiperTTS) directory holds the single `pipertts::PiperController` class, the speech engine of the branch. It implements the `tts::ISpeechSynthesizer` interface of the engine neutral [src/TTS](/src/TTS) sources:

| Class | What it does |
| --- | --- |
| `tts::Speech` | keeps the synthesized mono 16-bit samples with their rate and duration |
| `tts::ISpeechSynthesizer` | the interface of the speech engines: speaks the given text with the given voice into the `tts::Speech`, the `create` call gives the engine the build links in |
| `tts::WavWriter` | writes the `tts::Speech` into the 16-bit PCM mono WAV file |
| `tts::AudioPlayer` | plays the `tts::Speech` through the default audio playback device, see the [Enabling the SDL2 audio playback](/doc/sections/en_US/5-project-build/audio/5-68-enabling-the-SDL2-audio-playback.md) section |
| `pipertts::PiperController` | synthesizes the speech with the Piper |

The `synthesize` call of the controller loads the voice on the very first call with it and reuses it next time, while another voice replaces it. It synthesizes the UTF-8 text chunk by chunk, converting the floating point samples of the Piper into the 16-bit ones of the voice rate, and gives the `std::nullopt` on a failure: the missing voice one, the voice load one (the broken files the `libpiper` reports with the exceptions included) or the synthesis one, each logged through the `LOGE` macro. The espeak-ng keeps a single state per process, so keep a single controller at a time:

```
auto synthesizer = tts::ISpeechSynthesizer::create();

if (const auto speech = synthesizer->synthesize("Hello!", "voices/en_US-lessac-medium.onnx")) {
  tts::WavWriter::create()->write(*speech, "speech.wav");
}
```

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file speaks the text and the voice of the command line, writing the speech into the WAV file of the `--output` (or `-o`) parameter or playing it otherwise. It knows the interfaces of the `src/TTS` sources alone, so another engine takes the place of the Piper by a `src/<engine>` directory of it's own, which defines the `tts::ISpeechSynthesizer::create` call, and an enabler of it: the `appESpeakNG`, the `appRHVoice` and the `appSherpaONNX` branches do exactly that.

### The tests

The `UTEST_PiperController` test drives the controller over a mock of the `libpiper` calls, so every failure of the library is covered, while the `CTEST_PiperController` and the `CTEST_app` ones synthesize the English speech with the real library and the downloaded voice, check the written WAV files and play the speech through the `dummy` audio driver of the SDL2, so no sound card takes part. The cases speaking with the downloaded voice are skipped when the `ENABLE_PIPER_VOICE_DOWNLOAD` option is turned `OFF`.

### Packaging

The installation (and so the DEB, the RPM and the other packages) carries the `libpiper`, the downloaded onnxruntime (when no system one is taken) and the `espeak-ng-data` in the `<prefix>/lib/<project>` directory, where the executable finds them through it's `$ORIGIN` relative run path, while the DEB depends on the system onnxruntime and the SDL2 packages through the `dpkg-shlibdeps` tool. The flatpak and the snap build the `libpiper` the same way with the network access, take the SDL2 of the runtime (the snap of the Ubuntu archive) and download no voice. The flatpak plays the speech through the PulseAudio socket and reads the voices and writes the `--output` files in the home directory, while the snap plays it through the `audio-playback` interface.
