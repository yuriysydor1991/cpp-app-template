## Вмикання розпізнавання мовлення whisper.cpp

Для того щоб увімкнути бібліотеку розпізнавання мовлення [whisper.cpp](https://github.com/ggml-org/whisper.cpp) (порт моделі OpenAI [Whisper](https://github.com/openai/whisper) на C/C++) для проекту, необхідно встановити значення `ON` для CMake змінної `ENABLE_WHISPERCPP` (для гілки `appWhisperCPP` це значення за замовчуванням):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_WHISPERCPP=ON
cmake --build build --target all
```

Модуль [cmake/enablers/ai/template-project-whispercpp-enabler.cmake](/cmake/enablers/ai/template-project-whispercpp-enabler.cmake) спершу шукає встановлену в системі whisper.cpp. Ubuntu 26.04 і Debian forky постачають її пакет розробки (скрипти `scripts/packages/install-ubuntu.sh` і `scripts/packages/install-debian.sh` встановлюють його скрізь, де він доступний):

```
sudo apt install -y libwhisper-dev
```

Без нього тег `TEMPLATE_APP_WHISPERCPP_GIT_TAG` (за замовчуванням `v1.9.4`) репозиторію `TEMPLATE_APP_WHISPERCPP_GIT` завантажується і збирається через мережу Інтернет. Обидва шляхи надають ту саму ціль `whisper`, тому прилінковуй її до своїх цільових об'єктів:

```
target_link_libraries(${PROJECT_BINARY_NAME} whisper)
```

Завантажені вихідні коди збирають тензорну бібліотеку [ggml](https://github.com/ggml-org/ggml) під процесор машини збірки, тому передавай параметр `-DGGML_NATIVE=OFF` збірці, яка має працювати й на інших машинах (пакувальники flatpak і snap цієї гілки так і роблять).

### Модель

whisper.cpp розпізнає мовлення за допомогою [ggml-моделі](https://huggingface.co/ggerganov/whisper.cpp) Whisper, яка не є частиною збірки, тож конфігурування завантажує модель `TEMPLATE_APP_WHISPERCPP_MODEL` у директорію `models` дерева збірки. За замовчуванням це багатомовна модель `small` розміром 466 МіБ, яка розпізнає англійську, українську та інші мови Whisper.

Завантаження виконує скрипт [download-ggml-model.sh](https://github.com/ggml-org/whisper.cpp/blob/master/models/download-ggml-model.sh) з whisper.cpp (у MS Windows - скрипт `download-ggml-model.cmd`), якому потрібен інструмент `curl` або `wget`. Жоден системний пакет не постачає цього скрипта, тож конфігурування спершу завантажує скрипт випуску `TEMPLATE_APP_WHISPERCPP_GIT_TAG`. Кожне дерево збірки один раз завантажує власну модель, а невдале завантаження лише попереджає, залишаючи для моделі параметр `--model`. Іншу модель обирає змінна `TEMPLATE_APP_WHISPERCPP_MODEL`:

```
cmake -S . -B build -DTEMPLATE_APP_WHISPERCPP_MODEL=large-v3-turbo
```

| Змінна | Що вона тримає |
| --- | --- |
| `TEMPLATE_APP_WHISPERCPP_MODEL` | модель для завантаження, наприклад багатомовна `tiny`, `base`, `small`, `medium`, `large-v3-turbo`, квантована на кшталт `small-q5_1` або їхній англомовний варіант `.en` |
| `ENABLE_WHISPERCPP_MODEL_DOWNLOAD` | завантажує модель під час конфігурування, за замовчуванням `ON` |
| `PROJECT_WHISPER_MODEL_PATH` | модель, яку завантажує програма, поки параметр командного рядка `--model` (або `-m`) не задає іншої, а якщо змінна порожня - завантажену модель, тож коли змінну задано, нічого не завантажується |
| `PROJECT_WHISPER_LANGUAGE` | код мови мовлення (`en`, `uk`, `de` тощо), яку розпізнають багатомовні моделі, `auto` для її визначення |

Більші моделі розпізнають точніше, але довше обробляють висловлювання. Автоматичне визначення обирає мову кожного висловлювання окремо і може помилитися на короткому висловлюванні, тож для мовлення однією мовою задай змінній `PROJECT_WHISPER_LANGUAGE` значення `uk` (або іншої мови). Англомовні моделі розпізнають англійську мову незалежно від значення цієї змінної. Підійде будь-яка модель зі [списку моделей whisper.cpp](https://github.com/ggml-org/whisper.cpp/tree/master/models), тож можна завантажити її вручну і вказати на неї параметром командного рядка:

```
./src/CppAppTemplate --model /шлях/до/ggml-small.bin
```

### Компоненти

Директорія [src/WhisperCPP](/src/WhisperCPP) містить три невеликі класи простору імен `whisperi`:

| Клас | Що він робить |
| --- | --- |
| `Microphone` | захоплює типовий мікрофон системи через аудіопідсистему SDL2, дивись розділ [Вмикання захоплення мікрофона SDL2](/doc/sections/uk_UA/5-project-build/audio/5-59-enabling-the-SDL2-microphone-capture.md) |
| `UtteranceDetector` | розрізає захоплене аудіо на висловлювання за паузами мовлення |
| `WhisperController` | завантажує модель whisper, слухає `Microphone` і розпізнає висловлювання, які завершує `UtteranceDetector` |

Виклик `init` класу `whisperi::WhisperController` з файлу [src/WhisperCPP/WhisperController.h](/src/WhisperCPP/WhisperController.h) завантажує модель і приймає мову мовлення. Кожен виклик `listen` захоплює мікрофон упродовж наступних 100 мс (відкриваючи його під час першого виклику) і повертає текст висловлювання, завершеного за цей час, порожній текст, поки нічого завершеного не сказано, або `std::nullopt` у разі помилки. Виклик `transcribe` розпізнає задані монофонічні відліки з частотою 16 кГц, наприклад декодований аудіофайл:

```
auto whisper = whisperi::WhisperController::create();

if (whisper->init("models/ggml-base.en.bin", "auto")) {
  while (keepListening) {
    if (const auto text = whisper->listen(); text && !text->empty()) {
      LOGI(*text);
    }
  }
}
```

`UtteranceDetector` розпізнає мовлення за гучністю: кадр тривалістю 30 мс, утричі гучніший за рівень шуму оточення, вважається мовленням. Висловлювання починається за 300 мс до мовлення, тож його перше слово не обрізається, і закінчується паузою у 750 мс або досягнувши тривалості 15 с. Його налаштовують константи файлу [src/WhisperCPP/UtteranceDetector.h](/src/WhisperCPP/UtteranceDetector.h).

Повідомлення whisper.cpp і ggml потрапляють у журнал проекту: помилки і попередження на власних рівнях, інформаційні на рівні налагодження, а решта на рівні трасування, тож підніми CMake змінну `MAX_LOG_LEVEL`, щоб їх побачити. Найперший виклик `init` завантажує модулі обчислень ggml, зібраної з динамічно завантажуваними модулями (наприклад, ggml з пакету Debian), яка без них нічого не обчислює.

Метод `app::Application::run` файлу [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) записує кожне розпізнане висловлювання у журнал макросом `LOGI`, доки його не зупинять клавіші Ctrl+C, тож заміни запис у журнал власною обробкою мовлення.

### Тести

Тести `UTEST_WhisperController` і `CTEST_WhisperController` розпізнають мовлення порожньою моделлю власних тестів whisper.cpp (без жодних ваг, тож вона не розпізнає тексту) і [зразком мовлення](https://github.com/ggml-org/whisper.cpp/tree/master/samples) з її вихідних кодів, які завантажуються під час конфігурування тестів. Аудіодрайвер `disk` бібліотеки SDL2 програє цей зразок у мікрофон компонентного тесту, який розпізнає його слова завантаженою моделлю `PROJECT_WHISPER_MODEL_PATH`. Тестові випадки, яким бракує файлів, пропускаються.

### Пакування

Пакет DEB залежить від пакетів whisper.cpp, ggml і SDL2, з якими лінкується виконуваний файл, за допомогою інструменту `dpkg-shlibdeps`. Flatpak спершу збирає whisper.cpp з вихідних кодів і бере SDL2 з середовища виконання freedesktop, тоді як snap завантажує whisper.cpp через модуль CMake і додає SDL2. Завантажена whisper.cpp встановлює свої бібліотеки поруч з виконуваним файлом (і свої заголовки також), тож пакети, зібрані без системної whisper.cpp, містять їх.

Модель лишається у дереві збірки, тож жоден пакет її не містить, а збірки flatpak і snap не завантажують її взагалі: передай модель параметром `--model`. Flatpak читає її з домашньої директорії і записує мікрофон через сокет PulseAudio, тоді як snap потребує вручну під'єднаного інтерфейсу `audio-record`:

```
sudo snap connect cppapptemplate:audio-record
```
