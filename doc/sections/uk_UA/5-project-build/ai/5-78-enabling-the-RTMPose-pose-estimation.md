## Вмикання оцінювання пози RTMPose

Для того щоб увімкнути у проекті оцінювання пози [RTMPose](https://github.com/open-mmlab/mmpose/tree/main/projects/rtmpose) від OpenMMLab (17 ключових точок COCO кожної людини, яку знаходить детектор YOLOX), необхідно встановити значення `ON` для CMake змінної `ENABLE_RTMPOSE` (для гілки `appRTMPose` воно типове):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_RTMPOSE=ON
cmake --build build --target all
```

Програма цієї гілки побудована навколо RTMPose, тож тут ця опція обов'язкова: крок конфігурування CMake завершується з поясненням, якщо опцію вимкнено значенням `OFF`.

Моделі RTMPose і YOLOX виконує встановлений у системі [ONNX Runtime](https://onnxruntime.ai/), див. розділ [Вмикання ONNX Runtime](/doc/sections/uk_UA/5-project-build/ai/5-83-enabling-the-ONNX-Runtime.md), а модуль [cmake/enablers/ai/template-project-rtmpose-enabler.cmake](/cmake/enablers/ai/template-project-rtmpose-enabler.cmake) завантажує їх.

| Змінна | Що вона містить |
| --- | --- |
| `PROJECT_POSE_MODEL` | директорія моделей `detector.onnx` і `pose.onnx`, які завантажує програма, доки параметр командного рядка `--model` (або `-m`) не задає іншої, завантажена, якщо змінна порожня, тож нічого не завантажується, коли її задано |
| `TEMPLATE_APP_RTMPOSE_MODEL_URL`, `TEMPLATE_APP_RTMPOSE_MODEL_SHA256` | модель пози, яку завантажує конфігурування, і її контрольна сума SHA256, типово архів RTMPose-m |
| `TEMPLATE_APP_RTMPOSE_DETECTOR_URL`, `TEMPLATE_APP_RTMPOSE_DETECTOR_SHA256` | архів детектора людей, який завантажує конфігурування, і його контрольна сума SHA256, типово YOLOX-tiny |
| `ENABLE_RTMPOSE_MODEL_DOWNLOAD` | завантажує моделі в директорію `TEMPLATE_APP_POSE_MODELS_DIR` під час конфігурування і встановлює їх разом з виконуваним файлом, типово `ON` |
| `TEMPLATE_APP_POSE_MODELS_DIR` | директорія, в яку завантажуються моделі, типово `misc/models` дерева вихідних кодів |

### Модель

Параметр `--model` (або `-m`) приймає директорію двох ONNX-моделей експорту MMDeploy: детектора людей YOLOX `detector.onnx`, разом з його придушенням немаксимумів, і низхідної моделі родини RTMPose `pose.onnx` з виходами SimCC (класифікації координат). Детектор приймає кадр, масштабований у верхній лівий кут свого входу, решту якого заповнює сіре доповнення, і залишає людей з оцінкою понад 0.3. Модель пози приймає кожну рамку людини, розширену на чверть і доведену до співвідношення сторін свого входу, з каналами RGB, нормалізованими середніми і відхиленнями ImageNet, а комірка найвищого відгуку кожної осі SimCC дає координату ключової точки і менший з відгуків осей x та y дає її оцінку, так, як це робить MMPose.

Конфігурування завантажує офіційні ONNX-експорти OpenMMLab, які поєднує [rtmlib](https://github.com/Tau-J/rtmlib): 51 МБ архів моделі RTMPose-m 17 ключових точок COCO і 19 МБ архів детектора людей YOLOX-tiny, моделі `end2end.onnx` яких видобуваються як `pose.onnx` і `detector.onnx` директорії `misc/models/rtmpose-m`, у директорію `misc/models` дерева вихідних кодів, поза директоріями побудови, які скрипти `scripts/build` стирають при кожному конфігуруванні, тож усі директорії побудови дерева вихідних кодів, хоч як вони звуться, поділяють одне завантаження, а файли `.gitignore` і `.dockerignore` тримають його поза комітами і docker-збірками. Кожен файл спершу перевіряється за контрольною сумою SHA256 (і видобувається зі свого архіву) у директорії `.part` поруч з моделями, тож перерване чи пошкоджене завантаження ніколи не сприймається за модель, а невдале лише попереджає, лишаючи параметр `--model` способом задати модель. Вимкніть завантаження параметром `-DENABLE_RTMPOSE_MODEL_DOWNLOAD=OFF` або вкажіть власну модель змінною `PROJECT_POSE_MODEL`.

Інші експорти родини RTMPose від OpenMMLab (RTMPose-l, моделі Halpe26 з 26 ключовими точками разом зі стопами, моделі всього тіла RTMW) працюють так само, тож вкажіть одну з них змінними `TEMPLATE_APP_RTMPOSE_MODEL_URL` і `TEMPLATE_APP_RTMPOSE_MODEL_SHA256` або покладіть її модель `end2end.onnx` як `pose.onnx` поруч з `detector.onnx` власної директорії і задайте цю директорію параметром `--model`.

### Встановлення моделі

Крок встановлення (і кожен пакунок, зібраний з нього: deb, rpm, AppImage, FreeBSD pkg, інсталятор MS Windows) копіює завантажену модель у директорію `share/CppAppTemplate` префікса встановлення, наприклад у `/usr/share/CppAppTemplate/rtmpose-m`, і встановлений виконуваний файл працює без дерева вихідних кодів. Клас `app::DataLocator` файлу [src/app/DataLocator.h](/src/app/DataLocator.h) обирає модель, яку завантажує запущений виконуваний файл, доки не задано параметр `--model`: спершу встановлену відносно розташування виконуваного файлу (тож перенесений пакунок, наприклад AppImage, працює й далі), далі завантажену в директорію моделей (виконуваний файл, запущений з дерева побудови), далі встановлену під налаштованим префіксом. Вимкнене чи невдале завантаження не встановлює жодної моделі, а модель змінної `PROJECT_POSE_MODEL` завантажується з того місця, де вона є.

### Ліцензії

MMPose, моделі RTMPose і YOLOX від OpenMMLab поширюються під ліцензією [Apache-2.0](https://github.com/open-mmlab/mmpose/blob/main/LICENSE), ONNX Runtime — під ліцензією MIT, а OpenCV — під [Apache-2.0](https://github.com/opencv/opencv/blob/4.x/LICENSE), тож їхні повідомлення про авторські права і тексти ліцензій супроводжують поширюваний виконуваний файл. Набори даних, на яких навчено моделі, мають власні умови.

### Компоненти

Директорія [src/MoCap](/src/MoCap) містить незалежні від рушія вихідні коди захоплення рухів тіла простору імен `mocap`, інтерфейс оцінювача яких реалізує рушій [src/RTMPose](/src/RTMPose) цієї гілки:

| Клас | Що він робить |
| --- | --- |
| `mocap::FrameSource` | читає кадри камери, зображення, послідовності зображень, відеофайлу чи потоку модулем videoio бібліотеки OpenCV, див. розділ [Вмикання інтеграції OpenCV](/doc/sections/uk_UA/5-project-build/5-65-enabling-the-OpenCV.md) |
| `mocap::IPoseEstimator` | інтерфейс рушіїв оцінювання пози: завантажує модель і оцінює пози кадру BGR, а виклик `create` надає рушій, який долучає збірка |
| `mocap::MotionCapture` | оцінює пози кожного кадру, який читає `FrameSource`, засобами `IPoseEstimator` |
| `rtmpose::RTMPoseController` | знаходить людей на кадрі засобами `PersonDetector` і оцінює їхні ключові точки засобами `PoseModel` |
| `rtmpose::PersonDetector` | виявляє людей на кадрі ONNX-моделлю YOLOX |
| `rtmpose::PoseModel` | оцінює ключові точки рамки людини низхідною ONNX-моделлю родини RTMPose |
| `rtmpose::PoseCrop` | масштабує розширену рамку людини у вхід моделі і переносить точки входу моделі назад на кадр |
| `rtmpose::SimCCDecoder` | декодує ключові точки з виходів SimCC моделі так, як це робить MMPose |
| `onnxi::ONNXModel` | виконує ONNX-модель засобами ONNX Runtime, див. розділ [Вмикання ONNX Runtime](/doc/sections/uk_UA/5-project-build/ai/5-83-enabling-the-ONNX-Runtime.md) |

Кожна поза — це ключові точки тіла в порядку ключових точок моделі, а кожна ключова точка — кортеж її положення в пікселях кадру (глибина нульова) та її оцінки. Виклик `init` класу `mocap::MotionCapture` файлу [src/MoCap/MotionCapture.h](/src/MoCap/MotionCapture.h) завантажує модель, а виклик `open` відкриває вхід: камеру заданого індексу (`0` — типова камера) або зображення, послідовність зображень (`frame_%03d.png`), відеофайл чи URL потоку заданого шляху. Кожен виклик `capture` оцінює пози наступного кадру (порожні, якщо тіла немає) або повертає `std::nullopt` наприкінці входу чи у разі збою, який записує в журнал макрос `LOGE`:

```
#include "src/MoCap/MotionCapture.h"

auto capture = mocap::MotionCapture::create();

if (capture->init(model) && capture->open("dance.mp4")) {
  while (const auto poses = capture->capture()) {
    for (const auto& pose : *poses) {
      const auto& [position, score] = pose.front();
      // position.x, position.y і position.z першої ключової точки
    }
  }
}
```

Виклик `estimate` інтерфейсу `mocap::IPoseEstimator` оцінює пози власного кадру, а визначення `mocap::IPoseEstimator::create` у вихідних кодах рушія обирає рушій, тож інший рушій займає місце RTMPose заміною одного класу.
