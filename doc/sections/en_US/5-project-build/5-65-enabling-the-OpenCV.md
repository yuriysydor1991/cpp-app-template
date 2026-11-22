## Enabling the OpenCV

The `appRTMW` template branch integrates the [OpenCV](https://opencv.org/) computer vision library through the dedicated CMake enabler module [cmake/enablers/template-project-OpenCV-enabler.cmake](/cmake/enablers/template-project-OpenCV-enabler.cmake).

The integration is enabled by default with the `ENABLE_OPENCV` CMake variable:

```
# inside the project root directory

cmake -B build -S . -DENABLE_OPENCV=ON
cmake --build build --target all
```

The [src/MoCap/CMakeLists.txt](/src/MoCap/CMakeLists.txt) file probes the system installation of the OpenCV with `find_package(OpenCV REQUIRED COMPONENTS core videoio)`, since it's tests link the library too, while the [src/RTMPose/CMakeLists.txt](/src/RTMPose/CMakeLists.txt) file of the engine probes the `core imgproc` components it uses the same way.

Since the body motion capture requires the library, turning the `ENABLE_OPENCV` option `OFF` stops the configuration with an explanation, until the `add_subdirectory(MoCap)` call of the `src/CMakeLists.txt` file is dropped together with the `src/MoCap` subdirectory, the engine sources and their usage of the `src/app/applications/Application.cpp` file.

The `mocap::FrameSource` class of the [src/MoCap/FrameSource.h](/src/MoCap/FrameSource.h) file reads the frames through the OpenCV videoio module: the camera of the given index through the camera backend of the platform (the V4L2 one of the GNU/Linux), the images and the image sequences through it's built in images backend, and the video files and the streams through the FFmpeg or the GStreamer backends of the OpenCV build. The flatpak manifest builds an OpenCV of no FFmpeg, GStreamer or V4L2, so the flatpak package reads the images and the image sequences alone.
