## Вмикання MediaPipe Pose landmarker

Для того щоб увімкнути у проекті [MediaPipe Pose](https://ai.google.dev/edge/mediapipe/solutions/vision/pose_landmarker) landmarker від Google (33 точки BlazePose до чотирьох тіл у 3D), необхідно встановити значення `ON` для CMake змінної `ENABLE_MEDIAPIPE` (для гілки `appMediaPipePose` воно типове):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_MEDIAPIPE=ON
cmake --build build --target all
```

Програма цієї гілки побудована навколо MediaPipe, тож тут ця опція обов'язкова: крок конфігурування CMake завершується з поясненням, якщо опцію вимкнено значенням `OFF`.

MediaPipe збирається лише засобами Bazel, а її офіційний PyPI-пакунок (wheel) містить попередньо зібрану бібліотеку MediaPipe Tasks C API, яку завантажує Python Tasks API, тож модуль [cmake/enablers/ai/template-project-mediapipe-enabler.cmake](/cmake/enablers/ai/template-project-mediapipe-enabler.cmake) отримує пакунок `mediapipe-1.2.3` для GNU/Linux x86-64 засобами `FetchContent` (перевіряючи його контрольну суму SHA256), бере з нього бібліотеку `libmediapipe.so` і завантажує заголовкові файли C API з вихідних кодів того самого випуску, закріплених за його комітом. Бібліотека працює лише на GNU/Linux x86-64 (деінде конфігурування завершується з поясненням), потребує бібліотек `libEGL.so.1` і `libGLESv2.so.2` (пакунки `libegl1` і `libgles2` Debian і Ubuntu) і містить власне середовище виконання C++, тож не поділяє з виконуваним файлом жодних об'єктів C++.

Модуль надає імпортовану ціль `MediaPipe::mediapipe`, тож долучіть її до своїх цілей:

```
target_link_libraries(${PROJECT_BINARY_NAME} MediaPipe::mediapipe)
```

Встановлення кладе бібліотеку та її файли ліцензій у приватну директорію `lib/CppAppTemplate` префікса встановлення (у директорію `lib/<multiarch>/CppAppTemplate` з префіксом `/usr`), де встановлений виконуваний файл знаходить бібліотеку за своїм відносним до `$ORIGIN` RPATH, тож встановлений, запакований і зібраний у дереві побудови виконуваний файл працюють без змінної `LD_LIBRARY_PATH`.

| Змінна | Що вона містить |
| --- | --- |
| `TEMPLATE_APP_MEDIAPIPE_WHEEL_URL`, `TEMPLATE_APP_MEDIAPIPE_WHEEL_SHA256` | PyPI-пакунок MediaPipe, з якого береться бібліотека C API, і його контрольна сума SHA256, типово `mediapipe-1.2.3` для GNU/Linux x86-64 |
| `TEMPLATE_APP_MEDIAPIPE_SOURCES_URL` | вихідні коди MediaPipe, з яких завантажуються заголовкові файли C API, типово коміту випуску v1.2.3 |
| `PROJECT_POSE_MODEL` | модель `.task` pose landmarker-а, яку завантажує програма, доки параметр командного рядка `--model` (або `-m`) не задає іншої, завантажена, якщо змінна порожня, тож нічого не завантажується, коли її задано |
| `TEMPLATE_APP_MEDIAPIPE_MODEL_URL`, `TEMPLATE_APP_MEDIAPIPE_MODEL_SHA256` | модель, яку завантажує конфігурування, і її контрольна сума SHA256, типово `pose_landmarker_full` |
| `ENABLE_MEDIAPIPE_MODEL_DOWNLOAD` | завантажує модель у директорію `TEMPLATE_APP_POSE_MODELS_DIR` під час конфігурування і встановлює її разом з виконуваним файлом, типово `ON` |
| `TEMPLATE_APP_POSE_MODELS_DIR` | директорія, в яку завантажуються моделі, типово `misc/models` дерева вихідних кодів |

### Модель

Параметр `--model` (або `-m`) приймає модель `.task` pose landmarker-а MediaPipe: пакет детектора пози і детектора точок пози топології BlazePose GHUM 3D з 33 точок. Контролер запускає landmarker у відеорежимі строго зростаючих часових міток, тож він відстежує тіла від кадру до кадру замість того, щоб наново виявляти їх на кожному, знаходить до чотирьох тіл і перетворює нормалізовані точки в пікселі кадру, а видимість стає оцінкою ключової точки.

Конфігурування завантажує 9 МБ модель `pose_landmarker_full` від Google у директорію `misc/models` дерева вихідних кодів, поза директоріями побудови, які скрипти `scripts/build` стирають при кожному конфігуруванні, тож усі директорії побудови дерева вихідних кодів, хоч як вони звуться, поділяють одне завантаження, а файли `.gitignore` і `.dockerignore` тримають його поза комітами і docker-збірками. Кожен файл спершу перевіряється за контрольною сумою SHA256 (і видобувається зі свого архіву) у директорії `.part` поруч з моделями, тож перерване чи пошкоджене завантаження ніколи не сприймається за модель, а невдале лише попереджає, лишаючи параметр `--model` способом задати модель. Вимкніть завантаження параметром `-DENABLE_MEDIAPIPE_MODEL_DOWNLOAD=OFF` або вкажіть власну модель змінною `PROJECT_POSE_MODEL`.

Моделі `pose_landmarker_lite` і `pose_landmarker_heavy` сторінки [MediaPipe pose landmarker](https://ai.google.dev/edge/mediapipe/solutions/vision/pose_landmarker) обмінюють точність на швидкість і навпаки, тож вкажіть одну з них змінними `TEMPLATE_APP_MEDIAPIPE_MODEL_URL` і `TEMPLATE_APP_MEDIAPIPE_MODEL_SHA256` або завантажте її вручну:

```
mkdir -p ~/models && cd ~/models
curl -SL -O https://storage.googleapis.com/mediapipe-models/pose_landmarker/pose_landmarker_heavy/float16/1/pose_landmarker_heavy.task

# з директорії побудови
./src/CppAppTemplate --model ~/models/pose_landmarker_heavy.task
```

### Встановлення моделі

Крок встановлення (і кожен пакунок, зібраний з нього: deb, rpm, AppImage, FreeBSD pkg, інсталятор MS Windows) копіює завантажену модель у директорію `share/CppAppTemplate` префікса встановлення, наприклад у `/usr/share/CppAppTemplate/pose_landmarker_full.task`, і встановлений виконуваний файл працює без дерева вихідних кодів. Клас `app::DataLocator` файлу [src/app/DataLocator.h](/src/app/DataLocator.h) обирає модель, яку завантажує запущений виконуваний файл, доки не задано параметр `--model`: спершу встановлену відносно розташування виконуваного файлу (тож перенесений пакунок, наприклад AppImage, працює й далі), далі завантажену в директорію моделей (виконуваний файл, запущений з дерева побудови), далі встановлену під налаштованим префіксом. Вимкнене чи невдале завантаження не встановлює жодної моделі, а модель змінної `PROJECT_POSE_MODEL` завантажується з того місця, де вона є.

### Ліцензії

MediaPipe поширюється під ліцензією [Apache-2.0](https://github.com/google-ai-edge/mediapipe/blob/master/LICENSE), а файли ліцензії і NOTICE її пакунка лягають поруч зі встановленою бібліотекою, тоді як моделі pose landmarker-а поширюються під ліцензією Apache-2.0, яку вказує копія тієї самої моделі на Hugging Face [litert-community/MediaPipe-PoseLandmarker-Full](https://huggingface.co/litert-community/MediaPipe-PoseLandmarker-Full). OpenCV поширюється під ліцензією [Apache-2.0](https://github.com/opencv/opencv/blob/4.x/LICENSE).

### Компоненти

Директорія [src/MoCap](/src/MoCap) містить незалежні від рушія вихідні коди захоплення рухів тіла простору імен `mocap`, інтерфейс оцінювача яких реалізує рушій [src/MediaPipe](/src/MediaPipe) цієї гілки:

| Клас | Що він робить |
| --- | --- |
| `mocap::FrameSource` | читає кадри камери, зображення, послідовності зображень, відеофайлу чи потоку модулем videoio бібліотеки OpenCV, див. розділ [Вмикання інтеграції OpenCV](/doc/sections/uk_UA/5-project-build/5-65-enabling-the-OpenCV.md) |
| `mocap::IPoseEstimator` | інтерфейс рушіїв оцінювання пози: завантажує модель і оцінює пози кадру BGR, а виклик `create` надає рушій, який долучає збірка |
| `mocap::MotionCapture` | оцінює пози кожного кадру, який читає `FrameSource`, засобами `IPoseEstimator` |
| `mediapipei::MediaPipeController` | відстежує пози кадрів відео pose landmarker-ом MediaPipe Tasks C API |
| `mediapipei::LandmarksDecoder` | декодує нормалізовані точки результату landmarker-а в пікселі кадру |

Кожна поза — це ключові точки тіла в порядку ключових точок моделі, а кожна ключова точка — кортеж її положення в пікселях кадру (глибина в масштабі осі x, що менша, то ближче до камери) та її оцінки. Виклик `init` класу `mocap::MotionCapture` файлу [src/MoCap/MotionCapture.h](/src/MoCap/MotionCapture.h) завантажує модель, а виклик `open` відкриває вхід: камеру заданого індексу (`0` — типова камера) або зображення, послідовність зображень (`frame_%03d.png`), відеофайл чи URL потоку заданого шляху. Кожен виклик `capture` оцінює пози наступного кадру (порожні, якщо тіла немає) або повертає `std::nullopt` наприкінці входу чи у разі збою, який записує в журнал макрос `LOGE`:

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

Виклик `estimate` інтерфейсу `mocap::IPoseEstimator` оцінює пози власного кадру, а визначення `mocap::IPoseEstimator::create` у вихідних кодах рушія обирає рушій, тож інший рушій займає місце MediaPipe заміною одного класу.
