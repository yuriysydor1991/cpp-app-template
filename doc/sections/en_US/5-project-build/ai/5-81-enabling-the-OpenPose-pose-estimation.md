## Enabling the OpenPose pose estimation

In order to enable the [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose) COCO pose estimation model (the 18 COCO keypoints of a body) for the project set an `ON` value to the `ENABLE_OPENPOSE` CMake variable (it is the default one for the `appOpenPose` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_OPENPOSE=ON
cmake --build build --target all
```

The application of this branch is built around the OpenPose, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

The OpenPose COCO Caffe model runs on the DNN module of the OpenCV the branch is built on, so no other library is needed, while the [cmake/enablers/ai/template-project-openpose-enabler.cmake](/cmake/enablers/ai/template-project-openpose-enabler.cmake) module downloads the model.

| Variable | What it holds |
| --- | --- |
| `PROJECT_POSE_MODEL` | the directory of the `pose_deploy_linevec.prototxt` network and the `pose_iter_440000.caffemodel` weights the application loads while the `--model` (or `-m`) command line parameter gives none, the downloaded one if empty, so nothing gets downloaded once it is given |
| `TEMPLATE_APP_OPENPOSE_NETWORK_URL`, `TEMPLATE_APP_OPENPOSE_NETWORK_SHA256` | the network file the configure downloads and it's SHA256 checksum, the one of the OpenPose repository pinned to it's commit by default |
| `TEMPLATE_APP_OPENPOSE_WEIGHTS_URL`, `TEMPLATE_APP_OPENPOSE_WEIGHTS_SHA256` | the weights file the configure downloads and it's SHA256 checksum, the one of the OpenCV models mirror by default |
| `ENABLE_OPENPOSE_MODEL_DOWNLOAD` | downloads the model into the `TEMPLATE_APP_POSE_MODELS_DIR` directory while configuring, `ON` by default |
| `TEMPLATE_APP_POSE_MODELS_DIR` | the directory the models are downloaded into, the `misc/models` one of the source tree by default |

### The model

The `--model` (or `-m`) parameter takes the directory of the OpenPose COCO body model: the `pose_deploy_linevec.prototxt` Caffe network and the `pose_iter_440000.caffemodel` weights. The model takes the BGR frame scaled to the 368 pixels height, the width keeping the aspect ratio in the multiples of 16, of the (pixel - 128) / 256 values, the way the OpenPose does, and gives the 57 maps of the eighth of the input size: the 18 keypoint heatmaps (the nose, the neck, the right shoulder, elbow and wrist, the left ones, the right hip, knee and ankle, the left ones, the right eye, the left one, the right ear and the left one), the background one and the 38 part affinity fields. The highest response of every keypoint heatmap gives the keypoint of a single body, the way the OpenCV openpose sample does, while no keypoint scored 0.1 at least means no body. The part affinity fields, which group the keypoints of several bodies, stay for a multi-person grouping of your own.

The CMU server of the OpenPose models is gone, so the network comes from the OpenPose repository and the weights from the mirror of the models the OpenCV tests use.

The configure downloads the 46 KB network of the OpenPose repository, pinned to it's commit, and the 209 MB weights of the `dl.opencv.org` mirror into the `misc/models/openpose-coco` directory, into the `misc/models` directory of the source tree, out of the build directories, which the `scripts/build` scripts erase on every configure, so all the build directories of the source tree, whatever their names are, share a single download, while the `.gitignore` and the `.dockerignore` files keep it out of the commits and the docker builds. Every file is checked against it's SHA256 checksum (and taken out of it's archive) in a `.part` directory beside the models first, so an interrupted or a damaged download is never taken for the model, while a failed one only warns, leaving the `--model` parameter the way to give one. Turn the download off with the `-DENABLE_OPENPOSE_MODEL_DOWNLOAD=OFF` parameter or point at a model of your own with the `PROJECT_POSE_MODEL` variable.

### Installing the model

The OpenPose license forbids the redistribution of the model, so neither the install step nor any package carries it: the `app::DataLocator` class of the [src/app/DataLocator.h](/src/app/DataLocator.h) file finds no installed copy and the installed binary loads the downloaded model of the source tree, while a binary of another machine needs the `--model` parameter pointing at a model it's user has downloaded.

### Licenses

The OpenPose and it's models are distributed under the [OpenPose academic license](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/LICENSE), which grants the noncommercial research use alone, forbids the redistribution and sends the commercial users to a paid license of the Carnegie Mellon University, so check whether your use of the model is covered before building anything on it. The OpenCV is distributed under the [Apache-2.0](https://github.com/opencv/opencv/blob/4.x/LICENSE) license.

### The components

The [src/MoCap](/src/MoCap) directory holds the engine neutral body motion capture sources of the `mocap` namespace, which the [src/OpenPose](/src/OpenPose) engine of the branch implements the estimator interface of:

| Class | What it does |
| --- | --- |
| `mocap::FrameSource` | reads the frames of a camera, an image, an image sequence, a video file or a stream through the OpenCV videoio module, see the [Enabling the OpenCV](/doc/sections/en_US/5-project-build/5-65-enabling-the-OpenCV.md) section |
| `mocap::IPoseEstimator` | the interface of the pose estimation engines: loads a model and estimates the poses of a BGR frame, while the `create` call gives the engine the build links in |
| `mocap::MotionCapture` | estimates the poses of every frame the `FrameSource` reads with the `IPoseEstimator` |
| `openpose::OpenPoseController` | estimates the pose with the OpenPose COCO Caffe model through the OpenCV DNN module |
| `openpose::HeatmapDecoder` | decodes the keypoints of a single body out of the highest responses of the keypoint heatmaps |

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

The `estimate` call of the `mocap::IPoseEstimator` interface estimates the poses of a frame of your own, while the `mocap::IPoseEstimator::create` definition of the engine sources picks the engine, so another engine takes the place of the OpenPose by a single class.
