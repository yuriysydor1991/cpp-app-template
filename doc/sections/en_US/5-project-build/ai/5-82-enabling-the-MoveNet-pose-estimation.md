## Enabling the MoveNet pose estimation

In order to enable the Google's [MoveNet](https://www.tensorflow.org/hub/tutorials/movenet) MultiPose Lightning pose estimation model (the 17 COCO keypoints of up to six bodies) for the project set an `ON` value to the `ENABLE_MOVENET` CMake variable (it is the default one for the `appMoveNet` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_MOVENET=ON
cmake --build build --target all
```

The application of this branch is built around the MoveNet, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

The MoveNet model run on the [ONNX Runtime](https://onnxruntime.ai/) the system has installed, see the [Enabling the ONNX Runtime](/doc/sections/en_US/5-project-build/ai/5-83-enabling-the-ONNX-Runtime.md) section, while the [cmake/enablers/ai/template-project-movenet-enabler.cmake](/cmake/enablers/ai/template-project-movenet-enabler.cmake) module downloads it.

| Variable | What it holds |
| --- | --- |
| `PROJECT_POSE_MODEL` | the MoveNet MultiPose ONNX model the application loads while the `--model` (or `-m`) command line parameter gives none, the downloaded one if empty, so nothing gets downloaded once it is given |
| `TEMPLATE_APP_MOVENET_MODEL_URL`, `TEMPLATE_APP_MOVENET_MODEL_SHA256` | the model the configure downloads and it's SHA256 checksum, the pinned ONNX conversion of the MultiPose Lightning model by default |
| `ENABLE_MOVENET_MODEL_DOWNLOAD` | downloads the model into the `TEMPLATE_APP_POSE_MODELS_DIR` directory while configuring and installs it with the binary, `ON` by default |
| `TEMPLATE_APP_POSE_MODELS_DIR` | the directory the models are downloaded into, the `misc/models` one of the source tree by default |

### The model

The `--model` (or `-m`) parameter takes the ONNX file of the MoveNet MultiPose model: the `int32` RGB frame of the `[1, height, width, 3]` shape in, the sides being the multiples of 32, and the `[1, 6, 56]` bodies out, every body being the 17 keypoints (the nose, then the eye, the ear, the shoulder, the elbow, the wrist, the hip, the knee and the ankle, each left then right) of the (y, x, score) values normalized to the input, followed by the body box and the body score. The controller scales the frame so it's longer side takes 256 pixels and pads the shorter one up to the multiple of 32, the way the TF.js pose detection does, and keeps the bodies of the 0.25 score at least.

The Google publishes the MoveNet models in the TFLite, the SavedModel and the TF.js formats alone, so the ONNX conversion of the [Xenova/movenet-multipose-lightning](https://huggingface.co/Xenova/movenet-multipose-lightning) Hugging Face repository runs here.

The configure downloads the 19 MB `tf2onnx` conversion of the MultiPose Lightning model of that repository, pinned to it's commit, into the `misc/models` directory of the source tree, out of the build directories, which the `scripts/build` scripts erase on every configure, so all the build directories of the source tree, whatever their names are, share a single download, while the `.gitignore` and the `.dockerignore` files keep it out of the commits and the docker builds. Every file is checked against it's SHA256 checksum (and taken out of it's archive) in a `.part` directory beside the models first, so an interrupted or a damaged download is never taken for the model, while a failed one only warns, leaving the `--model` parameter the way to give one. Turn the download off with the `-DENABLE_MOVENET_MODEL_DOWNLOAD=OFF` parameter or point at a model of your own with the `PROJECT_POSE_MODEL` variable.

### Installing the model

The install step (and every package built out of it: deb, rpm, AppImage, FreeBSD pkg, the MS Windows installer) copies the downloaded model into the `share/CppAppTemplate` directory of the installation prefix, the `/usr/share/CppAppTemplate/movenet-multipose-lightning.onnx` one for example, and the installed binary runs with no source tree around. The `app::DataLocator` class of the [src/app/DataLocator.h](/src/app/DataLocator.h) file picks the model the running binary loads while no `--model` parameter is given: the installed one relative to the binary location first (so a relocated package, an AppImage for example, keeps working), then the downloaded one of the models directory (a binary run out of the build tree), then the installed one under the configured prefix. The download turned off or failed installs no model, and the model of the `PROJECT_POSE_MODEL` variable gets loaded from where it is.

### Licenses

The MoveNet models are distributed under the Apache-2.0 license, which the Google states for all of them and the [Xenova/movenet-multipose-lightning](https://huggingface.co/Xenova/movenet-multipose-lightning) repository states for it's conversion, the ONNX Runtime under the MIT one and the OpenCV under the [Apache-2.0](https://github.com/opencv/opencv/blob/4.x/LICENSE) one, so their copyright notices and license texts accompany a distributed executable.

### The components

The [src/MoCap](/src/MoCap) directory holds the engine neutral body motion capture sources of the `mocap` namespace, which the [src/MoveNet](/src/MoveNet) engine of the branch implements the estimator interface of:

| Class | What it does |
| --- | --- |
| `mocap::FrameSource` | reads the frames of a camera, an image, an image sequence, a video file or a stream through the OpenCV videoio module, see the [Enabling the OpenCV](/doc/sections/en_US/5-project-build/5-65-enabling-the-OpenCV.md) section |
| `mocap::IPoseEstimator` | the interface of the pose estimation engines: loads a model and estimates the poses of a BGR frame, while the `create` call gives the engine the build links in |
| `mocap::MotionCapture` | estimates the poses of every frame the `FrameSource` reads with the `IPoseEstimator` |
| `movenet::MoveNetController` | estimates the poses with the MoveNet MultiPose ONNX model |
| `movenet::MoveNetDecoder` | decodes the bodies scored 0.25 at least out of the model output |
| `onnxi::ONNXModel` | runs an ONNX model with the ONNX Runtime, see the [Enabling the ONNX Runtime](/doc/sections/en_US/5-project-build/ai/5-83-enabling-the-ONNX-Runtime.md) section |

Every pose is the keypoints of a body in the keypoint order of the model, each keypoint being the tuple of it's position in the frame pixels (the depth being zero) and it's score. The `init` call of the `mocap::MotionCapture` class of the [src/MoCap/MotionCapture.h](/src/MoCap/MotionCapture.h) file loads the model and the `open` call opens the input: the camera of the given index (`0` is the default camera) or the image, the image sequence (`frame_%03d.png`), the video file or the stream URL of the given path. Every `capture` call estimates the poses of the next frame, the empty ones for no body, or gives the `std::nullopt` at the end of the input or on a failure, which the `LOGE` macro logs:

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

The `estimate` call of the `mocap::IPoseEstimator` interface estimates the poses of a frame of your own, while the `mocap::IPoseEstimator::create` definition of the engine sources picks the engine, so another engine takes the place of the MoveNet by a single class.
