## Enabling the RHVoice speech synthesis

In order to enable the [RHVoice](https://github.com/RHVoice/RHVoice) speech synthesis library (the statistical parametric synthesizer of the English, the Ukrainian, the Russian, the Polish and a dozen of other languages) for the project set an `ON` value to the `ENABLE_RHVOICE` CMake variable (it is the default one for the `appRHVoice` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_RHVOICE=ON
cmake --build build --target all
```

The application of this branch is built around the RHVoice, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

The [cmake/enablers/tts/template-project-rhvoice-enabler.cmake](/cmake/enablers/tts/template-project-rhvoice-enabler.cmake) module takes the system installed RHVoice by it's `RHVoice.h` header and it's `RHVoice` library, since no RHVoice installation ships a `pkg-config` or a CMake package file, and the library reads the voices data of it's installation at the run time. Install it's development package together with the voices (the `scripts/packages` scripts do it):

```
sudo apt install -y librhvoice-dev rhvoice-english rhvoice-ukrainian
```

| Distribution | Packages |
| --- | --- |
| Ubuntu 24.04, 26.04 | the `librhvoice-dev`, `rhvoice-english` and `rhvoice-ukrainian` ones of the `multiverse` component, which the Ubuntu enables by default |
| Debian 13 | the same ones of the `non-free` component alone, since a part of the voices forbids the commercial use or the modifications: append the `non-free` to the `Components: main` line of the `/etc/apt/sources.list.d/debian.sources` file (or to the `deb` lines of the `/etc/apt/sources.list` one) and run the `sudo apt update` |
| Fedora, RHEL | no package: the `scripts/packages/install-redhat.sh` script builds the `1.18.4` release out of it's sources with the English and the Ukrainian data into the `/usr/local` prefix |
| FreeBSD | the `audio/rhvoice` port (the `rhvoice` package) with it's voices |

Without the library the configure fails with a message naming them, while a custom installation is found through the `CMAKE_PREFIX_PATH` variable pointing at it's prefix. The enabler provides the `RHVoice::RHVoice` target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} RHVoice::RHVoice)
```

| Variable | What it holds |
| --- | --- |
| `PROJECT_TTS_TEXT` | the text the application speaks while the `--text` (or `-t`) command line parameter gives none, the `Hello, RHVoice! Insert your text here!` one by default |
| `PROJECT_TTS_VOICE` | the voice the application speaks with while the `--voice` (or `-s`) command line parameter gives none, the `Alan` one by default |

### The license

The RHVoice library is licensed under the [LGPL-2.1-or-later](https://github.com/RHVoice/RHVoice/blob/master/doc/en/License.md) license (a build with the optional MAGE engine falls under the GPL-3.0-or-later one, while the packages above and the source build of the branch leave it out). The executable links the shared library, so the executable distributed to the others keeps the license of the project sources, while the library itself stays a replaceable one under it's own terms: ship it's sources (or a written offer of them) along with a package carrying the library.

The voices carry the licenses of their own: the English Alan, Bdl, Clb and Slt ones and the Ukrainian Anatol and Natalia ones are free, the Ukrainian Marianna and Volodymyr ones forbid the modifications (the CC-BY-ND-4.0), while the English Evgeniy-Eng and Lyubov ones forbid the commercial use as well (the CC-BY-NC-ND-4.0), which is the reason the Debian keeps the RHVoice in it's `non-free` component. Check the `/usr/share/doc/rhvoice-*/copyright` files ahead of distributing a voice along with the project or using it commercially.

### The voices

The RHVoice names it's voices by the speaker names: the `Alan`, `Bdl`, `Clb`, `Slt`, `Evgeniy-Eng` and `Lyubov` voices of the `rhvoice-english` package speak the English, the `Anatol`, `Natalia`, `Marianna` and `Volodymyr` voices of the `rhvoice-ukrainian` one speak the Ukrainian. The names ignore the letter case, and a voice profile of the voices of different languages (the `Anatol+Alan` one) switches to the second voice for the words of it's language. The voices of these packages speak at the 24 kHz rate, and the `/usr/share/RHVoice/voices` directory (the `/usr/local/share/RHVoice/voices` one of the FreeBSD and the source build) lists the installed voices.

The very first synthesis creates the engine out of the data path of the installation, while the `RHVOICE_DATA_PATH` environment variable points at another directory of the `languages` and `voices` subdirectories, and the `RHVOICE_CONFIG_PATH` one at another directory of the `RHVoice.conf` file (the `/etc/RHVoice` one by default), which tunes the rate, the pitch and the volume of the voices:

```
RHVOICE_DATA_PATH=/opt/rhvoice/share/RHVoice ./src/CppAppTemplate --voice Natalia --text "Привіт!"
```

### The components

The [src/RHVoice](/src/RHVoice) directory holds the single `rhvoice::RHVoiceController` class, the speech engine of the branch. It implements the `tts::ISpeechSynthesizer` interface of the engine neutral [src/TTS](/src/TTS) sources:

| Class | What it does |
| --- | --- |
| `tts::Speech` | keeps the synthesized mono 16-bit samples with their rate and duration |
| `tts::ISpeechSynthesizer` | the interface of the speech engines: speaks the given text with the given voice into the `tts::Speech`, the `create` call gives the engine the build links in |
| `tts::WavWriter` | writes the `tts::Speech` into the 16-bit PCM mono WAV file |
| `tts::AudioPlayer` | plays the `tts::Speech` through the default audio playback device, see the [Enabling the SDL2 audio playback](/doc/sections/en_US/5-project-build/audio/5-68-enabling-the-SDL2-audio-playback.md) section |
| `rhvoice::RHVoiceController` | synthesizes the speech with the RHVoice |

The `synthesize` call of the controller creates the RHVoice engine on the very first call, speaks the UTF-8 text with the voice into a message of the engine and collects the sample rate and the samples the engine hands over to the callbacks of it, giving the `std::nullopt` on a failure: the no voices one, the unknown voice (or the empty text) one or the synthesis one, each logged through the `LOGE` macro. The controller destruction deletes the engine:

```
auto synthesizer = tts::ISpeechSynthesizer::create();

if (const auto speech = synthesizer->synthesize("Привіт, світе!", "Anatol")) {
  tts::WavWriter::create()->write(*speech, "speech.wav");
}
```

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file speaks the text and the voice of the command line, writing the speech into the WAV file of the `--output` (or `-o`) parameter or playing it otherwise. It knows the interfaces of the `src/TTS` sources alone, so another engine takes the place of the RHVoice by a `src/<engine>` directory of it's own, which defines the `tts::ISpeechSynthesizer::create` call, and an enabler of it: the `appESpeakNG`, the `appPiperTTS` and the `appSherpaONNX` branches do exactly that.

### The tests

The `UTEST_RHVoiceController` test drives the controller over a mock of the RHVoice library calls, so every failure of the library is covered, while the `CTEST_RHVoiceController` and the `CTEST_app` ones synthesize the English and the Ukrainian speech with the real library and voices, check the written WAV files and play the speech through the `dummy` audio driver of the SDL2, so no sound card takes part. The component tests need the `Alan`, `Anatol` and `Natalia` voices installed.

### Packaging

The DEB package depends on the RHVoice and the SDL2 ones the executable links against through the `dpkg-shlibdeps` tool, and the `librhvoice5` package brings the RHVoice core and an English voice along. The flatpak builds the `1.18.4` release of the RHVoice from it's sources together with the English and the Ukrainian data and the `Alan`, `Anatol` and `Natalia` voices into the `/app/share/RHVoice` directory and takes the SDL2 of the freedesktop runtime, while the snap stages the RHVoice, the English and the Ukrainian voices and the SDL2 of the Ubuntu archive and points the `RHVOICE_DATA_PATH` and the `RHVOICE_CONFIG_PATH` variables at the staged data. The flatpak plays the speech through the PulseAudio socket and writes the `--output` files into the home directory, while the snap plays it through the `audio-playback` interface.
