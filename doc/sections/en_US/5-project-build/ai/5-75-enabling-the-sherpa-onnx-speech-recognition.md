## Enabling the sherpa-onnx speech recognition

In order to enable the [sherpa-onnx](https://github.com/k2-fsa/sherpa-onnx) speech recognition library (the offline neural speech engine of the NeMo Parakeet, the Whisper, the Zipformer and the other models on top of the [onnxruntime](https://github.com/microsoft/onnxruntime)) for the project set an `ON` value to the `ENABLE_SHERPA_ONNX` CMake variable (it is the default one for the `appSherpaONNXSTT` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_SHERPA_ONNX=ON
cmake --build build --target all
```

The application of this branch is built around the sherpa-onnx, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

No distribution packages the sherpa-onnx, so the [cmake/enablers/ai/template-project-sherpa-onnx-enabler.cmake](/cmake/enablers/ai/template-project-sherpa-onnx-enabler.cmake) module fetches it's `v1.13.8` release sources through the `FetchContent` (the `git` tool and the internet access are needed) and builds it's C and C++ API libraries alone: no binaries, Python, tests, text to speech, PortAudio, websocket, GPU or speaker diarization. The sherpa-onnx runs the models with the onnxruntime installed in the system where the distribution packages it (the `libonnxruntime-dev` package of the Ubuntu 26.04 and the Debian 13, the `onnxruntime-devel` one of the Fedora, the `misc/onnxruntime` port of the FreeBSD), and downloads it's own prebuilt one otherwise (the Ubuntu 24.04, the RHEL, the flatpak and the snap builds). The `SHERPA_ONNXRUNTIME_INCLUDE_DIR` and the `SHERPA_ONNXRUNTIME_LIB_DIR` environment variables point the configure at an onnxruntime of a custom location:

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
| `PROJECT_STT_MODEL` | the model directory the application recognizes the speech with while the `--model` (or `-m`) command line parameter gives none, the downloaded `TEMPLATE_APP_SHERPA_ONNX_MODEL` one if empty, so nothing gets downloaded once it is given |
| `TEMPLATE_APP_SHERPA_ONNX_MODEL` | the NeMo transducer model of the sherpa-onnx [asr-models](https://github.com/k2-fsa/sherpa-onnx/releases/tag/asr-models) release the configure downloads, the `sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8` one by default |
| `ENABLE_SHERPA_ONNX_MODEL_DOWNLOAD` | downloads the model into the `models` directory of the build tree while configuring and installs it with the binary, `ON` by default |
| `TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256` | the SHA256 checksum of the model archive, the known one of the `sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8`, the `sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8` and the `sherpa-onnx-nemo-fast-conformer-transducer-be-de-en-es-fr-hr-it-pl-ru-uk-20k-int8` models by default |

### The model

The `--model` (or `-m`) parameter takes the directory of a NeMo transducer model (the Parakeet TDT, the FastConformer one etc.) the sherpa-onnx `asr-models` release archives unpack into: the `encoder`, the `decoder` and the `joiner` networks (the `.onnx` files or the quantized `.int8.onnx` ones) and the `tokens.txt` file. The controller names the NeMo transducer kind of the model to the sherpa-onnx, which spares it a load of the encoder for the kind of it's metadata.

The default `sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8` model (the 465 MiB archive of the int8 quantized [Parakeet TDT 0.6B v3](https://huggingface.co/nvidia/parakeet-tdt-0.6b-v3) model of the NVIDIA, 640 MiB unpacked) recognizes the speech of 25 European languages - the Bulgarian, the Croatian, the Czech, the Danish, the Dutch, the English, the Estonian, the Finnish, the French, the German, the Greek, the Hungarian, the Italian, the Latvian, the Lithuanian, the Maltese, the Polish, the Portuguese, the Romanian, the Russian, the Slovak, the Slovenian, the Spanish, the Swedish and the Ukrainian one - detecting the language of every utterance on it's own, and puts the punctuation and the capital letters in. The configure downloads it and checks it's checksum once per build tree, while a failed download only warns, leaving the `--model` parameter the way to give one. Turn the download off with the `-DENABLE_SHERPA_ONNX_MODEL_DOWNLOAD=OFF` parameter, download another model with the `-DTEMPLATE_APP_SHERPA_ONNX_MODEL=<model>` one or point at a model of your own with the `PROJECT_STT_MODEL` variable. The four times smaller `sherpa-onnx-nemo-fast-conformer-transducer-be-de-en-es-fr-hr-it-pl-ru-uk-20k-int8` model, for example, recognizes the Belarusian, the German, the English, the Spanish, the French, the Croatian, the Italian, the Polish, the Russian and the Ukrainian speech:

```
cmake -S . -B build -DTEMPLATE_APP_SHERPA_ONNX_MODEL=sherpa-onnx-nemo-fast-conformer-transducer-be-de-en-es-fr-hr-it-pl-ru-uk-20k-int8
```

Any other NeMo transducer model of the release does too, so download one by hand and point at it with the command line parameter as well:

```
mkdir -p ~/models && cd ~/models
curl -SL -O https://github.com/k2-fsa/sherpa-onnx/releases/download/asr-models/sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8.tar.bz2
tar xf sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8.tar.bz2

# from the build dir
./src/CppAppTemplate --model ~/models/sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8
```

### Installing the model

The downloaded model directory is a part of the build tree, so the install step (and every package built out of it: deb, rpm, AppImage, FreeBSD pkg, the MS Windows installer) copies it, but it's `test_wavs` recordings, into the `share/CppAppTemplate` directory of the installation prefix, the `/usr/share/CppAppTemplate/sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8` one for example, and the installed binary runs with no build tree around. The `app::DataLocator` class of the [src/app/DataLocator.h](/src/app/DataLocator.h) file picks the model the running binary loads while no `--model` parameter is given: the installed one relative to the binary location first (so a relocated package, an AppImage for example, keeps working), then the downloaded one of the build tree (a binary run out of it), then the installed one under the configured prefix. The download turned off or failed installs no model, and the model of the `PROJECT_STT_MODEL` variable gets loaded from where it is.

### Licenses

The sherpa-onnx is distributed under the [Apache-2.0](https://github.com/k2-fsa/sherpa-onnx/blob/master/LICENSE) license and the onnxruntime under the [MIT](https://github.com/microsoft/onnxruntime/blob/main/LICENSE) one, so their copyright notices and license texts accompany a distributed executable. The models are the data of their own licenses: the Parakeet TDT 0.6B v3 one is distributed under the [CC-BY-4.0](https://huggingface.co/nvidia/parakeet-tdt-0.6b-v3) license, which asks for the attribution of the NVIDIA, and the model card of every other model names it's own. Check the license of the model you distribute with or for your application: the packages built with the downloaded model carry it, while the `-DENABLE_SHERPA_ONNX_MODEL_DOWNLOAD=OFF` parameter leaves it out of them.

### The components

The [src/STT](/src/STT) directory holds the engine neutral speech recognition sources of the `stt` namespace, which the [src/SherpaONNX](/src/SherpaONNX) engine of the branch implements the recognizer interface of:

| Class | What it does |
| --- | --- |
| `stt::Microphone` | captures the default microphone of the system through the SDL2 audio subsystem, see the [Enabling the SDL2 microphone capture](/doc/sections/en_US/5-project-build/audio/5-59-enabling-the-SDL2-microphone-capture.md) section |
| `stt::UtteranceDetector` | cuts the captured audio into the utterances at the pauses of the speech |
| `stt::ISpeechRecognizer` | the interface of the speech engines: loads a model and recognizes the text of the given mono samples of the 16 kHz rate, while the `create` call gives the engine the build links in |
| `stt::SpeechListener` | listens to the `Microphone` and recognizes the utterances the `UtteranceDetector` completes with the `ISpeechRecognizer` |
| `sherpaonnx::SherpaONNXController` | loads the NeMo transducer model of a directory and recognizes the speech with the sherpa-onnx |

The `init` call of the `stt::SpeechListener` class of the [src/STT/SpeechListener.h](/src/STT/SpeechListener.h) file loads the model. Every `listen` call captures the microphone for the next 100 ms (opening it on the very first call) and returns the text of the utterance completed meanwhile, the empty one while nothing complete is said yet, or the `std::nullopt` on a failure, which the `LOGE` macro logs. The `recognize` call of the `stt::ISpeechRecognizer` recognizes the given samples, a decoded audio file for example:

```
auto listener = stt::SpeechListener::create();

if (listener->init("models/sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8")) {
  while (keepListening) {
    if (const auto text = listener->listen(); text && !text->empty()) {
      LOGI(*text);
    }
  }
}
```

The `UtteranceDetector` tells the speech by it's loudness: a 30 ms frame three times louder than the noise floor of the surroundings is a speech one. An utterance starts 300 ms ahead of the speech, so it's first word comes complete, and ends with a 750 ms pause or at the 15 s length. The constants of the [src/STT/UtteranceDetector.h](/src/STT/UtteranceDetector.h) file tune it.

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file logs every recognized utterance through the `LOGI` macro till the Ctrl+C keys stop it, so replace the logging with your own handling of the speech. It knows the `src/STT` sources alone, so another engine replaces the sherpa-onnx with a `src/<engine>` directory of it's own defining the `stt::ISpeechRecognizer::create` call and an enabler of it's own.

### The tests

The `UTEST_Microphone` and the `UTEST_UtteranceDetector` tests check the microphone over the demand only audio drivers of the SDL2 and the utterances of the generated tones, the `UTEST_SpeechListener` one checks the listener over the mocked microphone and recognizer, while the `UTEST_SherpaONNXController` one checks the controller over the mocked C++ API of the sherpa-onnx, so it covers every failure of the engine. The `CTEST_SherpaONNXController` test recognizes the English speech sample the downloaded model comes with and the [Ukrainian one](https://github.com/k2-fsa/sherpa-onnx/releases/tag/asr-models) the test configure downloads, and plays the English sample into the microphone of a real `SpeechListener` through the `disk` audio driver of the SDL2, so no sound card takes part. The test cases needing a file the configure has not downloaded skip themselves.

### Packaging

The DEB package ships the shared sherpa-onnx libraries in it's private library directory and depends on the SDL2 and the onnxruntime packages the libraries link against through the `dpkg-shlibdeps` tool, or ships the downloaded onnxruntime where the distribution packages none. The flatpak and the snap fetch the sherpa-onnx and the prebuilt onnxruntime while building (the flatpak module shares the network for it), and so does the Docker image. None of them carries a model, unlike the DEB and the other packages of a build with the downloaded one (see the installing of the model above): the flatpak reads the models of the home directory, so pass the `--model` parameter to them. The flatpak records the microphone through the PulseAudio socket, while the snap needs it's `audio-record` interface connected by hand:

```
sudo snap connect cppapptemplate:audio-record
```
