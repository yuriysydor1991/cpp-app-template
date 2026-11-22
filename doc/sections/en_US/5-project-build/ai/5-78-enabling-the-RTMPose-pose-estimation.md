## Enabling the RTMPose pose estimation

In order to enable the [RTMPose](https://github.com/open-mmlab/mmpose/tree/main/projects/rtmpose) pose estimation of the OpenMMLab (the 17 COCO keypoints of every person the YOLOX detector finds) for the project set an `ON` value to the `ENABLE_RTMPOSE` CMake variable (it is the default one for the `appRTMPose` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_RTMPOSE=ON
cmake --build build --target all
```

The application of this branch is built around the RTMPose, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

The RTMPose and the YOLOX models run on the [ONNX Runtime](https://onnxruntime.ai/) the system has installed, see the [Enabling the ONNX Runtime](/doc/sections/en_US/5-project-build/ai/5-83-enabling-the-ONNX-Runtime.md) section, while the [cmake/enablers/ai/template-project-rtmpose-enabler.cmake](/cmake/enablers/ai/template-project-rtmpose-enabler.cmake) module downloads them.

| Variable | What it holds |
| --- | --- |
| `PROJECT_POSE_MODEL` | the directory of the `detector.onnx` and the `pose.onnx` models the application loads while the `--model` (or `-m`) command line parameter gives none, the downloaded one if empty, so nothing gets downloaded once it is given |
| `TEMPLATE_APP_RTMPOSE_MODEL_URL`, `TEMPLATE_APP_RTMPOSE_MODEL_SHA256` | the pose model the configure downloads and it's SHA256 checksum, the RTMPose-m archive by default |
| `TEMPLATE_APP_RTMPOSE_DETECTOR_URL`, `TEMPLATE_APP_RTMPOSE_DETECTOR_SHA256` | the person detector archive the configure downloads and it's SHA256 checksum, the YOLOX-tiny one by default |
| `ENABLE_RTMPOSE_MODEL_DOWNLOAD` | downloads the models into the `TEMPLATE_APP_POSE_MODELS_DIR` directory while configuring and installs them with the binary, `ON` by default |
| `TEMPLATE_APP_POSE_MODELS_DIR` | the directory the models are downloaded into, the `misc/models` one of the source tree by default |

### The model

The `--model` (or `-m`) parameter takes the directory of the two ONNX models of the MMDeploy export: the `detector.onnx` YOLOX person detector, it's non-maximum suppression included, and the `pose.onnx` top-down RTMPose family model of the SimCC (the coordinate classification) outputs. The detector takes the frame scaled into the top left corner of it's input, the gray padding filling the rest, and keeps the persons of the score above 0.3. The pose model takes every person box padded by a quarter and widened to the aspect ratio of it's input, the RGB channels normalized by the ImageNet means and deviations, while the bin of the highest response of every SimCC axis gives the keypoint coordinate and the lower of the x and the y responses gives it's score, the way the MMPose does.

The configure downloads the official ONNX exports of the OpenMMLab the [rtmlib](https://github.com/Tau-J/rtmlib) pairs: the 51 MB archive of the RTMPose-m model of the 17 COCO keypoints and the 19 MB one of the YOLOX-tiny person detector, their `end2end.onnx` models taken out as the `pose.onnx` and the `detector.onnx` ones of the `misc/models/rtmpose-m` directory, into the `misc/models` directory of the source tree, out of the build directories, which the `scripts/build` scripts erase on every configure, so all the build directories of the source tree, whatever their names are, share a single download, while the `.gitignore` and the `.dockerignore` files keep it out of the commits and the docker builds. Every file is checked against it's SHA256 checksum (and taken out of it's archive) in a `.part` directory beside the models first, so an interrupted or a damaged download is never taken for the model, while a failed one only warns, leaving the `--model` parameter the way to give one. Turn the download off with the `-DENABLE_RTMPOSE_MODEL_DOWNLOAD=OFF` parameter or point at a model of your own with the `PROJECT_POSE_MODEL` variable.

The other RTMPose family exports of the OpenMMLab (the RTMPose-l one, the Halpe26 ones of the 26 keypoints with the feet, the RTMW whole body ones) run the same way, so point the `TEMPLATE_APP_RTMPOSE_MODEL_URL` and the `TEMPLATE_APP_RTMPOSE_MODEL_SHA256` variables at one of them or put it's `end2end.onnx` model as the `pose.onnx` one beside the `detector.onnx` one of a directory of your own and give that directory with the `--model` parameter.

### Installing the model

The install step (and every package built out of it: deb, rpm, AppImage, FreeBSD pkg, the MS Windows installer) copies the downloaded model into the `share/CppAppTemplate` directory of the installation prefix, the `/usr/share/CppAppTemplate/rtmpose-m` one for example, and the installed binary runs with no source tree around. The `app::DataLocator` class of the [src/app/DataLocator.h](/src/app/DataLocator.h) file picks the model the running binary loads while no `--model` parameter is given: the installed one relative to the binary location first (so a relocated package, an AppImage for example, keeps working), then the downloaded one of the models directory (a binary run out of the build tree), then the installed one under the configured prefix. The download turned off or failed installs no model, and the model of the `PROJECT_POSE_MODEL` variable gets loaded from where it is.

### Licenses

The MMPose, the RTMPose and the YOLOX models of the OpenMMLab are distributed under the [Apache-2.0](https://github.com/open-mmlab/mmpose/blob/main/LICENSE) license, the ONNX Runtime under the MIT one and the OpenCV under the [Apache-2.0](https://github.com/opencv/opencv/blob/4.x/LICENSE) one, so their copyright notices and license texts accompany a distributed executable. The data sets the models are trained on keep the terms of their own.

### The components

The [src/MoCap](/src/MoCap) directory holds the engine neutral body motion capture sources of the `mocap` namespace, which the [src/RTMPose](/src/RTMPose) engine of the branch implements the estimator interface of:

| Class | What it does |
| --- | --- |
| `mocap::FrameSource` | reads the frames of a camera, an image, an image sequence, a video file or a stream through the OpenCV videoio module, see the [Enabling the OpenCV](/doc/sections/en_US/5-project-build/5-65-enabling-the-OpenCV.md) section |
| `mocap::IPoseEstimator` | the interface of the pose estimation engines: loads a model and estimates the poses of a BGR frame, while the `create` call gives the engine the build links in |
| `mocap::MotionCapture` | estimates the poses of every frame the `FrameSource` reads with the `IPoseEstimator` |
| `rtmpose::RTMPoseController` | finds the persons of the frame with the `PersonDetector` and estimates their keypoints with the `PoseModel` |
| `rtmpose::PersonDetector` | detects the persons of a frame with the YOLOX ONNX model |
| `rtmpose::PoseModel` | estimates the keypoints of a person box with the top-down RTMPose family ONNX model |
| `rtmpose::PoseCrop` | scales the padded person box into the model input and maps the points of the model input back to the frame |
| `rtmpose::SimCCDecoder` | decodes the keypoints out of the SimCC outputs of the model the MMPose way |
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

The `estimate` call of the `mocap::IPoseEstimator` interface estimates the poses of a frame of your own, while the `mocap::IPoseEstimator::create` definition of the engine sources picks the engine, so another engine takes the place of the RTMPose by a single class.
