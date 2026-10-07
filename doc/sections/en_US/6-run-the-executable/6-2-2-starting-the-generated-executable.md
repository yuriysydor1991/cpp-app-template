### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appDarknetXX` branch executable loads the YOLOv4-tiny network (the weights of which the configure has downloaded), detects the objects in the sample image of the darknetxx and logs every detected one: the class name, the probability and the box of the left, the top, the width and the height in the image pixels. Point it at the network and the image of your own with the parameters:

```
# from the build dir
./src/CppAppTemplate --cfg yolov4-tiny.cfg --dxxwjz1 yolov4-tiny.dxxwjz1 --names coco.names --image /path/to/image.jpg
```

```
2026-10-07 16:03:59.466999 INF 139939117711616 Application.cpp:82 : Detected 4 object(s) in the misc/data/dog.jpg
2026-10-07 16:03:59.467062 INF 139939117711616 Application.cpp:86 : dog: 84% [137, 205, 181 x 332]
2026-10-07 16:03:59.467072 INF 139939117711616 Application.cpp:86 : truck: 79% [463, 79, 242 x 91]
2026-10-07 16:03:59.467079 INF 139939117711616 Application.cpp:86 : car: 45% [473, 81, 224 x 92]
2026-10-07 16:03:59.467086 INF 139939117711616 Application.cpp:86 : bicycle: 60% [70, 100, 507 x 379]
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
