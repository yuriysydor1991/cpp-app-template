### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appMediaPipePose` branch executable loads the MediaPipe `pose_landmarker_full` model the configure has downloaded and captures the body motion of the default camera, logging the keypoints of every pose of every frame till the Ctrl+C keys stop it or the input ends. Give an image, an image sequence, a video file, a stream or another camera with the `--input` (or `-i`) parameter and another model with the `--model` (or `-m`) one:

```
# from the build dir
./src/CppAppTemplate --input pose.jpg
```

```
2026-11-22 15:16:04.305628 INF 127003183254592 Application.cpp:55 : Capturing the body motion of the pose.jpg input, press Ctrl+C to stop
2026-11-22 15:16:04.359012 INF 127003183254592 Application.cpp:73 : Frame 0 pose: [463.217, 287.395, -212.563] 0.999988 [468.855, 277.461, -216.479] 0.999929 [471.715, 276.78, -216.469] 0.999921 ...
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
