## Enabling the darknetxx object detection

In order to enable the [darknetxx](https://github.com/yuriysydor1991/darknetxx) object detection (the C++ port of the [Darknet](https://github.com/AlexeyAB/darknet) neural network) for the project set an `ON` value to the `ENABLE_DARKNETXX` CMake variable (it is the default one for the `appDarknetXX` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_DARKNETXX=ON
cmake --build build --target all
```

The darknetxx is an application made of this very template rather than a library, so no system package ships it and it's CMake project builds as the top level one only. The [cmake/enablers/ai/template-project-darknetxx-enabler.cmake](/cmake/enablers/ai/template-project-darknetxx-enabler.cmake) module fetches the sources of the `TEMPLATE_APP_DARKNETXX_GIT_TAG` commit (a tested one by default, the darknetxx has no release tags yet) of the `TEMPLATE_APP_DARKNETXX_GIT` repository through the Internet and builds the network core of them into the `darknetxx` static library: the original Darknet C code computing with the C++ network infrastructure of the darknetxx (the layers and the networks memory, the network cfg files loader, the readers, the writers and the validators of the network weights files). The core needs the [OpenCV](https://opencv.org/), the [zlib](https://zlib.net/) and the [nlohmann JSON](https://github.com/nlohmann/json) libraries, the last one gets fetched while not installed, and runs the Darknet kernels on all of the CPU cores with the OpenMP of the compiler:

```
sudo apt install -y libopencv-dev zlib1g-dev nlohmann-json3-dev
```

The standard FetchContent variable builds a local darknetxx checkout instead, the one of your own changes for example:

```
cmake -S . -B build -DFETCHCONTENT_SOURCE_DIR_DARKNETXX=/path/to/darknetxx
```

The `ENABLE_DARKNETXX_AVX` variable (`ON` by default for the x86_64 GCC and Clang builds) compiles the AVX/FMA kernels of the Darknet C core into the non Debug builds, which run several times faster, while the binary needs the AVX2 capable CPU then. So pass the `-DENABLE_DARKNETXX_AVX=OFF` option to the build meant to run on any machine (the flatpak and the snap packagers of the branch do it).

### The darknetxx headers

The darknetxx is made of this very template, so it's headers take the paths of the project ones (the `src/log/log.h`, the `src/app/ApplicationContext.h` and the like) and declare the classes of the same names (the `app::ApplicationContext`, the `default_logger::DefaultLogger`). Both of them live in the very same executable, since:

- the sources including the darknetxx headers compile with the `DARKNETXX_INCLUDE_DIRS` include directories before the project ones (the `SYSTEM` ones, so the 3rd-party headers stay out of the project warnings) and with the `DARKNETXX_COMPILE_DEFINITIONS`, which rename the `app` and the `default_logger` namespaces of the darknetxx into the `darknetxx_app` and the `darknetxx_default_logger` ones;
- the project sources never include the darknetxx headers: the headers of the [src/DarknetXX](/src/DarknetXX) directory keep them out, so the project includes them the usual way.

So compile the sources of your own, which include the darknetxx headers, the way the [src/DarknetXX/CMakeLists.txt](/src/DarknetXX/CMakeLists.txt) file compiles the adaptor:

```
target_include_directories(<target> SYSTEM PRIVATE ${DARKNETXX_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_compile_definitions(<target> PRIVATE ${DARKNETXX_COMPILE_DEFINITIONS})
target_link_libraries(<target> PUBLIC darknetxx)
```

The `darknetxx` library leaves the darknetxx logger out: the [src/DarknetXX/log](/src/DarknetXX/log) directory implements it, forwarding the darknetxx messages into the project log. The errors and the warnings keep their levels, while the info and the debug ones go a level down (a network load alone writes the dozens of the info ones, the table of the layers and the like), so raise the `MAX_LOG_LEVEL` CMake variable to see them. The very variable compiles the debug and the trace messages of the darknetxx core in.

### The network

By default the application detects the objects with the [YOLOv4-tiny](https://github.com/AlexeyAB/darknet#pre-trained-models) network of the 80 classes of the [COCO](https://cocodataset.org/) data set: the network cfg file, the class names and the sample image come with the darknetxx sources, while the configure downloads the weights file of 23 MiB into the `models` directory of the build tree. Every build tree downloads the weights once, while a failed download only warns, leaving the `--weights` (or the `--dxxwjz1`) parameter the way to give them.

| Variable | What it holds |
| --- | --- |
| `TEMPLATE_APP_DARKNETXX_WEIGHTS_URL` | the weights file to download, the YOLOv4-tiny one by default |
| `TEMPLATE_APP_DARKNETXX_WEIGHTS_SHA256` | the SHA256 hash of the downloaded file, empty to skip the check |
| `ENABLE_DARKNETXX_WEIGHTS_DOWNLOAD` | downloads the weights file while configuring, `ON` by default |
| `PROJECT_DARKNETXX_CFG_PATH` | the network cfg file the application loads while the `--cfg` (or `-c`) parameter gives none, the darknetxx `yolov4-tiny.cfg` one if empty |
| `PROJECT_DARKNETXX_WEIGHTS_PATH` | the original weights file the application loads while neither the `--weights` (or `-w`) nor the `--dxxwjz1` parameter gives one, the downloaded one if empty, so nothing gets downloaded once it is given |
| `PROJECT_DARKNETXX_NAMES_PATH` | the class names file the application labels the objects with while the `--names` (or `-n`) parameter gives none, the darknetxx `coco.names` one if empty |
| `PROJECT_DARKNETXX_IMAGE_PATH` | the image the application detects the objects in while the `--image` (or `-i`) parameter gives none, the darknetxx `dog.jpg` one if empty |

Any network of the Darknet does, the ones trained by the darknetxx included, so point at it's files with the command line parameters:

```
./src/CppAppTemplate --cfg yolov4.cfg --weights yolov4.weights --names coco.names --image /path/to/image.jpg
```

### The network weights files

The application reads the weights files of the two formats the darknetxx reads (see the [Network weights files](https://github.com/yuriysydor1991/darknetxx/blob/master/doc/sections/en_US/4-7-4-network-weights-files.md) section of the darknetxx):

| Format | Command line parameter | Class |
| --- | --- | --- |
| the original Darknet weights file (`*.weights`), the binary arrays of the layers, which only the network cfg file gives the structure | `--weights` (or `-w`) | `darknetxxi::OrigWeights` |
| the darknetxx dxxwjz1 file (`*.dxxwjz1`), the gzip compressed JSON document of the very arrays found by their layers and names | `--dxxwjz1` | `darknetxxi::Dxxwjz1Weights` |

The two formats convert into each other with no loss by the `darknetxxConverter` binary of the darknetxx:

```
darknetxxConverter --convert-from weights --convert-src yolov4-tiny.weights \
  --convert-to dxxwjz1 --convert-dst yolov4-tiny.dxxwjz1 --convert-cfg yolov4-tiny.cfg
```

The darknetxx validators check either file against the network before the load, so a file of another network or of the other format (the dxxwjz1 one given to the `--weights` parameter, for example) gets refused with the error, while a truncated file loads with the warning. The plain (not gzip compressed) JSON text of the dxxwjz1 file loads with the warning as well.

Every format is a class derived from the `darknetxxi::NetworkWeights` one, which calls the method of it's own format of the `darknetxxi::WeightsLoader` interface the controller implements, so no value tells the formats apart. A format of the future darknetxx (the dxxwjz2 one, for example) adds it's class and the method of the interface.

### The components

The [src/DarknetXX](/src/DarknetXX) directory holds the classes of the `darknetxxi` namespace:

| Class | What it does |
| --- | --- |
| `DarknetXXController` | loads the network of the cfg file with the weights of any format and detects the objects in the images with it |
| `NetworkWeights`, `OrigWeights`, `Dxxwjz1Weights` | the network weights files of the formats |
| `WeightsLoader` | the interface of the loaders of the weights files formats |
| `DarknetImage` | the owner of the Darknet image (the planar RGB floats) made of the OpenCV one |
| `Detection` | the detected object: the class name, the probability and the box in the image pixels |
| `DarknetXXLog` | the sink of the darknetxx log messages, which forwards them into the project log |

The `init` call of the `darknetxxi::DarknetXXController` class of the [src/DarknetXX/DarknetXXController.h](/src/DarknetXX/DarknetXXController.h) file loads the single image batch network of the cfg file with the given weights and the class names file (the empty path numbers the classes instead). Every `detect` call reads the image of any format the OpenCV reads, resizes it to the network input (letterboxes it for the `letter_box=1` networks), predicts and returns the objects of the probability above the `THRESHOLD` (0.25) after the non maximum suppression, or the `std::nullopt` on a failure:

```
auto darknetxx = darknetxxi::DarknetXXController::create();

if (darknetxx->init("yolov4-tiny.cfg", darknetxxi::Dxxwjz1Weights{"yolov4-tiny.dxxwjz1"},
                    "coco.names")) {
  if (const auto objects = darknetxx->detect("dog.jpg")) {
    for (const auto& object : *objects) {
      LOGI(object);  // dog: 84% [137, 205, 181 x 332]
    }
  }
}
```

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file loads the network of the command line parameters (or of the defaults above), detects the objects in the image and logs every detected one through the `LOGI` macro, so replace the logging with your own handling of the objects.

### The tests

The `UTEST_DarknetXXController` test loads the tiny network of it's own into the darknetxx core: the maxpool of the whole image, the 1x1 convolution of no weights but the biases and the YOLO layer of the single cell, the weights files of both formats written by the test itself. The biases alone tell the YOLO outputs, so the test knows the very box the network detects in whatever image, and the dxxwjz1 weights detect the very objects the original ones do. The `UTEST_DarknetImage`, the `UTEST_Detection` and the `UTEST_NetworkWeights` tests check the rest of the classes, while the `CTEST_DarknetXXController` one detects the objects of the darknetxx sample image with the downloaded YOLOv4-tiny network (the test cases needing it skip themselves without the downloaded weights) and checks the darknetxx messages in the project log.

### Packaging

The darknetxx core is linked into the executable statically, so no package carries a darknetxx library, while the DEB package depends on the OpenCV and the other ones the executable links against through the `dpkg-shlibdeps` tool. The flatpak builds the OpenCV modules the core needs from their sources first and takes the darknetxx sources as an archive of the very commit, while the snap stages the OpenCV libraries of the Ubuntu.

The network files stay in the build tree, so no package carries them and the flatpak and the snap builds download none: give them with the `--cfg`, the `--weights` (or the `--dxxwjz1`), the `--names` and the `--image` parameters. The flatpak reads them from the home directory.
