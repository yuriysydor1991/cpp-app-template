### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appRTMPose` branch executable loads the RTMPose-m and YOLOX-tiny models the configure has downloaded and captures the body motion of the default camera, logging the keypoints of every pose of every frame till the Ctrl+C keys stop it or the input ends. Give an image, an image sequence, a video file, a stream or another camera with the `--input` (or `-i`) parameter and another model with the `--model` (or `-m`) one:

```
# from the build dir
./src/CppAppTemplate --input pose.jpg
```

```
2026-11-22 15:15:52.627391 INF 133479730037888 Application.cpp:55 : Capturing the body motion of the pose.jpg input, press Ctrl+C to stop
2026-11-22 15:15:53.044474 INF 133479730037888 Application.cpp:73 : Frame 0 pose: [468.19, 269.935, 0] 0.875346 [480.198, 262.729, 0] 0.869675 [468.19, 265.131, 0] 0.926918 ...
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
