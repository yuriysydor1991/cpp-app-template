### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appRHVoice` branch executable speaks the `Hello, RHVoice! Insert your text here!` greeting with the English `Alan` voice through the default audio device of the system and exits once the speech is played (or the Ctrl+C keys stop it). The `--text` (or `-t`) parameter gives another text, the `--voice` (or `-s`) one another RHVoice voice (the `Anatol` or the `Natalia` one for the Ukrainian text), while the `--output` (or `-o`) one writes the speech into a 16-bit PCM mono WAV file instead of playing it:

```
# from the build dir
./src/CppAppTemplate --text "Привіт, світе!" --voice Anatol
./src/CppAppTemplate -t "Hello, world!" -s Slt -o hello.wav
```

```
2026-10-18 13:00:51 DBG 140354055991680 RHVoiceController.cpp:118 : Synthesized 36360 samples with the Anatol RHVoice voice
2026-10-18 13:00:51 DBG 140354055991680 AudioPlayer.cpp:48 : Playing the 1515 ms speech through the pulseaudio audio driver
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
