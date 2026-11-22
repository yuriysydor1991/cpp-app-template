### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appMoveNet` branch executable loads the MoveNet MultiPose model the configure has downloaded and captures the body motion of the default camera, logging the keypoints of every pose of every frame till the Ctrl+C keys stop it or the input ends. Give an image, an image sequence, a video file, a stream or another camera with the `--input` (or `-i`) parameter and another model with the `--model` (or `-m`) one:

```
# from the build dir
./src/CppAppTemplate --input pose.jpg
```

```
2026-11-22 15:14:22.656704 INF 125537364059264 Application.cpp:55 : Capturing the body motion of the pose.jpg input, press Ctrl+C to stop
2026-11-22 15:14:22.676225 INF 125537364059264 Application.cpp:73 : Frame 0 pose: [460.522, 284.08, 0] 0.774824 [470.947, 273.156, 0] 0.595239 [462.7, 275.608, 0] 0.793707 ...
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
