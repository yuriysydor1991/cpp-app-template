### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appPiperTTS` branch executable speaks the `Hello, Piper! Insert your text here!` greeting with the English `en_US-lessac-medium` voice the configure downloads through the default audio device of the system and exits once the speech is played (or the Ctrl+C keys stop it). The `--text` (or `-t`) parameter gives another text, the `--voice` (or `-s`) one another Piper voice model (e.g. the Ukrainian one a `-DTEMPLATE_APP_PIPER_VOICE=uk_UA-ukrainian_tts-medium` configure downloads), while the `--output` (or `-o`) one writes the speech into a 16-bit PCM mono WAV file instead of playing it:

```
# from the build dir
./src/CppAppTemplate -t "Hello, world!" -s voices/en_US-lessac-medium.onnx
./src/CppAppTemplate -t "Привіт, світе!" -s voices/uk_UA-ukrainian_tts-medium.onnx -o hello.wav
```

```
2026-10-18 12:59:11 DBG 140558553168896 PiperController.cpp:80 : The voices/en_US-lessac-medium.onnx Piper voice is loaded
2026-10-18 12:59:12 DBG 140558553168896 PiperController.cpp:120 : Synthesized 22272 samples with the voices/en_US-lessac-medium.onnx Piper voice
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
