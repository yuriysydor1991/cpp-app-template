## Вмикання ONNX Runtime

Для того щоб увімкнути у проекті [ONNX Runtime](https://onnxruntime.ai/) (кросплатформний рушій виконання ONNX-моделей), необхідно встановити значення `ON` для CMake змінної `ENABLE_ONNXRUNTIME` (для гілки `appRTMW` воно типове):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_ONNXRUNTIME=ON
cmake --build build --target all
```

Оцінювання пози цієї гілки виконує свої моделі засобами ONNX Runtime, тож тут ця опція обов'язкова: крок конфігурування CMake завершується з поясненням, якщо опцію вимкнено значенням `OFF`.

Модуль [cmake/enablers/ai/template-project-onnxruntime-enabler.cmake](/cmake/enablers/ai/template-project-onnxruntime-enabler.cmake) знаходить встановлений у системі ONNX Runtime за його конфігурацією пакета CMake: пакет `libonnxruntime-dev` Ubuntu 26.04 і Debian 13, пакет `onnxruntime-devel` Fedora, порт `misc/onnxruntime` FreeBSD або формулу `onnxruntime` Homebrew. Ubuntu 24.04, RHEL і база core24 пакунка snap не пакують ONNX Runtime, середовище freedesktop пакунка flatpak також його не містить, а попередньо зібрані архіви випусків ONNX Runtime на GitHub недосяжні, оскільки репозиторій microsoft/onnxruntime відповідає 404 (перевірено 2026-11-22), тож там змінна `onnxruntime_DIR` вказує конфігуруванню на ONNX Runtime у власному розташуванні:

```
sudo apt install -y libonnxruntime-dev
cmake -S . -B build -Donnxruntime_DIR=/opt/onnxruntime/lib/cmake/onnxruntime
```

Модуль надає ціль `onnxruntime::onnxruntime`, тож долучіть її до своїх цілей:

```
target_link_libraries(${PROJECT_BINARY_NAME} onnxruntime::onnxruntime)
```

Клас `onnxi::ONNXModel` файлу [src/ONNX/ONNXModel.h](/src/ONNX/ONNXModel.h) завантажує файл ONNX-моделі і виконує її на CPU: виклик `run` приймає неперервну матрицю OpenCV типу float (`CV_32F`) або int32 (`CV_32S`) розмірностей першого входу моделі і повертає виходи моделі в її порядку, або жодного у разі збою, який записує в журнал макрос `LOGE`, а виклик `planar` перетворює зображення з чергуванням каналів типу float у планарний (NCHW) тензор, який приймає більшість моделей комп'ютерного зору:

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

Збірка ONNX Runtime 1.23.2 в Ubuntu 26.04 друкує у стандартний потік помилок сотні рядків `Schema error: Trying to register schema ... already registered`, які нічого не змінюють у виконанні моделей. ONNX Runtime поширюється під ліцензією MIT, тож його повідомлення про авторські права і текст ліцензії супроводжують поширюваний виконуваний файл.
