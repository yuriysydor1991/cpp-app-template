## Enabling the OpenCV

The `appOpenCV` template branch integrates the [OpenCV](https://opencv.org/) computer vision library through the dedicated CMake enabler module [cmake/enablers/template-project-OpenCV-enabler.cmake](/cmake/enablers/template-project-OpenCV-enabler.cmake).

The integration is enabled by default with the `ENABLE_OPENCV` CMake variable:

```
# inside the project root directory

cmake -B build -S . -DENABLE_OPENCV=ON
cmake --build build --target all
```

By default the enabler probes the system installation of OpenCV with `find_package(OpenCV REQUIRED COMPONENTS core objdetect imgcodecs imgproc)`. The probed components may be tuned through the `TEMPLATE_APP_OPENCV_COMPONENTS` cache variable (semicolon-separated list).

Once built the application accepts two new command line flags:

- `--image <path>` / `-i <path>` - run the OpenCV face detection on the given image file.
- `--face-cascade <path>` - override the default Haar cascade XML used by the detector.

When neither of the flags is provided the application only verifies that the preinstalled cascade can be loaded and exits cleanly.

The Haar cascade XML that ships with the system OpenCV installation - `haarcascade_frontalface_default.xml` - is auto-discovered out of the following well-known locations:

- `/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml` (Debian/Ubuntu `opencv-data`)
- `/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml`
- `/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml`
- `/usr/local/share/opencv/haarcascades/haarcascade_frontalface_default.xml`
- macOS Homebrew locations under `/usr/local/Cellar` and `/opt/homebrew`

The `app::Application::run` method only delegates to `opencvi::OpenCVController::run` so that the available OpenCV examples can be swapped without touching the `app` component. The current dispatcher invokes `opencvi::OpenCVController::face_recognition_example` which holds the Haar cascade loading and image scanning logic. Add a new example method to `opencvi::OpenCVController` and route `opencvi::OpenCVController::run` to it to quickly switch between examples.

Refer to the implementation of `opencvi::OpenCVController` at [src/opencv/OpenCVController.h](/src/opencv/OpenCVController.h) for the public surface of the integration.
