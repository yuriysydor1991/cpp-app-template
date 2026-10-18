## Enabling the sherpa-onnx speech synthesis

In order to enable the [sherpa-onnx](https://github.com/k2-fsa/sherpa-onnx) speech synthesis library (the offline neural speech engine of the Kokoro, the MeloTTS, the Piper and the other models on top of the [onnxruntime](https://github.com/microsoft/onnxruntime)) for the project set an `ON` value to the `ENABLE_SHERPA_ONNX` CMake variable (it is the default one for the `appSherpaONNX` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_SHERPA_ONNX=ON
cmake --build build --target all
```

The application of this branch is built around the sherpa-onnx, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

No distribution packages the sherpa-onnx, so the [cmake/enablers/tts/template-project-sherpa-onnx-enabler.cmake](/cmake/enablers/tts/template-project-sherpa-onnx-enabler.cmake) module fetches it's `v1.13.8` release sources through the `FetchContent` (the `git` tool and the internet access are needed) and builds it's C and C++ API libraries alone: no binaries, Python, tests, PortAudio, websocket, GPU or speaker diarization. The sherpa-onnx runs the models with the onnxruntime installed in the system where the distribution packages it (the `libonnxruntime-dev` package of the Ubuntu 26.04 and the Debian 13, the `onnxruntime-devel` one of the Fedora, the `misc/onnxruntime` port of the FreeBSD), and downloads it's own prebuilt one otherwise (the Ubuntu 24.04, the RHEL, the flatpak and the snap builds). The `SHERPA_ONNXRUNTIME_INCLUDE_DIR` and the `SHERPA_ONNXRUNTIME_LIB_DIR` environment variables point the configure at an onnxruntime of a custom location:

```
sudo apt install -y libonnxruntime-dev
SHERPA_ONNXRUNTIME_INCLUDE_DIR=/opt/onnxruntime/include SHERPA_ONNXRUNTIME_LIB_DIR=/opt/onnxruntime/lib cmake -S . -B build
```

The enabler provides the `SherpaONNX::cxx-api` target of the shared C++ API library, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} SherpaONNX::cxx-api)
```

The installation puts the shared sherpa-onnx libraries (and the downloaded onnxruntime one) into the private `lib/CppAppTemplate` directory of the installation prefix (the `lib/<multiarch>/CppAppTemplate` one with the `/usr` prefix), which the installed executable finds them in by it's `$ORIGIN` relative RPATH, so the installed, the packaged and the build tree executables run with no `LD_LIBRARY_PATH` variable.

| Variable | What it holds |
| --- | --- |
| `TEMPLATE_APP_SHERPA_ONNX_GIT`, `TEMPLATE_APP_SHERPA_ONNX_GIT_TAG` | the sherpa-onnx repository and the tag the configure fetches, the `v1.13.8` one by default |
| `PROJECT_TTS_TEXT` | the text the application speaks while the `--text` (or `-t`) command line parameter gives none, the `Hello, sherpa-onnx! Insert your text here!` one by default |
| `PROJECT_TTS_VOICE` | the voice the application speaks with while the `--voice` (or `-s`) command line parameter gives none, the downloaded `TEMPLATE_APP_SHERPA_ONNX_MODEL` one by default |
| `TEMPLATE_APP_SHERPA_ONNX_MODEL` | the model of the sherpa-onnx [tts-models](https://github.com/k2-fsa/sherpa-onnx/releases/tag/tts-models) release the configure downloads, the `kokoro-int8-multi-lang-v1_0` one by default |
| `ENABLE_SHERPA_ONNX_MODEL_DOWNLOAD` | downloads the model into the `models` directory of the build tree while configuring, `ON` by default |
| `TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256` | the SHA256 checksum of the model archive, the known one of the `kokoro-int8-multi-lang-v1_0`, the `kokoro-multi-lang-v1_0`, the `kokoro-int8-en-v0_19`, the `kokoro-en-v0_19`, the `vits-melo-tts-zh_en` and the `vits-piper-en_US-amy-low-int8` models by default |

### The voices

The `--voice` (or `-s`) parameter takes the directory of a model the sherpa-onnx `tts-models` release archives unpack into, optionally followed by the `:<id>` speaker id of a multi-speaker model (the first speaker speaks otherwise). The controller tells the model kind by the files of the directory:

| Model kind | Files of the directory |
| --- | --- |
| Kokoro | the `model.onnx` (or the `model.int8.onnx`), the `voices.bin`, the `tokens.txt`, the `espeak-ng-data` directory and, for the multilingual models, the `lexicon-us-en.txt` and the `lexicon-zh.txt` |
| VITS (Piper, MeloTTS, MMS etc.) | the `model.onnx` (or the `<voice>.onnx` of a Piper one), the `tokens.txt` and either the `espeak-ng-data` directory of the Piper voices or the `lexicon.txt` of the MeloTTS ones |

The default `kokoro-int8-multi-lang-v1_0` model (the 126 MB archive of the int8 quantized [Kokoro-82M](https://huggingface.co/hexgrad/Kokoro-82M) v1.0, 183 MB unpacked) speaks the English and the Chinese text of it's lexicons with it's 54 speakers (the `:0` to `:53` ids of the English, the Chinese, the Spanish, the French, the Hindi, the Italian, the Japanese and the Portuguese voices of the model) at the 24 kHz rate, while the configure downloads and checks it once per build tree. Turn the download off with the `-DENABLE_SHERPA_ONNX_MODEL_DOWNLOAD=OFF` parameter, download another model with the `-DTEMPLATE_APP_SHERPA_ONNX_MODEL=<model>` one, or point the `PROJECT_TTS_VOICE` variable at a model of your own.

The Chinese and English [MeloTTS](https://github.com/myshell-ai/MeloTTS) model and the [Piper](https://github.com/rhasspy/piper) voices speak through the very same parameter:

```
mkdir -p ~/models && cd ~/models
curl -SL -O https://github.com/k2-fsa/sherpa-onnx/releases/download/tts-models/vits-melo-tts-zh_en.tar.bz2
curl -SL -O https://github.com/k2-fsa/sherpa-onnx/releases/download/tts-models/vits-piper-en_US-amy-low-int8.tar.bz2
curl -SL -O https://github.com/k2-fsa/sherpa-onnx/releases/download/tts-models/vits-piper-uk_UA-lada-x_low-int8.tar.bz2
for archive in *.tar.bz2 ; do tar xf "${archive}" ; done

# from the build dir
./src/CppAppTemplate -t "它也支持英文, and English too." -s ~/models/vits-melo-tts-zh_en
./src/CppAppTemplate -t "Hello, Piper!" -s ~/models/vits-piper-en_US-amy-low-int8
./src/CppAppTemplate -t "Привіт, світе!" -s ~/models/vits-piper-uk_UA-lada-x_low-int8
```

The MeloTTS model speaks at the 44.1 kHz rate, the Piper voices at the rate of their model cards (16 kHz for the `x_low` and the `low` ones, 22.05 kHz for the `medium` and the `high` ones). The configure downloads any of them into the build tree as well, e.g. with the `-DTEMPLATE_APP_SHERPA_ONNX_MODEL=vits-melo-tts-zh_en` parameter.

### The licenses

The sherpa-onnx is licensed under the [Apache-2.0](https://github.com/k2-fsa/sherpa-onnx/blob/master/LICENSE) license and the onnxruntime under the [MIT](https://github.com/microsoft/onnxruntime/blob/main/LICENSE) one, so the distributed executable keeps their copyright notices and license texts along. The models are the data of their own licenses: the Kokoro-82M is licensed under the [Apache-2.0](https://huggingface.co/hexgrad/Kokoro-82M) license and the MeloTTS under the [MIT](https://github.com/myshell-ai/MeloTTS/blob/main/LICENSE) one, while every Piper voice carries the license of it's training data set, which the `MODEL_CARD` file of the voice directory names (some of them allow no commercial use). Check the license of the model you distribute with or for your application.

### The components

The [src/SherpaONNX](/src/SherpaONNX) directory holds the speech engine of the branch. It implements the `tts::ISpeechSynthesizer` interface of the engine neutral [src/TTS](/src/TTS) sources:

| Class | What it does |
| --- | --- |
| `tts::Speech` | keeps the synthesized mono 16-bit samples with their rate and duration |
| `tts::ISpeechSynthesizer` | the interface of the speech engines: speaks the given text with the given voice into the `tts::Speech`, the `create` call gives the engine the build links in |
| `tts::WavWriter` | writes the `tts::Speech` into the 16-bit PCM mono WAV file |
| `tts::AudioPlayer` | plays the `tts::Speech` through the default audio playback device, see the [Enabling the SDL2 audio playback](/doc/sections/en_US/5-project-build/audio/5-68-enabling-the-SDL2-audio-playback.md) section |
| `sherpaonnx::SherpaONNXModel` | the model of a directory: detects the model kind by the files of it and gives the sherpa-onnx configuration of the model |
| `sherpaonnx::KokoroModel`, `sherpaonnx::VitsModel` | the Kokoro and the VITS model kinds, which configure the sherpa-onnx out of the files of their own |
| `sherpaonnx::SherpaONNXController` | synthesizes the speech with the sherpa-onnx |

The `synthesize` call of the controller loads the model of the voice directory (and keeps it loaded for the next call with the same directory), checks the speaker id against the speakers of the model, generates the speech and converts it's float samples into the 16-bit ones, giving the `std::nullopt` on a failure: the directory of no known model, the model load one or the unknown speaker one, each logged through the `LOGE` macro:

```
auto synthesizer = tts::ISpeechSynthesizer::create();

if (const auto speech = synthesizer->synthesize("Hello, world!", "models/kokoro-int8-multi-lang-v1_0:3")) {
  tts::WavWriter::create()->write(*speech, "speech.wav");
}
```

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file speaks the text and the voice of the command line, writing the speech into the WAV file of the `--output` (or `-o`) parameter or playing it otherwise. It knows the interfaces of the `src/TTS` sources alone, so another engine takes the place of the sherpa-onnx by a `src/<engine>` directory of it's own, which defines the `tts::ISpeechSynthesizer::create` call, and an enabler of it: the `appESpeakNG`, the `appRHVoice` and the `appPiperTTS` branches do exactly that.

### The tests

The `UTEST_SherpaONNXModel` test checks the model kind detection and the configurations of the Kokoro, the Piper and the MeloTTS directories, the `UTEST_SherpaONNXController` one drives the controller over a mock of the sherpa-onnx C++ API, so every failure of the engine is covered, while the `CTEST_SherpaONNXController` and the `CTEST_app` ones synthesize the English speech of several speakers with the downloaded Kokoro model, check the written WAV files and play the speech through the `dummy` audio driver of the SDL2, so no sound card takes part. The test cases needing the model skip themselves while the configure downloads none.

### Packaging

The DEB package ships the shared sherpa-onnx libraries in it's private library directory and depends on the SDL2 and the onnxruntime packages the libraries link against through the `dpkg-shlibdeps` tool, or ships the downloaded onnxruntime where the distribution packages none. The flatpak and the snap fetch the sherpa-onnx and the prebuilt onnxruntime while building (the flatpak module shares the network for it), and so does the Docker image. None of them carries a model: the flatpak reads the models of the home directory, so pass the `--voice` parameter to them. The flatpak plays the speech through the PulseAudio socket and writes the `--output` files into the home directory, while the snap plays it through the `audio-playback` interface.
