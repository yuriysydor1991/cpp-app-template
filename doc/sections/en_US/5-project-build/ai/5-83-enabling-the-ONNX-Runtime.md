## Enabling the ONNX Runtime

In order to enable the [ONNX Runtime](https://onnxruntime.ai/) (the cross platform inference engine of the ONNX models) for the project set an `ON` value to the `ENABLE_ONNXRUNTIME` CMake variable (it is the default one for the `appRTMPose` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_ONNXRUNTIME=ON
cmake --build build --target all
```

The pose estimation of this branch runs it's models on the ONNX Runtime, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

The [cmake/enablers/ai/template-project-onnxruntime-enabler.cmake](/cmake/enablers/ai/template-project-onnxruntime-enabler.cmake) module finds the ONNX Runtime the system has installed through it's CMake package configuration: the `libonnxruntime-dev` package of the Ubuntu 26.04 and the Debian 13, the `onnxruntime-devel` one of the Fedora, the `misc/onnxruntime` port of the FreeBSD or the `onnxruntime` formula of the Homebrew. The Ubuntu 24.04, the RHEL and the core24 base of the snap package no ONNX Runtime, the freedesktop runtime of the flatpak carries none either, while the prebuilt archives of the ONNX Runtime GitHub releases are unreachable since the microsoft/onnxruntime repository answers 404 (checked on 2026-11-22), so the `onnxruntime_DIR` variable points the configure at an ONNX Runtime of a custom location there:

```
sudo apt install -y libonnxruntime-dev
cmake -S . -B build -Donnxruntime_DIR=/opt/onnxruntime/lib/cmake/onnxruntime
```

The module provides the `onnxruntime::onnxruntime` target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} onnxruntime::onnxruntime)
```

The `onnxi::ONNXModel` class of the [src/ONNX/ONNXModel.h](/src/ONNX/ONNXModel.h) file loads an ONNX model file and runs it on the CPU: the `run` call takes the continuous float (`CV_32F`) or int32 (`CV_32S`) OpenCV matrix of the dimensions of the first model input and gives the model outputs in the model order, none on a failure, which the `LOGE` macro logs, while the `planar` call turns an interleaved float image into the planar (NCHW) tensor most of the vision models take:

```
#include "src/ONNX/ONNXModel.h"

onnxi::ONNXModel model;

if (model.load("model.onnx")) {
  cv::Mat image;

  frame.convertTo(image, CV_32F);

  cv::Mat tensor = onnxi::ONNXModel::planar(image);
  const auto outputs = model.run(tensor);
}
```

The Ubuntu 26.04 build of the ONNX Runtime 1.23.2 prints hundreds of the `Schema error: Trying to register schema ... already registered` lines on the standard error, which change nothing of the inference. The ONNX Runtime is distributed under the MIT license, so it's copyright notice and license text accompany a distributed executable.
