## Enabling the MediaPipe Pose landmarker

In order to enable the [MediaPipe Pose](https://ai.google.dev/edge/mediapipe/solutions/vision/pose_landmarker) landmarker of the Google (the 33 BlazePose landmarks of up to four bodies in 3D) for the project set an `ON` value to the `ENABLE_MEDIAPIPE` CMake variable (it is the default one for the `appMediaPipePose` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_MEDIAPIPE=ON
cmake --build build --target all
```

The application of this branch is built around the MediaPipe, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

The MediaPipe builds with the Bazel alone, while it's official PyPI wheel ships the prebuilt MediaPipe Tasks C API library the Python Tasks API loads, so the [cmake/enablers/ai/template-project-mediapipe-enabler.cmake](/cmake/enablers/ai/template-project-mediapipe-enabler.cmake) module fetches the `mediapipe-1.2.3` wheel of the GNU/Linux x86-64 through the `FetchContent` (checked against it's SHA256 checksum), takes the `libmediapipe.so` library out of it and downloads the C API headers out of the sources of the very same release, pinned to it's commit. The library runs on the GNU/Linux x86-64 alone (the configure fails with an explanatory message elsewhere), needs the `libEGL.so.1` and the `libGLESv2.so.2` libraries (the `libegl1` and the `libgles2` packages of the Debian and the Ubuntu) and carries the C++ runtime of it's own, so it shares no C++ objects with the executable.

The module provides the `MediaPipe::mediapipe` imported target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} MediaPipe::mediapipe)
```

The installation puts the library and it's license files into the private `lib/CppAppTemplate` directory of the installation prefix (the `lib/<multiarch>/CppAppTemplate` one with the `/usr` prefix), which the installed executable finds the library in by it's `$ORIGIN` relative RPATH, so the installed, the packaged and the build tree executables run with no `LD_LIBRARY_PATH` variable.

| Variable | What it holds |
| --- | --- |
| `TEMPLATE_APP_MEDIAPIPE_WHEEL_URL`, `TEMPLATE_APP_MEDIAPIPE_WHEEL_SHA256` | the MediaPipe PyPI wheel the C API library is taken out of and it's SHA256 checksum, the `mediapipe-1.2.3` GNU/Linux x86-64 one by default |
| `TEMPLATE_APP_MEDIAPIPE_SOURCES_URL` | the MediaPipe sources the C API headers are downloaded from, the ones of the v1.2.3 release commit by default |
| `PROJECT_POSE_MODEL` | the pose landmarker `.task` model the application loads while the `--model` (or `-m`) command line parameter gives none, the downloaded one if empty, so nothing gets downloaded once it is given |
| `TEMPLATE_APP_MEDIAPIPE_MODEL_URL`, `TEMPLATE_APP_MEDIAPIPE_MODEL_SHA256` | the model the configure downloads and it's SHA256 checksum, the `pose_landmarker_full` one by default |
| `ENABLE_MEDIAPIPE_MODEL_DOWNLOAD` | downloads the model into the `TEMPLATE_APP_POSE_MODELS_DIR` directory while configuring and installs it with the binary, `ON` by default |
| `TEMPLATE_APP_POSE_MODELS_DIR` | the directory the models are downloaded into, the `misc/models` one of the source tree by default |

### The model

The `--model` (or `-m`) parameter takes the `.task` model of the MediaPipe pose landmarker: the bundle of the pose detector and the pose landmarks detector of the BlazePose GHUM 3D topology of 33 landmarks. The controller runs the landmarker in the video mode of the strictly increasing timestamps, so it tracks the bodies across the frames instead of detecting them anew on every one, finds up to four bodies and converts the normalized landmarks into the frame pixels, the visibility being the keypoint score.

The configure downloads the 9 MB `pose_landmarker_full` model of the Google into the `misc/models` directory of the source tree, out of the build directories, which the `scripts/build` scripts erase on every configure, so all the build directories of the source tree, whatever their names are, share a single download, while the `.gitignore` and the `.dockerignore` files keep it out of the commits and the docker builds. Every file is checked against it's SHA256 checksum (and taken out of it's archive) in a `.part` directory beside the models first, so an interrupted or a damaged download is never taken for the model, while a failed one only warns, leaving the `--model` parameter the way to give one. Turn the download off with the `-DENABLE_MEDIAPIPE_MODEL_DOWNLOAD=OFF` parameter or point at a model of your own with the `PROJECT_POSE_MODEL` variable.

The `pose_landmarker_lite` and the `pose_landmarker_heavy` models of the [MediaPipe pose landmarker](https://ai.google.dev/edge/mediapipe/solutions/vision/pose_landmarker) page trade the accuracy for the speed and back, so point the `TEMPLATE_APP_MEDIAPIPE_MODEL_URL` and the `TEMPLATE_APP_MEDIAPIPE_MODEL_SHA256` variables at one of them or download it by hand:

```
mkdir -p ~/models && cd ~/models
curl -SL -O https://storage.googleapis.com/mediapipe-models/pose_landmarker/pose_landmarker_heavy/float16/1/pose_landmarker_heavy.task

# from the build dir
./src/CppAppTemplate --model ~/models/pose_landmarker_heavy.task
```

### Installing the model

The install step (and every package built out of it: deb, rpm, AppImage, FreeBSD pkg, the MS Windows installer) copies the downloaded model into the `share/CppAppTemplate` directory of the installation prefix, the `/usr/share/CppAppTemplate/pose_landmarker_full.task` one for example, and the installed binary runs with no source tree around. The `app::DataLocator` class of the [src/app/DataLocator.h](/src/app/DataLocator.h) file picks the model the running binary loads while no `--model` parameter is given: the installed one relative to the binary location first (so a relocated package, an AppImage for example, keeps working), then the downloaded one of the models directory (a binary run out of the build tree), then the installed one under the configured prefix. The download turned off or failed installs no model, and the model of the `PROJECT_POSE_MODEL` variable gets loaded from where it is.

### Licenses

The MediaPipe is distributed under the [Apache-2.0](https://github.com/google-ai-edge/mediapipe/blob/master/LICENSE) license, and the license and the NOTICE files of it's wheel go beside the installed library, while the pose landmarker models are distributed under the Apache-2.0 license the [litert-community/MediaPipe-PoseLandmarker-Full](https://huggingface.co/litert-community/MediaPipe-PoseLandmarker-Full) Hugging Face copy of the very same model states. The OpenCV is distributed under the [Apache-2.0](https://github.com/opencv/opencv/blob/4.x/LICENSE) license.

### The components

The [src/MoCap](/src/MoCap) directory holds the engine neutral body motion capture sources of the `mocap` namespace, which the [src/MediaPipe](/src/MediaPipe) engine of the branch implements the estimator interface of:

| Class | What it does |
| --- | --- |
| `mocap::FrameSource` | reads the frames of a camera, an image, an image sequence, a video file or a stream through the OpenCV videoio module, see the [Enabling the OpenCV](/doc/sections/en_US/5-project-build/5-65-enabling-the-OpenCV.md) section |
| `mocap::IPoseEstimator` | the interface of the pose estimation engines: loads a model and estimates the poses of a BGR frame, while the `create` call gives the engine the build links in |
| `mocap::MotionCapture` | estimates the poses of every frame the `FrameSource` reads with the `IPoseEstimator` |
| `mediapipei::MediaPipeController` | tracks the poses of the video frames with the pose landmarker of the MediaPipe Tasks C API |
| `mediapipei::LandmarksDecoder` | decodes the normalized landmarks of the landmarker result into the frame pixels |

Every pose is the keypoints of a body in the keypoint order of the model, each keypoint being the tuple of it's position in the frame pixels (the depth in the scale of the x axis, the smaller the closer to the camera) and it's score. The `init` call of the `mocap::MotionCapture` class of the [src/MoCap/MotionCapture.h](/src/MoCap/MotionCapture.h) file loads the model and the `open` call opens the input: the camera of the given index (`0` is the default camera) or the image, the image sequence (`frame_%03d.png`), the video file or the stream URL of the given path. Every `capture` call estimates the poses of the next frame, the empty ones for no body, or gives the `std::nullopt` at the end of the input or on a failure, which the `LOGE` macro logs:

```
#include "src/MoCap/MotionCapture.h"

auto capture = mocap::MotionCapture::create();

if (capture->init(model) && capture->open("dance.mp4")) {
  while (const auto poses = capture->capture()) {
    for (const auto& pose : *poses) {
      const auto& [position, score] = pose.front();
      // the position.x, the position.y and the position.z of the first keypoint
    }
  }
}
```

The `estimate` call of the `mocap::IPoseEstimator` interface estimates the poses of a frame of your own, while the `mocap::IPoseEstimator::create` definition of the engine sources picks the engine, so another engine takes the place of the MediaPipe by a single class.
