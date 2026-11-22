## Вмикання оцінювання пози MoveNet

Для того щоб увімкнути у проекті модель оцінювання пози MultiPose Lightning [MoveNet](https://www.tensorflow.org/hub/tutorials/movenet) від Google (17 ключових точок COCO до шести тіл), необхідно встановити значення `ON` для CMake змінної `ENABLE_MOVENET` (для гілки `appMoveNet` воно типове):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_MOVENET=ON
cmake --build build --target all
```

Програма цієї гілки побудована навколо MoveNet, тож тут ця опція обов'язкова: крок конфігурування CMake завершується з поясненням, якщо опцію вимкнено значенням `OFF`.

Модель MoveNet виконує встановлений у системі [ONNX Runtime](https://onnxruntime.ai/), див. розділ [Вмикання ONNX Runtime](/doc/sections/uk_UA/5-project-build/ai/5-83-enabling-the-ONNX-Runtime.md), а модуль [cmake/enablers/ai/template-project-movenet-enabler.cmake](/cmake/enablers/ai/template-project-movenet-enabler.cmake) завантажує її.

| Змінна | Що вона містить |
| --- | --- |
| `PROJECT_POSE_MODEL` | ONNX-модель MoveNet MultiPose, яку завантажує програма, доки параметр командного рядка `--model` (або `-m`) не задає іншої, завантажена, якщо змінна порожня, тож нічого не завантажується, коли її задано |
| `TEMPLATE_APP_MOVENET_MODEL_URL`, `TEMPLATE_APP_MOVENET_MODEL_SHA256` | модель, яку завантажує конфігурування, і її контрольна сума SHA256, типово закріплена ONNX-конвертація моделі MultiPose Lightning |
| `ENABLE_MOVENET_MODEL_DOWNLOAD` | завантажує модель у директорію `TEMPLATE_APP_POSE_MODELS_DIR` під час конфігурування і встановлює її разом з виконуваним файлом, типово `ON` |
| `TEMPLATE_APP_POSE_MODELS_DIR` | директорія, в яку завантажуються моделі, типово `misc/models` дерева вихідних кодів |

### Модель

Параметр `--model` (або `-m`) приймає ONNX-файл моделі MoveNet MultiPose: на вході кадр RGB типу `int32` форми `[1, height, width, 3]`, сторони якого кратні 32, а на виході тіла форми `[1, 6, 56]`, кожне з яких — 17 ключових точок (ніс, далі око, вухо, плече, лікоть, зап'ясток, стегно, коліно і щиколотка, кожна спершу ліва, потім права) значень (y, x, оцінка), нормалізованих до входу, за якими йдуть рамка і оцінка тіла. Контролер масштабує кадр так, щоб його довша сторона мала 256 пікселів, і доповнює коротшу до кратної 32, так, як це робить TF.js pose detection, і залишає тіла з оцінкою щонайменше 0.25.

Google публікує моделі MoveNet лише у форматах TFLite, SavedModel і TF.js, тож тут працює ONNX-конвертація з репозиторію Hugging Face [Xenova/movenet-multipose-lightning](https://huggingface.co/Xenova/movenet-multipose-lightning).

Конфігурування завантажує 19 МБ `tf2onnx`-конвертацію моделі MultiPose Lightning з цього репозиторію, закріплену за її комітом, у директорію `misc/models` дерева вихідних кодів, поза директоріями побудови, які скрипти `scripts/build` стирають при кожному конфігуруванні, тож усі директорії побудови дерева вихідних кодів, хоч як вони звуться, поділяють одне завантаження, а файли `.gitignore` і `.dockerignore` тримають його поза комітами і docker-збірками. Кожен файл спершу перевіряється за контрольною сумою SHA256 (і видобувається зі свого архіву) у директорії `.part` поруч з моделями, тож перерване чи пошкоджене завантаження ніколи не сприймається за модель, а невдале лише попереджає, лишаючи параметр `--model` способом задати модель. Вимкніть завантаження параметром `-DENABLE_MOVENET_MODEL_DOWNLOAD=OFF` або вкажіть власну модель змінною `PROJECT_POSE_MODEL`.

### Встановлення моделі

Крок встановлення (і кожен пакунок, зібраний з нього: deb, rpm, AppImage, FreeBSD pkg, інсталятор MS Windows) копіює завантажену модель у директорію `share/CppAppTemplate` префікса встановлення, наприклад у `/usr/share/CppAppTemplate/movenet-multipose-lightning.onnx`, і встановлений виконуваний файл працює без дерева вихідних кодів. Клас `app::DataLocator` файлу [src/app/DataLocator.h](/src/app/DataLocator.h) обирає модель, яку завантажує запущений виконуваний файл, доки не задано параметр `--model`: спершу встановлену відносно розташування виконуваного файлу (тож перенесений пакунок, наприклад AppImage, працює й далі), далі завантажену в директорію моделей (виконуваний файл, запущений з дерева побудови), далі встановлену під налаштованим префіксом. Вимкнене чи невдале завантаження не встановлює жодної моделі, а модель змінної `PROJECT_POSE_MODEL` завантажується з того місця, де вона є.

### Ліцензії

Моделі MoveNet поширюються під ліцензією Apache-2.0, яку Google вказує для всіх них, а репозиторій [Xenova/movenet-multipose-lightning](https://huggingface.co/Xenova/movenet-multipose-lightning) — для своєї конвертації, ONNX Runtime — під ліцензією MIT, а OpenCV — під [Apache-2.0](https://github.com/opencv/opencv/blob/4.x/LICENSE), тож їхні повідомлення про авторські права і тексти ліцензій супроводжують поширюваний виконуваний файл.

### Компоненти

Директорія [src/MoCap](/src/MoCap) містить незалежні від рушія вихідні коди захоплення рухів тіла простору імен `mocap`, інтерфейс оцінювача яких реалізує рушій [src/MoveNet](/src/MoveNet) цієї гілки:

| Клас | Що він робить |
| --- | --- |
| `mocap::FrameSource` | читає кадри камери, зображення, послідовності зображень, відеофайлу чи потоку модулем videoio бібліотеки OpenCV, див. розділ [Вмикання інтеграції OpenCV](/doc/sections/uk_UA/5-project-build/5-65-enabling-the-OpenCV.md) |
| `mocap::IPoseEstimator` | інтерфейс рушіїв оцінювання пози: завантажує модель і оцінює пози кадру BGR, а виклик `create` надає рушій, який долучає збірка |
| `mocap::MotionCapture` | оцінює пози кожного кадру, який читає `FrameSource`, засобами `IPoseEstimator` |
| `movenet::MoveNetController` | оцінює пози ONNX-моделлю MoveNet MultiPose |
| `movenet::MoveNetDecoder` | декодує тіла з оцінкою щонайменше 0.25 з виходу моделі |
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

Виклик `estimate` інтерфейсу `mocap::IPoseEstimator` оцінює пози власного кадру, а визначення `mocap::IPoseEstimator::create` у вихідних кодах рушія обирає рушій, тож інший рушій займає місце MoveNet заміною одного класу.
