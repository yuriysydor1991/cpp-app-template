## Enabling the whisper.cpp speech recognition

In order to enable the [whisper.cpp](https://github.com/ggml-org/whisper.cpp) speech recognition library (the C/C++ port of the OpenAI [Whisper](https://github.com/openai/whisper) model) for the project set an `ON` value to the `ENABLE_WHISPERCPP` CMake variable (it is the default one for the `appWhisperCPP` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_WHISPERCPP=ON
cmake --build build --target all
```

The [cmake/enablers/ai/template-project-whispercpp-enabler.cmake](/cmake/enablers/ai/template-project-whispercpp-enabler.cmake) module probes the system installed whisper.cpp first. The Ubuntu 26.04 and the Debian forky ship it's development package (the `scripts/packages/install-ubuntu.sh` and the `scripts/packages/install-debian.sh` scripts install it wherever it is available):

```
sudo apt install -y libwhisper-dev
```

Without it the `TEMPLATE_APP_WHISPERCPP_GIT_TAG` tag (the `v1.9.4` by default) of the `TEMPLATE_APP_WHISPERCPP_GIT` repository gets fetched and built through the Internet. Both ways provide the very same `whisper` target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} whisper)
```

The fetched sources build the [ggml](https://github.com/ggml-org/ggml) tensor library for the CPU of the building machine, so pass the `-DGGML_NATIVE=OFF` option to the build meant to run on the other machines too (the flatpak and the snap packagers of the branch do it).

### The model

The whisper.cpp transcribes the speech with a [ggml model](https://huggingface.co/ggerganov/whisper.cpp) of the Whisper, which is no part of the build. Set the `ENABLE_WHISPERCPP_MODEL_DOWNLOAD` CMake variable to download the `TEMPLATE_APP_WHISPERCPP_MODEL` one (the English only `base.en` of 142 MiB by default) into the `models` directory of the build tree while configuring:

```
cmake -S . -B build -DENABLE_WHISPERCPP_MODEL_DOWNLOAD=ON -DTEMPLATE_APP_WHISPERCPP_MODEL=base
```

| Variable | What it holds |
| --- | --- |
| `TEMPLATE_APP_WHISPERCPP_MODEL` | the model to download, e.g. the `tiny`, the `base`, the `small`, the `large-v3-turbo` one or the English only `.en` variant of them |
| `ENABLE_WHISPERCPP_MODEL_DOWNLOAD` | downloads the model while configuring, `OFF` by default |
| `PROJECT_WHISPER_MODEL_PATH` | the model the application loads while the `--model` (or `-m`) command line parameter gives none, the downloaded one if empty |
| `PROJECT_WHISPER_LANGUAGE` | the spoken language code (`en`, `uk`, `de` etc.) the multilingual models transcribe, `auto` to detect it |

The English only models transcribe the English whatever the `PROJECT_WHISPER_LANGUAGE` value is. Any model of the [whisper.cpp models](https://github.com/ggml-org/whisper.cpp/tree/master/models) list does, so download one by hand and point at it with the command line parameter as well:

```
./src/CppAppTemplate --model /path/to/ggml-small.bin
```

### The components

The [src/WhisperCPP](/src/WhisperCPP) directory holds three small classes of the `whisperi` namespace:

| Class | What it does |
| --- | --- |
| `Microphone` | captures the default microphone of the system through the SDL2 audio subsystem, see the [Enabling the SDL2 microphone capture](/doc/sections/en_US/5-project-build/audio/5-59-enabling-the-SDL2-microphone-capture.md) section |
| `UtteranceDetector` | cuts the captured audio into the utterances at the pauses of the speech |
| `WhisperController` | loads the whisper model, listens to the `Microphone` and transcribes the utterances the `UtteranceDetector` completes |

The `init` call of the `whisperi::WhisperController` class of the [src/WhisperCPP/WhisperController.h](/src/WhisperCPP/WhisperController.h) file loads the model and takes the spoken language. Every `listen` call captures the microphone for the next 100 ms (opening it on the very first call) and returns the text of the utterance completed meanwhile, the empty one while nothing complete is said yet, or the `std::nullopt` on a failure. The `transcribe` call recognizes the given mono samples of the 16 kHz rate, a decoded audio file for example:

```
auto whisper = whisperi::WhisperController::create();

if (whisper->init("models/ggml-base.en.bin", "auto")) {
  while (keepListening) {
    if (const auto text = whisper->listen(); text && !text->empty()) {
      LOGI(*text);
    }
  }
}
```

The `UtteranceDetector` tells the speech by it's loudness: a 30 ms frame three times louder than the noise floor of the surroundings is a speech one. An utterance starts 300 ms ahead of the speech, so it's first word comes complete, and ends with a 750 ms pause or at the 15 s length. The constants of the [src/WhisperCPP/UtteranceDetector.h](/src/WhisperCPP/UtteranceDetector.h) file tune it.

The whisper.cpp and the ggml messages go into the project log: the errors and the warnings at their own levels, the info ones at the debug level and the rest at the trace one, so raise the `MAX_LOG_LEVEL` CMake variable to see them. The very first `init` call loads the backends of the ggml built with the dynamically loaded ones, the Debian package one for example, which computes nothing without them.

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file logs every recognized utterance through the `LOGI` macro till the Ctrl+C keys stop it, so replace the logging with your own handling of the speech.

### The tests

The `UTEST_WhisperController` and the `CTEST_WhisperController` tests transcribe with the empty model of the whisper.cpp own tests (the one holding no weights, so it recognizes no text) and the [speech sample](https://github.com/ggml-org/whisper.cpp/tree/master/samples) of it's sources, both downloaded while configuring the tests. The `disk` audio driver of the SDL2 plays that sample into the microphone of the component test, which recognizes it's words with the `PROJECT_WHISPER_MODEL_PATH` model once it is downloaded. The test cases needing an unavailable file skip themselves.

### Packaging

The DEB package depends on the whisper.cpp, the ggml and the SDL2 ones the executable links against through the `dpkg-shlibdeps` tool. The flatpak builds the whisper.cpp from it's sources first and takes the SDL2 of the freedesktop runtime, while the snap fetches the whisper.cpp through the enabler and stages the SDL2. The fetched whisper.cpp installs it's libraries next to the executable (and it's headers too), so the packages built without the system one carry them.

No package carries a model, so pass one with the `--model` parameter. The flatpak reads it from the home directory and records the microphone through the PulseAudio socket, while the snap needs it's `audio-record` interface connected by hand:

```
sudo snap connect cppapptemplate:audio-record
```
