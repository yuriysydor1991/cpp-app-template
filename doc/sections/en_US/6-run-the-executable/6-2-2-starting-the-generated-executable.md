### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appSherpaONNX` branch executable speaks the `Hello, sherpa-onnx! Insert your text here!` greeting with the first speaker of the Kokoro model the configure downloads into the `models` directory of the build tree through the default audio device of the system and exits once the speech is played (or the Ctrl+C keys stop it). The `--text` (or `-t`) parameter gives another text, the `--voice` (or `-s`) one another model directory of the sherpa-onnx, optionally followed by the `:<id>` speaker id, while the `--output` (or `-o`) one writes the speech into a 16-bit PCM mono WAV file instead of playing it:

```
# from the build dir
./src/CppAppTemplate --text "Hello, world!" --voice models/kokoro-int8-multi-lang-v1_0:3 --output hello.wav
./src/CppAppTemplate -t "它也支持英文, and English too." -s ~/models/vits-melo-tts-zh_en
```

```
2026-10-18 13:19:51.055968 DBG 140640821018752 SherpaONNXController.cpp:99 : The sherpa-onnx model of the models/kokoro-int8-multi-lang-v1_0 directory is loaded
2026-10-18 13:19:52.096190 DBG 140640821018752 SherpaONNXController.cpp:121 : Synthesized 25128 samples with the models/kokoro-int8-multi-lang-v1_0:3 sherpa-onnx voice
2026-10-18 13:19:52.097106 DBG 140640821018752 WavWriter.cpp:87 : The 1047 ms speech is written into hello.wav
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
