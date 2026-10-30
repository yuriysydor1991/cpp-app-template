### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appSherpaONNXSTT` branch executable loads the sherpa-onnx model the configure has downloaded (the multilingual `sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8` one by default) and listens to the default microphone of the system, logging every recognized utterance till the Ctrl+C keys stop it. Point it at another model directory with the `--model` (or `-m`) parameter:

```
# from the build dir
./src/CppAppTemplate --model ~/models/sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8
```

```
2026-10-30 14:04:55.109735 INF 131019520904448 Application.cpp:41 : Listening to the default microphone, press Ctrl+C to stop
2026-10-30 14:05:01.924416 INF 131019520904448 Application.cpp:53 : Ask what you can do for your country.
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
