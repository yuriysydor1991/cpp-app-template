## Enabling the OpenCV

The `appOpenCV` template branch integrates the [OpenCV](https://opencv.org/) computer vision library through the dedicated CMake enabler module [cmake/enablers/template-project-OpenCV-enabler.cmake](/cmake/enablers/template-project-OpenCV-enabler.cmake).

The integration is enabled by default with the `ENABLE_OPENCV` CMake variable:

```
# inside the project root directory

cmake -B build -S . -DENABLE_OPENCV=ON
cmake --build build --target all
```

The `src/opencv/CMakeLists.txt` file probes the system installation of OpenCV with `find_package(OpenCV REQUIRED COMPONENTS core objdetect imgcodecs imgproc)`, since its tests link the library too. The probed components may be tuned through the `TEMPLATE_APP_OPENCV_COMPONENTS` cache variable (semicolon-separated list).

Since the `src/opencv` example requires the library, turning the `ENABLE_OPENCV` option `OFF` stops the configuration with an explanation, until the `add_subdirectory(opencv)` call of the `src/CMakeLists.txt` file is dropped together with the `src/opencv` subdirectory and the OpenCV example of the `src/app/applications/Application.cpp` file.

Once built the application accepts two new command line flags:

- `--image <path>` / `-i <path>` - run the OpenCV face detection on the given image file.
- `--face-cascade <path>` - override the default Haar cascade XML used by the detector.

When neither of the flags is provided the application only verifies that the preinstalled cascade can be loaded and exits cleanly. A cascade that can't be loaded (a missing file or one that is no cascade XML at all) and an `--image` that is missing or that the OpenCV can't decode make the application exit with a failure status.

The Haar cascade XML that ships with the OpenCV installation - `haarcascade_frontalface_default.xml` - is auto-discovered in the `share/opencv4/haarcascades` (or the older `share/opencv/haarcascades`) directory of the next prefixes, in this order:

- `$SNAP/usr` - the snap package (the staged `opencv-data` package)
- `/app` - the flatpak package (the OpenCV the manifest builds)
- `/usr` - the system installation (the Debian/Ubuntu `opencv-data` package)
- `/usr/local` - the locally built OpenCV, the FreeBSD `opencv` package and the Intel macOS Homebrew one
- `/opt/homebrew` - the Apple Silicon macOS Homebrew one

The `app::Application::run` method only delegates to `opencvi::OpenCVController::run` so that the available OpenCV examples can be swapped without touching the `app` component. The current dispatcher invokes `opencvi::OpenCVController::face_recognition_example` which holds the Haar cascade loading and image scanning logic. Add a new example method to `opencvi::OpenCVController` and route `opencvi::OpenCVController::run` to it to quickly switch between examples.

Refer to the implementation of `opencvi::OpenCVController` at [src/opencv/OpenCVController.h](/src/opencv/OpenCVController.h) for the public surface of the integration.
