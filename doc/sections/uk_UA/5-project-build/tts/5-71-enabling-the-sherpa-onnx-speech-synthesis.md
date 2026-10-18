## Вмикання синтезу мовлення sherpa-onnx

Для того щоб увімкнути у проекті бібліотеку синтезу мовлення [sherpa-onnx](https://github.com/k2-fsa/sherpa-onnx) (офлайн нейромережевий рушій мовлення моделей Kokoro, MeloTTS, Piper та інших поверх [onnxruntime](https://github.com/microsoft/onnxruntime)), необхідно встановити значення `ON` для CMake змінної `ENABLE_SHERPA_ONNX` (для гілки `appSherpaONNX` воно типове):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_SHERPA_ONNX=ON
cmake --build build --target all
```

Програма цієї гілки побудована навколо sherpa-onnx, тож тут ця опція обов'язкова: крок конфігурування CMake завершується з поясненням, якщо опцію вимкнено значенням `OFF`.

Жоден дистрибутив не пакує sherpa-onnx, тож модуль [cmake/enablers/tts/template-project-sherpa-onnx-enabler.cmake](/cmake/enablers/tts/template-project-sherpa-onnx-enabler.cmake) завантажує вихідні коди її випуску `v1.13.8` засобами `FetchContent` (потрібні інструмент `git` і доступ до інтернету) та збирає лише бібліотеки її C та C++ API: без виконуваних файлів, Python, тестів, PortAudio, websocket, GPU і діаризації мовців. sherpa-onnx виконує моделі встановленою в системі onnxruntime, якщо дистрибутив її пакує (пакет `libonnxruntime-dev` Ubuntu 26.04 і Debian 13, пакет `onnxruntime-devel` Fedora, порт `misc/onnxruntime` FreeBSD), а інакше завантажує власну попередньо зібрану (збірки Ubuntu 24.04, RHEL, flatpak і snap). Змінні оточення `SHERPA_ONNXRUNTIME_INCLUDE_DIR` і `SHERPA_ONNXRUNTIME_LIB_DIR` вказують конфігуруванню на onnxruntime у власному розташуванні:

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
| `PROJECT_TTS_TEXT` | текст, який промовляє програма, поки параметр командного рядка `--text` (або `-t`) не задає іншого, за замовчуванням `Hello, sherpa-onnx! Insert your text here!` |
| `PROJECT_TTS_VOICE` | голос, яким промовляє програма, поки параметр командного рядка `--voice` (або `-s`) не задає іншого, за замовчуванням завантажена модель `TEMPLATE_APP_SHERPA_ONNX_MODEL` |
| `TEMPLATE_APP_SHERPA_ONNX_MODEL` | модель випуску [tts-models](https://github.com/k2-fsa/sherpa-onnx/releases/tag/tts-models) sherpa-onnx, яку завантажує конфігурування, за замовчуванням `kokoro-int8-multi-lang-v1_0` |
| `ENABLE_SHERPA_ONNX_MODEL_DOWNLOAD` | завантажує модель у директорію `models` дерева побудови під час конфігурування, за замовчуванням `ON` |
| `TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256` | контрольна сума SHA256 архіву моделі, за замовчуванням відома сума моделей `kokoro-int8-multi-lang-v1_0`, `kokoro-multi-lang-v1_0`, `kokoro-int8-en-v0_19`, `kokoro-en-v0_19`, `vits-melo-tts-zh_en` і `vits-piper-en_US-amy-low-int8` |

### Голоси

Параметр `--voice` (або `-s`) приймає директорію моделі, у яку розпаковуються архіви випуску `tts-models` sherpa-onnx, за якою може йти ідентифікатор мовця `:<id>` багатоголосої моделі (інакше говорить перший мовець). Контролер розпізнає вид моделі за файлами директорії:

| Вид моделі | Файли директорії |
| --- | --- |
| Kokoro | `model.onnx` (або `model.int8.onnx`), `voices.bin`, `tokens.txt`, директорія `espeak-ng-data` і, для багатомовних моделей, `lexicon-us-en.txt` та `lexicon-zh.txt` |
| VITS (Piper, MeloTTS, MMS тощо) | `model.onnx` (або `<голос>.onnx` голосу Piper), `tokens.txt` і або директорія `espeak-ng-data` голосів Piper, або `lexicon.txt` моделей MeloTTS |

Типова модель `kokoro-int8-multi-lang-v1_0` (архів розміром 126 МБ квантованої int8 моделі [Kokoro-82M](https://huggingface.co/hexgrad/Kokoro-82M) v1.0, 183 МБ у розпакованому вигляді) промовляє англійський і китайський текст своїх лексиконів 54 мовцями (ідентифікатори від `:0` до `:53` англійських, китайських, іспанських, французьких, гінді, італійських, японських і португальських голосів моделі) з частотою 24 кГц, а конфігурування завантажує й перевіряє її один раз для кожного дерева побудови. Вимкніть завантаження параметром `-DENABLE_SHERPA_ONNX_MODEL_DOWNLOAD=OFF`, завантажте іншу модель параметром `-DTEMPLATE_APP_SHERPA_ONNX_MODEL=<модель>` або вкажіть змінною `PROJECT_TTS_VOICE` на власну модель.

Китайсько-англійська модель [MeloTTS](https://github.com/myshell-ai/MeloTTS) і голоси [Piper](https://github.com/rhasspy/piper) говорять через той самий параметр:

```
mkdir -p ~/models && cd ~/models
curl -SL -O https://github.com/k2-fsa/sherpa-onnx/releases/download/tts-models/vits-melo-tts-zh_en.tar.bz2
curl -SL -O https://github.com/k2-fsa/sherpa-onnx/releases/download/tts-models/vits-piper-en_US-amy-low-int8.tar.bz2
curl -SL -O https://github.com/k2-fsa/sherpa-onnx/releases/download/tts-models/vits-piper-uk_UA-lada-x_low-int8.tar.bz2
for archive in *.tar.bz2 ; do tar xf "${archive}" ; done

# з директорії побудови
./src/CppAppTemplate -t "它也支持英文, and English too." -s ~/models/vits-melo-tts-zh_en
./src/CppAppTemplate -t "Hello, Piper!" -s ~/models/vits-piper-en_US-amy-low-int8
./src/CppAppTemplate -t "Привіт, світе!" -s ~/models/vits-piper-uk_UA-lada-x_low-int8
```

Модель MeloTTS говорить з частотою 44,1 кГц, а голоси Piper - з частотою своїх карток моделей (16 кГц для `x_low` і `low`, 22,05 кГц для `medium` і `high`). Конфігурування так само завантажує будь-яку з них у дерево побудови, наприклад параметром `-DTEMPLATE_APP_SHERPA_ONNX_MODEL=vits-melo-tts-zh_en`.

### Ліцензії

sherpa-onnx поширюється за ліцензією [Apache-2.0](https://github.com/k2-fsa/sherpa-onnx/blob/master/LICENSE), а onnxruntime - за ліцензією [MIT](https://github.com/microsoft/onnxruntime/blob/main/LICENSE), тож поширюваний виконуваний файл супроводжують їхні повідомлення про авторські права й тексти ліцензій. Моделі - це дані з власними ліцензіями: Kokoro-82M поширюється за ліцензією [Apache-2.0](https://huggingface.co/hexgrad/Kokoro-82M), MeloTTS - за ліцензією [MIT](https://github.com/myshell-ai/MeloTTS/blob/main/LICENSE), а кожен голос Piper має ліцензію свого навчального набору даних, яку називає файл `MODEL_CARD` директорії голосу (деякі з них забороняють комерційне використання). Перевірте ліцензію моделі, яку поширюєте разом зі своєю програмою чи для неї.

### Складові

Директорія [src/SherpaONNX](/src/SherpaONNX) містить рушій мовлення гілки. Він реалізує інтерфейс `tts::ISpeechSynthesizer` незалежних від рушія вихідних кодів [src/TTS](/src/TTS):

| Клас | Що він робить |
| --- | --- |
| `tts::Speech` | зберігає синтезовані монофонічні 16-бітні відліки з їхньою частотою і тривалістю |
| `tts::ISpeechSynthesizer` | інтерфейс рушіїв мовлення: промовляє заданий текст заданим голосом у `tts::Speech`, а виклик `create` надає рушій, який лінкує збірка |
| `tts::WavWriter` | записує `tts::Speech` у 16-бітний монофонічний WAV-файл PCM |
| `tts::AudioPlayer` | відтворює `tts::Speech` типовим пристроєм відтворення звуку, дивись розділ [Вмикання відтворення звуку SDL2](/doc/sections/uk_UA/5-project-build/audio/5-68-enabling-the-SDL2-audio-playback.md) |
| `sherpaonnx::SherpaONNXModel` | модель директорії: розпізнає вид моделі за її файлами і надає конфігурацію sherpa-onnx цієї моделі |
| `sherpaonnx::KokoroModel`, `sherpaonnx::VitsModel` | види моделей Kokoro і VITS, які конфігурують sherpa-onnx власними файлами |
| `sherpaonnx::SherpaONNXController` | синтезує мовлення засобами sherpa-onnx |

Виклик `synthesize` контролера завантажує модель директорії голосу (і тримає її завантаженою для наступного виклику з тією ж директорією), перевіряє ідентифікатор мовця серед мовців моделі, генерує мовлення і перетворює його відліки з рухомою комою на 16-бітні, повертаючи `std::nullopt` у разі невдачі: директорії без відомої моделі, завантаження моделі чи невідомого мовця, кожну з яких журналює макрос `LOGE`:

```
auto synthesizer = tts::ISpeechSynthesizer::create();

if (const auto speech = synthesizer->synthesize("Hello, world!", "models/kokoro-int8-multi-lang-v1_0:3")) {
  tts::WavWriter::create()->write(*speech, "speech.wav");
}
```

Метод `app::Application::run` з файлу [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) промовляє текст і голос командного рядка, записуючи мовлення у WAV-файл параметра `--output` (або `-o`) чи відтворюючи його в іншому разі. Він знає лише інтерфейси вихідних кодів `src/TTS`, тож інший рушій заступає sherpa-onnx власною директорією `src/<рушій>`, яка визначає виклик `tts::ISpeechSynthesizer::create`, і власним модулем увімкнення: саме так роблять гілки `appESpeakNG`, `appRHVoice` і `appPiperTTS`.

### Тести

Тест `UTEST_SherpaONNXModel` перевіряє розпізнавання виду моделі та конфігурації директорій Kokoro, Piper і MeloTTS, тест `UTEST_SherpaONNXController` перевіряє контролер з імітацією C++ API sherpa-onnx, тож охоплює кожну невдачу рушія, а тести `CTEST_SherpaONNXController` і `CTEST_app` синтезують англійське мовлення кількох мовців завантаженою моделлю Kokoro, перевіряють записані WAV-файли і відтворюють мовлення аудіодрайвером `dummy` SDL2, тож звукова карта участі не бере. Тестові випадки, яким потрібна модель, пропускають себе, поки конфігурування її не завантажує.

### Пакування

Пакет DEB містить спільні бібліотеки sherpa-onnx у своїй приватній директорії бібліотек і через інструмент `dpkg-shlibdeps` залежить від пакетів SDL2 та onnxruntime, які лінкують бібліотеки, або містить завантажену onnxruntime, якщо дистрибутив її не пакує. Flatpak і snap під час збирання завантажують sherpa-onnx і попередньо зібрану onnxruntime (модуль flatpak для цього має доступ до мережі), як і образ Docker. Жоден з них не містить моделі: flatpak читає моделі домашньої директорії, тож передавайте їм параметр `--voice`. Flatpak відтворює мовлення через сокет PulseAudio і записує файли параметра `--output` у домашню директорію, а snap відтворює його через інтерфейс `audio-playback`.
