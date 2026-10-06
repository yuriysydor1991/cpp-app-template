### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appWhisperCPP` branch executable loads the whisper model the configure has downloaded (the multilingual `small` one by default) and listens to the default microphone of the system, logging every recognized utterance till the Ctrl+C keys stop it. Point it at another model with the `--model` (or `-m`) parameter:

```
# from the build dir
./src/CppAppTemplate --model /path/to/ggml-large-v3-turbo.bin
```

```
2026-10-06 16:00:22 INF 139857446091008 Application.cpp:39 : Listening to the default microphone, press Ctrl+C to stop
2026-10-06 16:00:25 INF 139857446091008 Application.cpp:51 : And so, my fellow Americans!
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
