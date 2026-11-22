## Вмикання інтеграції OpenCV

Гілка `appRTMW` шаблонного проекту інтегрує бібліотеку компʼютерного зору [OpenCV](https://opencv.org/) через окремий CMake-модуль [cmake/enablers/template-project-OpenCV-enabler.cmake](/cmake/enablers/template-project-OpenCV-enabler.cmake).

Інтеграція увімкнена за замовчуванням через CMake-змінну `ENABLE_OPENCV`:

```
# всередині кореневої директорії проекту

cmake -B build -S . -DENABLE_OPENCV=ON
cmake --build build --target all
```

Файл [src/MoCap/CMakeLists.txt](/src/MoCap/CMakeLists.txt) шукає системну установку OpenCV викликом `find_package(OpenCV REQUIRED COMPONENTS core videoio)`, оскільки його тести також компонуються з бібліотекою, а файл [src/RTMPose/CMakeLists.txt](/src/RTMPose/CMakeLists.txt) рушія так само шукає компоненти `core imgproc`, які він використовує.

Оскільки захоплення рухів тіла потребує бібліотеки, вимкнення опції `ENABLE_OPENCV` значенням `OFF` зупиняє конфігурування з поясненням, доки виклик `add_subdirectory(MoCap)` файлу `src/CMakeLists.txt` не прибрано разом з піддиректорією `src/MoCap`, вихідними кодами рушія та їхнім використанням у файлі `src/app/applications/Application.cpp`.

Клас `mocap::FrameSource` файлу [src/MoCap/FrameSource.h](/src/MoCap/FrameSource.h) читає кадри модулем videoio бібліотеки OpenCV: камеру заданого індексу — бекендом камер платформи (V4L2 на GNU/Linux), зображення і послідовності зображень — своїм вбудованим бекендом зображень, а відеофайли і потоки — бекендами FFmpeg чи GStreamer збірки OpenCV. Маніфест flatpak збирає OpenCV без FFmpeg, GStreamer і V4L2, тож пакунок flatpak читає лише зображення і послідовності зображень.
