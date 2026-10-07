## Вмикання виявлення об'єктів darknetxx

Для того щоб увімкнути виявлення об'єктів [darknetxx](https://github.com/yuriysydor1991/darknetxx) (порт нейронної мережі [Darknet](https://github.com/AlexeyAB/darknet) на C++) для проекту, необхідно встановити значення `ON` для CMake змінної `ENABLE_DARKNETXX` (для гілки `appDarknetXX` це значення за замовчуванням):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_DARKNETXX=ON
cmake --build build --target all
```

darknetxx - це програма, створена з цього самого шаблону, тож жоден системний пакет її не постачає, а спільна бібліотека, яку вона збирає, експортує лише фасад, який зберігає виявлені об'єкти у файли, а не передає їх. Тож модуль [cmake/enablers/ai/template-project-darknetxx-enabler.cmake](/cmake/enablers/ai/template-project-darknetxx-enabler.cmake) завантажує через мережу Інтернет вихідні коди коміту `TEMPLATE_APP_DARKNETXX_GIT_TAG` (за замовчуванням перевіреного, адже darknetxx поки не має тегів випусків) репозиторію `TEMPLATE_APP_DARKNETXX_GIT` і збирає з них мережеве ядро у статичну бібліотеку `darknetxx`: оригінальний C код Darknet, який обчислює за допомогою C++ інфраструктури мереж darknetxx (пам'ять шарів і мереж, завантажувач cfg-файлів мереж, читачі, записувачі й валідатори файлів ваг мереж). Ядру потрібні бібліотеки [OpenCV](https://opencv.org/), [zlib](https://zlib.net/) і [nlohmann JSON](https://github.com/nlohmann/json), остання завантажується, якщо її не встановлено, а ядра обчислень Darknet працюють на всіх ядрах процесора завдяки OpenMP компілятора:

```
sudo apt install -y libopencv-dev zlib1g-dev nlohmann-json3-dev
```

Стандартна змінна FetchContent натомість збирає локальну копію darknetxx, наприклад, з власними змінами:

```
cmake -S . -B build -DFETCHCONTENT_SOURCE_DIR_DARKNETXX=/шлях/до/darknetxx
```

Змінна `ENABLE_DARKNETXX_AVX` (за замовчуванням `ON` для збірок x86_64 компіляторами GCC і Clang) компілює AVX/FMA ядра обчислень C ядра Darknet у збірки, відмінні від Debug, які працюють у кілька разів швидше, проте тоді виконуваний файл потребує процесора з підтримкою AVX2. Тож передавай параметр `-DENABLE_DARKNETXX_AVX=OFF` збірці, яка має працювати на будь-якій машині (пакувальники flatpak і snap цієї гілки так і роблять).

### Заголовки darknetxx

darknetxx створено з цього самого шаблону, тож її заголовки мають шляхи заголовків проекту (`src/log/log.h`, `src/log/default-logger/DefaultLogger.h` тощо) і оголошують класи з тими самими іменами (`default_logger::DefaultLogger`, `default_logger::RealDefaultLogger`). Обидва набори співіснують в одному виконуваному файлі, адже:

- вихідні коди, які включають заголовки darknetxx, компілюються з директоріями включення `DARKNETXX_INCLUDE_DIRS` перед директоріями проекту (як `SYSTEM` директорії, тож попередження проекту не стосуються сторонніх заголовків) і з визначеннями `DARKNETXX_COMPILE_DEFINITIONS`, які перейменовують простір імен `default_logger` darknetxx на `darknetxx_default_logger`;
- вихідні коди проекту ніколи не включають заголовків darknetxx: заголовки директорії [src/DarknetXX](/src/DarknetXX) не пропускають їх, тож проект включає їх у звичний спосіб.

Тож компілюй власні вихідні коди, які включають заголовки darknetxx, так само, як файл [src/DarknetXX/CMakeLists.txt](/src/DarknetXX/CMakeLists.txt) компілює адаптер:

```
target_include_directories(<target> SYSTEM PRIVATE ${DARKNETXX_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_compile_definitions(<target> PRIVATE ${DARKNETXX_COMPILE_DEFINITIONS})
target_link_libraries(<target> PUBLIC darknetxx)
```

Бібліотека `darknetxx` не містить журналу darknetxx: його реалізує директорія [src/DarknetXX/log](/src/DarknetXX/log), яка спрямовує повідомлення darknetxx у журнал проекту. Помилки і попередження зберігають власні рівні, а інформаційні повідомлення і повідомлення налагодження опускаються на рівень нижче (лише завантаження мережі записує десятки інформаційних повідомлень, таблицю шарів тощо), тож підніми CMake змінну `MAX_LOG_LEVEL`, щоб їх побачити. Ця ж змінна вмикає компіляцію повідомлень налагодження і трасування ядра darknetxx.

### Мережа

За замовчуванням програма виявляє об'єкти мережею [YOLOv4-tiny](https://github.com/AlexeyAB/darknet#pre-trained-models), навченою на 80 класах набору даних [COCO](https://cocodataset.org/): cfg-файл мережі, імена класів і зразок зображення постачаються з вихідними кодами darknetxx, а файл ваг розміром 23 МіБ конфігурування завантажує у директорію `models` дерева збірки. Кожне дерево збірки завантажує ваги один раз, а невдале завантаження лише попереджає, залишаючи для ваг параметр `--weights` (`--dxxwjz1` або `--dxxwjz2`).

| Змінна | Що вона тримає |
| --- | --- |
| `TEMPLATE_APP_DARKNETXX_WEIGHTS_URL` | файл ваг для завантаження, за замовчуванням ваги YOLOv4-tiny |
| `TEMPLATE_APP_DARKNETXX_WEIGHTS_SHA256` | хеш SHA256 завантаженого файлу, порожній, щоб пропустити перевірку |
| `ENABLE_DARKNETXX_WEIGHTS_DOWNLOAD` | завантажує файл ваг під час конфігурування, за замовчуванням `ON` |
| `PROJECT_DARKNETXX_CFG_PATH` | cfg-файл мережі, який завантажує програма, поки ні параметр `--cfg` (або `-c`), ні параметр `--dxxwjz2` не задає іншого, а якщо змінна порожня - файл `yolov4-tiny.cfg` darknetxx |
| `PROJECT_DARKNETXX_WEIGHTS_PATH` | оригінальний файл ваг, який завантажує програма, поки жоден з параметрів `--weights` (або `-w`), `--dxxwjz1` і `--dxxwjz2` не задає іншого, а якщо змінна порожня - завантажений файл, тож коли змінну задано, нічого не завантажується |
| `PROJECT_DARKNETXX_NAMES_PATH` | файл імен класів, якими програма позначає об'єкти, поки ні параметр `--names` (або `-n`), ні параметр `--dxxwjz2` не задає іншого, а якщо змінна порожня - файл `coco.names` darknetxx |
| `PROJECT_DARKNETXX_IMAGE_PATH` | зображення, на якому програма виявляє об'єкти, поки параметр `--image` (або `-i`) не задає іншого, а якщо змінна порожня - файл `dog.jpg` darknetxx |

Підійде будь-яка мережа Darknet, зокрема навчена darknetxx, тож вкажи на її файли параметрами командного рядка:

```
./src/CppAppTemplate --cfg yolov4.cfg --weights yolov4.weights --names coco.names --image /шлях/до/зображення.jpg
```

### Файли ваг мереж

Програма читає файли ваг усіх трьох форматів, які читає darknetxx (дивись розділ [Файли ваг мереж](https://github.com/yuriysydor1991/darknetxx/blob/master/doc/sections/uk_UA/4-7-4-network-weights-files.md) darknetxx):

| Формат | Параметр командного рядка | Клас |
| --- | --- | --- |
| оригінальний файл ваг Darknet (`*.weights`), двійкові масиви шарів, структуру яких задає лише cfg-файл мережі | `--weights` (або `-w`) | `darknetxxi::OrigWeights` |
| файл dxxwjz1 darknetxx (`*.dxxwjz1`), стиснутий gzip JSON документ тих самих масивів, які знаходяться за їхніми шарами й іменами | `--dxxwjz1` | `darknetxxi::Dxxwjz1Weights` |
| файл dxxwjz2 darknetxx (`*.dxxwjz2`), документ dxxwjz1 разом з мережею, до якої належать ваги: текстом її cfg-файлу, іменами класів і записом її навчання | `--dxxwjz2` | `darknetxxi::Dxxwjz2Weights` |

Формати без втрат перетворюються один в одний виконуваним файлом `darknetxxConverter` darknetxx, а файл dxxwjz2 ще й зберігає мережу з cfg-файлу і файлу імен класів (`--convert-to dxxwjz1` створює файл dxxwjz1 лише з вагами):

```
darknetxxConverter --convert-from weights --convert-src yolov4-tiny.weights \
  --convert-to dxxwjz2 --convert-dst yolov4-tiny.dxxwjz2 --convert-cfg yolov4-tiny.cfg \
  --convert-names coco.names
```

Сам файл dxxwjz2 є мережею для виявлення: параметр `--dxxwjz2` завантажує мережу з тексту cfg, який зберігає файл, разом з її вагами і позначає об'єкти іменами класів, які зберігає файл, а параметри `--cfg` і `--names` мають перевагу над мережею та іменами класів файлу:

```
./src/CppAppTemplate --dxxwjz2 yolov4-tiny.dxxwjz2 --image /шлях/до/зображення.jpg
```

Мережу файлу визначає розширення імені файлу `.dxxwjz2`, так само як її визначає darknetxx, тож параметр `--cfg` теж приймає файл dxxwjz2 (параметри `--cfg yolov4-tiny.dxxwjz2 --weights yolov4-tiny.weights` завантажують оригінальні ваги в мережу файлу dxxwjz2). Файл dxxwjz2 без ваг, тобто мережа для навчання, яку darknetxx створює з cfg-файлу, нічого не виявляє, тож відхиляється з помилкою.

Валідатори darknetxx перевіряють кожен файл на відповідність мережі перед завантаженням, тож файл іншої мережі або іншого формату (наприклад, файл dxxwjz1, переданий параметру `--weights`) відхиляється з помилкою, а обрізаний файл завантажується з попередженням. Нестиснутий gzip JSON текст файлу dxxwjz1 також завантажується з попередженням.

Кожен формат - це клас, похідний від класу `darknetxxi::NetworkWeights`, який викликає метод власного формату інтерфейсу `darknetxxi::WeightsLoader`, що його реалізує контролер, тож жодне значення не розрізняє форматів. Формат майбутньої darknetxx додає власний клас і метод інтерфейсу, як це зробив формат dxxwjz2.

### Компоненти

Директорія [src/DarknetXX](/src/DarknetXX) містить класи простору імен `darknetxxi`:

| Клас | Що він робить |
| --- | --- |
| `DarknetXXController` | завантажує мережу cfg-файлу (або файлу dxxwjz2) з вагами будь-якого формату і виявляє нею об'єкти на зображеннях |
| `NetworkWeights`, `OrigWeights`, `Dxxwjz1Weights`, `Dxxwjz2Weights` | файли ваг мереж різних форматів |
| `WeightsLoader` | інтерфейс завантажувачів форматів файлів ваг |
| `DarknetImage` | власник зображення Darknet (площинних RGB чисел з рухомою комою), створеного із зображення OpenCV |
| `Detection` | виявлений об'єкт: ім'я класу, ймовірність і прямокутник у пікселях зображення |
| `DarknetXXLog` | приймач повідомлень журналу darknetxx, який спрямовує їх у журнал проекту |

Виклик `init` класу `darknetxxi::DarknetXXController` з файлу [src/DarknetXX/DarknetXXController.h](/src/DarknetXX/DarknetXXController.h) завантажує мережу cfg-файлу (або файлу dxxwjz2) для пакету з одного зображення з заданими вагами і файлом імен класів (порожній шлях бере імена класів, які зберігають ваги dxxwjz2, а інакше нумерує класи). Кожен виклик `detect` читає зображення будь-якого формату, який читає OpenCV, змінює його розмір до входу мережі (для мереж з `letter_box=1` - зберігаючи пропорції), обчислює і повертає об'єкти з імовірністю, вищою за `THRESHOLD` (0.25), після придушення немаксимумів, або `std::nullopt` у разі помилки:

```
auto darknetxx = darknetxxi::DarknetXXController::create();

// the network, the class names and the weights of the dxxwjz2 file
if (darknetxx->init("yolov4-tiny.dxxwjz2", darknetxxi::Dxxwjz2Weights{"yolov4-tiny.dxxwjz2"},
                    "")) {
  if (const auto objects = darknetxx->detect("dog.jpg")) {
    for (const auto& object : *objects) {
      LOGI(object);  // dog: 84% [137, 205, 181 x 332]
    }
  }
}
```

Метод `app::Application::run` файлу [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) завантажує мережу, задану параметрами командного рядка (або типовими значеннями вище), виявляє об'єкти на зображенні і записує кожен виявлений об'єкт у журнал макросом `LOGI`, тож заміни запис у журнал власною обробкою об'єктів.

### Тести

Тест `UTEST_DarknetXXController` завантажує в ядро darknetxx власну крихітну мережу: maxpool усього зображення, згортку 1x1 без ваг, окрім зміщень, і YOLO шар з однієї комірки, а файли ваг усіх форматів записує сам тест (файли dxxwjz2 зберігають мережу того самого cfg і власне ім'я класу). Лише зміщення визначають виходи YOLO, тож тест знає той самий прямокутник, який мережа виявляє на будь-якому зображенні, а ваги dxxwjz1 і dxxwjz2 виявляють ті самі об'єкти, що й оригінальні, зокрема й сам файл dxxwjz2 без cfg-файлу. Тести `UTEST_DarknetImage`, `UTEST_Detection` і `UTEST_NetworkWeights` перевіряють решту класів, а тест `CTEST_DarknetXXController` виявляє об'єкти на зразку зображення darknetxx завантаженою мережею YOLOv4-tiny (тестові випадки, яким вона потрібна, пропускаються без завантажених ваг) і перевіряє повідомлення darknetxx у журналі проекту.

### Пакування

Ядро darknetxx статично лінкується у виконуваний файл, тож жоден пакет не містить бібліотеки darknetxx, а пакет DEB залежить від пакетів OpenCV та інших, з якими лінкується виконуваний файл, за допомогою інструменту `dpkg-shlibdeps`. Flatpak спершу збирає з вихідних кодів потрібні ядру модулі OpenCV і бере вихідні коди darknetxx архівом того самого коміту, тоді як snap додає бібліотеки OpenCV з Ubuntu.

Файли мережі лишаються у дереві збірки, тож жоден пакет їх не містить, а збірки flatpak і snap не завантажують їх взагалі: передай їх параметрами `--cfg`, `--weights` (або `--dxxwjz1`), `--names` і `--image` або параметрами `--dxxwjz2` і `--image`. Flatpak читає їх з домашньої директорії.
