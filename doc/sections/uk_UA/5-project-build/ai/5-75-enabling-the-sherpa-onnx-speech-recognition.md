## Вмикання розпізнавання мовлення sherpa-onnx

Для того щоб увімкнути у проекті бібліотеку розпізнавання мовлення [sherpa-onnx](https://github.com/k2-fsa/sherpa-onnx) (офлайн нейромережевий рушій мовлення моделей NeMo Parakeet, Whisper, Zipformer та інших поверх [onnxruntime](https://github.com/microsoft/onnxruntime)), необхідно встановити значення `ON` для CMake змінної `ENABLE_SHERPA_ONNX` (для гілки `appSherpaONNXSTT` воно типове):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_SHERPA_ONNX=ON
cmake --build build --target all
```

Програма цієї гілки побудована навколо sherpa-onnx, тож тут ця опція обов'язкова: крок конфігурування CMake завершується з поясненням, якщо опцію вимкнено значенням `OFF`.

Жоден дистрибутив не пакує sherpa-onnx, тож модуль [cmake/enablers/ai/template-project-sherpa-onnx-enabler.cmake](/cmake/enablers/ai/template-project-sherpa-onnx-enabler.cmake) завантажує вихідні коди її випуску `v1.13.8` засобами `FetchContent` (потрібні інструмент `git` і доступ до інтернету) та збирає лише бібліотеки її C та C++ API: без виконуваних файлів, Python, тестів, синтезу мовлення, PortAudio, websocket, GPU і діаризації мовців. sherpa-onnx виконує моделі встановленою в системі onnxruntime, якщо дистрибутив її пакує (пакет `libonnxruntime-dev` Ubuntu 26.04 і Debian 13, пакет `onnxruntime-devel` Fedora, порт `misc/onnxruntime` FreeBSD), а інакше завантажує власну попередньо зібрану (збірки Ubuntu 24.04, RHEL, flatpak і snap). Змінні оточення `SHERPA_ONNXRUNTIME_INCLUDE_DIR` і `SHERPA_ONNXRUNTIME_LIB_DIR` вказують конфігуруванню на onnxruntime у власному розташуванні:

```
sudo apt install -y libonnxruntime-dev
SHERPA_ONNXRUNTIME_INCLUDE_DIR=/opt/onnxruntime/include SHERPA_ONNXRUNTIME_LIB_DIR=/opt/onnxruntime/lib cmake -S . -B build
```

Модуль надає ціль `SherpaONNX::cxx-api` спільної бібліотеки C++ API, тож долучіть її до своїх цілей:

```
target_link_libraries(${PROJECT_BINARY_NAME} SherpaONNX::cxx-api)
```

Встановлення кладе спільні бібліотеки sherpa-onnx (і завантажену onnxruntime) у приватну директорію `lib/CppAppTemplate` префікса встановлення (у директорію `lib/<multiarch>/CppAppTemplate` з префіксом `/usr`), де встановлений виконуваний файл знаходить їх за своїм відносним до `$ORIGIN` RPATH, тож встановлений, запакований і зібраний у дереві побудови виконуваний файл працюють без змінної `LD_LIBRARY_PATH`.

| Змінна | Що вона містить |
| --- | --- |
| `TEMPLATE_APP_SHERPA_ONNX_GIT`, `TEMPLATE_APP_SHERPA_ONNX_GIT_TAG` | репозиторій sherpa-onnx і тег, який завантажує конфігурування, за замовчуванням `v1.13.8` |
| `PROJECT_STT_MODEL` | директорія моделі, якою програма розпізнає мовлення, поки параметр командного рядка `--model` (або `-m`) не задає іншої, а якщо змінна порожня - завантажена модель `TEMPLATE_APP_SHERPA_ONNX_MODEL`, тож коли змінну задано, нічого не завантажується |
| `TEMPLATE_APP_SHERPA_ONNX_MODEL` | модель-трансдюсер NeMo випуску [asr-models](https://github.com/k2-fsa/sherpa-onnx/releases/tag/asr-models) sherpa-onnx, яку завантажує конфігурування, за замовчуванням `sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8` |
| `ENABLE_SHERPA_ONNX_MODEL_DOWNLOAD` | завантажує модель у директорію `models` дерева побудови під час конфігурування і встановлює її разом з виконуваним файлом, за замовчуванням `ON` |
| `TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256` | контрольна сума SHA256 архіву моделі, за замовчуванням відома сума моделей `sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8`, `sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8` і `sherpa-onnx-nemo-fast-conformer-transducer-be-de-en-es-fr-hr-it-pl-ru-uk-20k-int8` |

### Модель

Параметр `--model` (або `-m`) приймає директорію моделі-трансдюсера NeMo (Parakeet TDT, FastConformer тощо), у яку розпаковуються архіви випуску `asr-models` sherpa-onnx: мережі `encoder`, `decoder` і `joiner` (файли `.onnx` або квантовані `.int8.onnx`) та файл `tokens.txt`. Контролер повідомляє sherpa-onnx вид моделі - трансдюсер NeMo, що позбавляє її завантаження кодувальника заради виду з його метаданих.

Типова модель `sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8` (архів розміром 465 МіБ квантованої int8 моделі [Parakeet TDT 0.6B v3](https://huggingface.co/nvidia/parakeet-tdt-0.6b-v3) від NVIDIA, 640 МіБ у розпакованому вигляді) розпізнає мовлення 25 європейських мов - болгарської, хорватської, чеської, данської, нідерландської, англійської, естонської, фінської, французької, німецької, грецької, угорської, італійської, латиської, литовської, мальтійської, польської, португальської, румунської, російської, словацької, словенської, іспанської, шведської та української - сама визначаючи мову кожного висловлювання, і розставляє розділові знаки та великі літери. Конфігурування завантажує її та перевіряє її контрольну суму один раз для кожного дерева побудови, а невдале завантаження лише попереджає, залишаючи для моделі параметр `--model`. Вимкніть завантаження параметром `-DENABLE_SHERPA_ONNX_MODEL_DOWNLOAD=OFF`, завантажте іншу модель параметром `-DTEMPLATE_APP_SHERPA_ONNX_MODEL=<модель>` або вкажіть змінною `PROJECT_STT_MODEL` на власну модель. Вчетверо менша модель `sherpa-onnx-nemo-fast-conformer-transducer-be-de-en-es-fr-hr-it-pl-ru-uk-20k-int8`, наприклад, розпізнає білоруське, німецьке, англійське, іспанське, французьке, хорватське, італійське, польське, російське та українське мовлення:

```
cmake -S . -B build -DTEMPLATE_APP_SHERPA_ONNX_MODEL=sherpa-onnx-nemo-fast-conformer-transducer-be-de-en-es-fr-hr-it-pl-ru-uk-20k-int8
```

Підійде й будь-яка інша модель-трансдюсер NeMo цього випуску, тож можна завантажити її вручну і вказати на неї параметром командного рядка:

```
mkdir -p ~/models && cd ~/models
curl -SL -O https://github.com/k2-fsa/sherpa-onnx/releases/download/asr-models/sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8.tar.bz2
tar xf sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8.tar.bz2

# з директорії побудови
./src/CppAppTemplate --model ~/models/sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8
```

### Встановлення моделі

Завантажена директорія моделі є частиною дерева побудови, тож крок встановлення (а також кожен пакет, зібраний на його основі: deb, rpm, AppImage, пакет FreeBSD, інсталятор MS Windows) копіює її, окрім записів `test_wavs`, до директорії `share/CppAppTemplate` префікса встановлення, наприклад у директорію `/usr/share/CppAppTemplate/sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8`, і встановлений виконуваний файл працює без дерева побудови. Клас `app::DataLocator` з файлу [src/app/DataLocator.h](/src/app/DataLocator.h) обирає модель, яку завантажує запущений виконуваний файл, поки параметр `--model` не задає іншої: спершу встановлену відносно розташування виконуваного файлу (тож перенесений пакет, наприклад AppImage, і далі працює), потім завантажену в дерево побудови (виконуваний файл, запущений з нього), а потім встановлену за налаштованим префіксом. Вимкнене або невдале завантаження не встановлює жодної моделі, а модель змінної `PROJECT_STT_MODEL` завантажується з того місця, де вона є.

### Ліцензії

sherpa-onnx поширюється за ліцензією [Apache-2.0](https://github.com/k2-fsa/sherpa-onnx/blob/master/LICENSE), а onnxruntime - за ліцензією [MIT](https://github.com/microsoft/onnxruntime/blob/main/LICENSE), тож поширюваний виконуваний файл супроводжують їхні повідомлення про авторські права й тексти ліцензій. Моделі - це дані з власними ліцензіями: Parakeet TDT 0.6B v3 поширюється за ліцензією [CC-BY-4.0](https://huggingface.co/nvidia/parakeet-tdt-0.6b-v3), яка вимагає зазначати авторство NVIDIA, а картка кожної іншої моделі називає її власну ліцензію. Перевірте ліцензію моделі, яку поширюєте разом зі своєю програмою чи для неї: пакети, зібрані із завантаженою моделлю, містять її, а параметр `-DENABLE_SHERPA_ONNX_MODEL_DOWNLOAD=OFF` залишає модель поза ними.

### Складові

Директорія [src/STT](/src/STT) містить незалежні від рушія вихідні коди розпізнавання мовлення простору імен `stt`, інтерфейс розпізнавача яких реалізує рушій гілки з директорії [src/SherpaONNX](/src/SherpaONNX):

| Клас | Що він робить |
| --- | --- |
| `stt::Microphone` | захоплює типовий мікрофон системи через аудіопідсистему SDL2, дивись розділ [Вмикання захоплення мікрофона SDL2](/doc/sections/uk_UA/5-project-build/audio/5-59-enabling-the-SDL2-microphone-capture.md) |
| `stt::UtteranceDetector` | розрізає захоплене аудіо на висловлювання за паузами мовлення |
| `stt::ISpeechRecognizer` | інтерфейс рушіїв мовлення: завантажує модель і розпізнає текст заданих монофонічних відліків з частотою 16 кГц, а виклик `create` надає рушій, який лінкує збірка |
| `stt::SpeechListener` | слухає `Microphone` і розпізнає засобами `ISpeechRecognizer` висловлювання, які завершує `UtteranceDetector` |
| `sherpaonnx::SherpaONNXController` | завантажує модель-трансдюсер NeMo директорії і розпізнає мовлення засобами sherpa-onnx |

Виклик `init` класу `stt::SpeechListener` з файлу [src/STT/SpeechListener.h](/src/STT/SpeechListener.h) завантажує модель. Кожен виклик `listen` захоплює мікрофон упродовж наступних 100 мс (відкриваючи його під час першого виклику) і повертає текст висловлювання, завершеного за цей час, порожній текст, поки нічого завершеного не сказано, або `std::nullopt` у разі помилки, яку журналює макрос `LOGE`. Виклик `recognize` інтерфейсу `stt::ISpeechRecognizer` розпізнає задані відліки, наприклад декодований аудіофайл:

```
auto listener = stt::SpeechListener::create();

if (listener->init("models/sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8")) {
  while (keepListening) {
    if (const auto text = listener->listen(); text && !text->empty()) {
      LOGI(*text);
    }
  }
}
```

`UtteranceDetector` розпізнає мовлення за гучністю: кадр тривалістю 30 мс, утричі гучніший за рівень шуму оточення, вважається мовленням. Висловлювання починається за 300 мс до мовлення, тож його перше слово не обрізається, і закінчується паузою у 750 мс або досягнувши тривалості 15 с. Його налаштовують константи файлу [src/STT/UtteranceDetector.h](/src/STT/UtteranceDetector.h).

Метод `app::Application::run` з файлу [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) записує кожне розпізнане висловлювання у журнал макросом `LOGI`, доки його не зупинять клавіші Ctrl+C, тож заміни запис у журнал власною обробкою мовлення. Він знає лише вихідні коди `src/STT`, тож інший рушій заступає sherpa-onnx власною директорією `src/<рушій>`, яка визначає виклик `stt::ISpeechRecognizer::create`, і власним модулем увімкнення.

### Тести

Тести `UTEST_Microphone` і `UTEST_UtteranceDetector` перевіряють мікрофон з аудіодрайверами SDL2, які обираються лише явно, і висловлювання згенерованих тонів, тест `UTEST_SpeechListener` перевіряє слухача з імітаціями мікрофона й розпізнавача, а тест `UTEST_SherpaONNXController` перевіряє контролер з імітацією C++ API sherpa-onnx, тож охоплює кожну невдачу рушія. Тест `CTEST_SherpaONNXController` розпізнає англійський зразок мовлення, який постачається із завантаженою моделлю, і [український](https://github.com/k2-fsa/sherpa-onnx/releases/tag/asr-models), який завантажує конфігурування тестів, та програє англійський зразок у мікрофон справжнього `SpeechListener` аудіодрайвером `disk` SDL2, тож звукова карта участі не бере. Тестові випадки, яким бракує не завантажених конфігуруванням файлів, пропускаються.

### Пакування

Пакет DEB містить спільні бібліотеки sherpa-onnx у своїй приватній директорії бібліотек і через інструмент `dpkg-shlibdeps` залежить від пакетів SDL2 та onnxruntime, які лінкують бібліотеки, або містить завантажену onnxruntime, якщо дистрибутив її не пакує. Flatpak і snap під час збирання завантажують sherpa-onnx і попередньо зібрану onnxruntime (модуль flatpak для цього має доступ до мережі), як і образ Docker. Жоден з них не містить моделі, на відміну від пакета DEB та інших пакетів збірки із завантаженою моделлю (дивіться встановлення моделі вище): flatpak читає моделі домашньої директорії, тож передавайте їм параметр `--model`. Flatpak записує мікрофон через сокет PulseAudio, тоді як snap потребує вручну під'єднаного інтерфейсу `audio-record`:

```
sudo snap connect cppapptemplate:audio-record
```
