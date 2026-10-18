## Вмикання синтезу мовлення RHVoice

Для того щоб увімкнути у проекті бібліотеку синтезу мовлення [RHVoice](https://github.com/RHVoice/RHVoice) (статистичний параметричний синтезатор англійської, української, російської, польської та ще з десятка інших мов), необхідно встановити значення `ON` для CMake змінної `ENABLE_RHVOICE` (для гілки `appRHVoice` це значення за замовчуванням):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_RHVOICE=ON
cmake --build build --target all
```

Програма цієї гілки побудована навколо RHVoice, тож тут ця опція обов'язкова: крок конфігурування CMake завершується з поясненням, якщо опцію вимкнено значенням `OFF`.

Модуль [cmake/enablers/tts/template-project-rhvoice-enabler.cmake](/cmake/enablers/tts/template-project-rhvoice-enabler.cmake) знаходить встановлену в системі RHVoice за її заголовком `RHVoice.h` і бібліотекою `RHVoice`, оскільки жодна інсталяція RHVoice не постачає файлу `pkg-config` чи пакета CMake, а бібліотека під час роботи читає дані голосів своєї інсталяції. Встанови її пакет розробки разом з голосами (це роблять скрипти `scripts/packages`):

```
sudo apt install -y librhvoice-dev rhvoice-english rhvoice-ukrainian
```

| Дистрибутив | Пакети |
| --- | --- |
| Ubuntu 24.04, 26.04 | `librhvoice-dev`, `rhvoice-english` і `rhvoice-ukrainian` з компонента `multiverse`, який Ubuntu вмикає за замовчуванням |
| Debian 13 | ті самі пакети лише з компонента `non-free`, оскільки частина голосів забороняє комерційне використання чи зміни: допиши `non-free` до рядка `Components: main` файлу `/etc/apt/sources.list.d/debian.sources` (або до рядків `deb` файлу `/etc/apt/sources.list`) і виконай `sudo apt update` |
| Fedora, RHEL | пакета немає: скрипт `scripts/packages/install-redhat.sh` збирає випуск `1.18.4` з вихідних кодів разом з англійськими й українськими даними у префікс `/usr/local` |
| FreeBSD | порт `audio/rhvoice` (пакет `rhvoice`) з його голосами |

Без бібліотеки конфігурування завершується з повідомленням, яке їх називає, а власну інсталяцію бібліотеки знаходить змінна `CMAKE_PREFIX_PATH`, що вказує на її префікс. Модуль надає ціль `RHVoice::RHVoice`, тож прилінковуй її до своїх цільових об'єктів:

```
target_link_libraries(${PROJECT_BINARY_NAME} RHVoice::RHVoice)
```

| Змінна | Що вона містить |
| --- | --- |
| `PROJECT_TTS_TEXT` | текст, який промовляє програма, поки параметр командного рядка `--text` (або `-t`) не задає іншого, за замовчуванням `Hello, RHVoice! Insert your text here!` |
| `PROJECT_TTS_VOICE` | голос, яким промовляє програма, поки параметр командного рядка `--voice` (або `-s`) не задає іншого, за замовчуванням `Alan` |

### Ліцензія

Бібліотека RHVoice поширюється за ліцензією [LGPL-2.1-or-later](https://github.com/RHVoice/RHVoice/blob/master/doc/en/License.md) (збірка з необов'язковим рушієм MAGE підпадає під GPL-3.0-or-later, але наведені вище пакети і збірка гілки з вихідних кодів його не містять). Виконуваний файл лінкує спільну бібліотеку, тож поширюваний іншим виконуваний файл зберігає ліцензію вихідних кодів проекту, а сама бібліотека лишається замінною на її власних умовах: постачай її вихідні коди (або письмову пропозицію їх надати) разом з пакетом, який містить бібліотеку.

Голоси мають власні ліцензії: англійські Alan, Bdl, Clb і Slt та українські Anatol і Natalia вільні, українські Marianna і Volodymyr забороняють зміни (CC-BY-ND-4.0), а англійські Evgeniy-Eng і Lyubov ще й комерційне використання (CC-BY-NC-ND-4.0), через що Debian тримає RHVoice у своєму компоненті `non-free`. Перевір файли `/usr/share/doc/rhvoice-*/copyright`, перш ніж поширювати голос разом з проектом чи використовувати його комерційно.

### Голоси

RHVoice називає свої голоси іменами дикторів: голоси `Alan`, `Bdl`, `Clb`, `Slt`, `Evgeniy-Eng` і `Lyubov` пакета `rhvoice-english` говорять англійською, а голоси `Anatol`, `Natalia`, `Marianna` і `Volodymyr` пакета `rhvoice-ukrainian` - українською. Імена не зважають на регістр літер, а профіль з голосів різних мов (`Anatol+Alan`) перемикається на другий голос для слів його мови. Голоси цих пакетів промовляють з частотою 24 кГц, а директорія `/usr/share/RHVoice/voices` (`/usr/local/share/RHVoice/voices` у FreeBSD і збірці з вихідних кодів) перелічує встановлені голоси.

Найперший синтез створює рушій за шляхом до даних інсталяції, а змінна оточення `RHVOICE_DATA_PATH` вказує на іншу директорію з піддиректоріями `languages` і `voices`, змінна `RHVOICE_CONFIG_PATH` - на іншу директорію файлу `RHVoice.conf` (за замовчуванням `/etc/RHVoice`), який налаштовує темп, висоту і гучність голосів:

```
RHVOICE_DATA_PATH=/opt/rhvoice/share/RHVoice ./src/CppAppTemplate --voice Natalia --text "Привіт!"
```

### Складові

Директорія [src/RHVoice](/src/RHVoice) містить єдиний клас `rhvoice::RHVoiceController` - рушій мовлення гілки. Він реалізує інтерфейс `tts::ISpeechSynthesizer` незалежних від рушія вихідних кодів [src/TTS](/src/TTS):

| Клас | Що він робить |
| --- | --- |
| `tts::Speech` | зберігає синтезовані монофонічні 16-бітні відліки з їхньою частотою і тривалістю |
| `tts::ISpeechSynthesizer` | інтерфейс рушіїв мовлення: промовляє заданий текст заданим голосом у `tts::Speech`, а виклик `create` надає рушій, який лінкує збірка |
| `tts::WavWriter` | записує `tts::Speech` у 16-бітний монофонічний WAV-файл PCM |
| `tts::AudioPlayer` | відтворює `tts::Speech` типовим пристроєм відтворення звуку, дивись розділ [Вмикання відтворення звуку SDL2](/doc/sections/uk_UA/5-project-build/audio/5-68-enabling-the-SDL2-audio-playback.md) |
| `rhvoice::RHVoiceController` | синтезує мовлення засобами RHVoice |

Виклик `synthesize` контролера під час першого виклику створює рушій RHVoice, промовляє текст у кодуванні UTF-8 голосом у повідомлення рушія і збирає частоту та відліки, які рушій передає його зворотним викликам, повертаючи `std::nullopt` у разі невдачі: відсутності голосів, невідомого голосу (чи порожнього тексту) або самого синтезу, кожну з яких записано у журнал макросом `LOGE`. Знищення контролера видаляє рушій:

```
auto synthesizer = tts::ISpeechSynthesizer::create();

if (const auto speech = synthesizer->synthesize("Привіт, світе!", "Anatol")) {
  tts::WavWriter::create()->write(*speech, "speech.wav");
}
```

Метод `app::Application::run` з файлу [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) промовляє текст і голос командного рядка, записуючи мовлення у WAV-файл параметра `--output` (або `-o`) чи відтворюючи його в іншому разі. Він знає лише інтерфейси вихідних кодів `src/TTS`, тож інший рушій заступає RHVoice власною директорією `src/<рушій>`, яка визначає виклик `tts::ISpeechSynthesizer::create`, і своїм модулем CMake: саме так роблять гілки `appESpeakNG`, `appPiperTTS` і `appSherpaONNX`.

### Тести

Тест `UTEST_RHVoiceController` перевіряє контролер з імітацією викликів бібліотеки RHVoice, тож охоплює кожну невдачу бібліотеки, а тести `CTEST_RHVoiceController` і `CTEST_app` синтезують англійське й українське мовлення справжніми бібліотекою і голосами, перевіряють записані WAV-файли і відтворюють мовлення аудіодрайвером `dummy` бібліотеки SDL2, тож звукова карта не потрібна. Компонентні тести потребують встановлених голосів `Alan`, `Anatol` і `Natalia`.

### Пакування

Пакет DEB залежить від пакетів RHVoice і SDL2, які лінкує виконуваний файл, через інструмент `dpkg-shlibdeps`, а пакет `librhvoice5` приносить із собою ядро RHVoice та англійський голос. Flatpak збирає випуск `1.18.4` RHVoice з вихідних кодів разом з англійськими й українськими даними і голосами `Alan`, `Anatol` і `Natalia` у директорію `/app/share/RHVoice` і бере SDL2 середовища виконання freedesktop, а snap додає до себе RHVoice, англійські й українські голоси та SDL2 з архіву Ubuntu і вказує на ці дані змінними `RHVOICE_DATA_PATH` і `RHVOICE_CONFIG_PATH`. Flatpak відтворює мовлення через сокет PulseAudio і записує файли параметра `--output` у домашню директорію, а snap відтворює його через інтерфейс `audio-playback`.
