## Вмикання звукових ефектів OpenGameArt

Набори звукових ефектів [OpenGameArt](https://opengameart.nl/assets) під ліцензією CC0 стають доступними проекту за допомогою змінної CMake `ENABLE_OPENGAMEART_AUDIO`, яка на даній гілці типово має значення `ON`:

```
# Всередині кореневої директорії з вихідними кодами

cmake -S . -B build -DENABLE_OPENGAMEART_AUDIO=ON
```

Механізм вмикання завантажує кожен налаштований набір, розпаковує його у директорію ресурсів дерева побудови, зберігає його **недоторканим** і доступним як з CMake, так і з коду C++, а рішення про те, що саме потрапить до виконуваного файлу програми, залишає за розробником. Жодного браузера, жодного ритуалу «зберегти як» для кожного окремого звуку і жодного доступу до мережі під час роботи програми.

OpenGameArt публікує набори на умовах [CC0](https://creativecommons.org/publicdomain/zero/1.0/), тому вони не потребують зазначення авторства і залишаються придатними для комерційного використання. **Набори ніколи не потрапляють до даного репозиторію**: вони завантажуються під час налаштування, точно так само, як набір іконок Font Awesome на гілці `appFontAwesome`.

### Змінні механізму вмикання

Модуль `cmake/enablers/audio/template-project-opengameart-audio-enabler.cmake` оголошує наступне:

| Змінна | Типове значення | Призначення |
| --- | --- | --- |
| `ENABLE_OPENGAMEART_AUDIO` | `ON` | вмикає усю інтеграцію |
| `TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST` | `misc/opengameart-packs.txt` | маніфест, що називає кожен набір разом з адресою його архіву і його ліцензією |
| `TEMPLATE_APP_OPENGAMEART_AUDIO_DIR` | порожнє | вже наявна директорія з наборами, яку слід використати замість завантаження |
| `OPENGAMEART_AUDIO_EXTENSIONS` | `ogg;wav;mp3` | розширення звукових файлів, які слід обрати з наборів |
| `OPENGAMEART_AUDIO_QT_RESOURCE_PREFIX` | `/sounds` | префікс згенерованих маніфестів `.qrc` |
| `OPENGAMEART_AUDIO_GRESOURCE_PREFIX` | `/ua/org/kytok/template/<binary>/sounds` | префікс згенерованих маніфестів `.gresource.xml` |
| `OPENGAMEART_AUDIO_GENERATE_FULL_MANIFESTS` | `ON` | генерує маніфести, що містять усі доступні звуки |

### Маніфест наборів

OpenGameArt розміщує свої матеріали під декількома різними ліцензіями, тому дана гілка не називає жодного власного набору: маніфест `misc/opengameart-packs.txt` є єдиним місцем, що фіксує, **який** набір використовується, **звідки** він походить і **під якою** ліцензією опублікований. Кожен рядок має вигляд

```
<набір>|<адреса архіву>|<ліцензія>
```

де `#` починає коментар, а порожні рядки пропускаються:

```
cc0-interface-sfx|https://opengameart.org/sites/default/files/<архів>.zip|CC0-1.0
cc0-footsteps|https://opengameart.org/sites/default/files/<архів>.zip|CC0-1.0
```

**Маніфест навмисно постачається порожнім, і етап налаштування зупиняється, доки його не буде заповнено**: вибір потрібних матеріалів — і читання ліцензії кожного з них на [opengameart.org](https://opengameart.org) — є рішенням, яке дана гілка відмовляється приймати замість розробника. Набір без записаної ліцензії відхиляється, а не вважається мовчазно таким, що має ліцензію CC0.

Записана ліцензія потрапляє аж до виконуваного файлу, тому код також відповідає за неї:

```cpp
auto pack = packs->find("cc0-interface-sfx");

pack->license();  // "CC0-1.0"
```

### Завантаження наборів вручну

Хост, етап налаштування якого не має власного доступу до мережі, директорія наборів, спільна для декількох дерев побудови, і бажання тримати завантажене поза деревом побудови — усе це обслуговує скрипт `misc/scripts/fetch-opengameart-audio.sh`:

```
misc/scripts/fetch-opengameart-audio.sh ~/opengameart-audio

cmake -S . -B build -DTEMPLATE_APP_OPENGAMEART_AUDIO_DIR=~/opengameart-audio
```

Скрипт приймає директорію призначення як свій єдиний аргумент, зважає на змінні середовища `OPENGAMEART_AUDIO_PACKS` та `OPENGAMEART_AUDIO_URL_TEMPLATE`, завантажує за допомогою `curl` або `wget` (залежно від того, що доступне) і не чіпає вже розпакований набір.

### Доступ до звуків з коду C++

Механізм вмикання генерує покажчик звуків з тих самих наборів, що використовуються, тому увесь набір доступний без сканування директорій під час роботи і без жодної назви звуку, написаної у вихідних кодах вручну:

```cpp
#include "src/opengameartaudio/sounds/OpenGameArtSounds.h"

auto sounds = opengameartaudio::OpenGameArtSounds::create();

// кожен звук кожного налаштованого набору
for (const auto& sound : sounds->all()) {
  sound->name();       // "click_001"
  sound->alias();      // "interface-sounds/Audio/click_001.ogg"
  sound->filePath();   // абсолютний шлях всередині директорії наборів
}

// звуки одного набору
auto interfaceSounds = sounds->ofPack("interface-sounds");

// окремий звук за його набором і відносним шляхом
auto click = sounds->find("interface-sounds", "Audio/click_001.ogg");

// кожен звук, назва якого містить задану частину
auto clicks = sounds->search("click");
```

### Вбудовування звуків до виконуваного файлу

Кожен набір залишається недоторканим всередині директорії наборів, і лише ті звуки, які програма дійсно запитує, потрапляють до її виконуваного файлу. Обрати їх можна за допомогою функції `template_project_opengameart_audio_write_qrc` (Qt) або `template_project_opengameart_audio_write_gresource` (Gtkmm), після чого записаний маніфест передається компілятору ресурсів того інструментарію, що використовується:

```cmake
template_project_opengameart_audio_write_qrc(
  "${CMAKE_CURRENT_BINARY_DIR}/opengameart-audio.qrc"
  SOUNDS
    interface-sounds/Audio/click_001.ogg
    interface-sounds/Audio/confirmation_001.ogg
)
```

Запит без `PACKS` і без `SOUNDS` обирає увесь доступний набір. Маніфести, що містять усе, генеруються вже зараз, у файлах `generated/opengameartaudio/opengameart-audio-all.qrc` та `generated/opengameartaudio/opengameart-audio-all.gresource.xml` директорії побудови.

Всередині маніфестів звуки зберігають свої псевдоніми виду `<набір>/<шлях>`, тому класи `OpenGameArtQtResourcePath` та `OpenGameArtGResourcePath` розв'язують їх під час роботи:

```cpp
#include "src/opengameartaudio/resources/OpenGameArtQtResourcePath.h"

auto qtPath = opengameartaudio::OpenGameArtQtResourcePath::create();

qtPath->of(click);     // ":/sounds/interface-sounds/Audio/click_001.ogg"
qtPath->uriOf(click);  // "qrc:/sounds/interface-sounds/Audio/click_001.ogg"
```

Прапорець `COMPRESSED` функції запису GResource залишається корисним виключно для нестиснених членів набору у форматі `.wav`: файли `.ogg` та `.mp3` вже містять стиснений потік, тому повторне стиснення їх засобами GLib коштує часу побудови і не дає нічого.

### Відтворення звуків

Гілка постачає програвач, тому набори не лише доступні, а й чутні. Його побудовано на **звуковій підсистемі SDL2** та **декодерах SDL_mixer** і вмикається він змінною CMake `ENABLE_SDL2_AUDIO`, яка типово має значення `ON`:

| Змінна | Типове значення | Призначення |
| --- | --- | --- |
| `ENABLE_SDL2_AUDIO` | `ON` | будує програвач звуку на основі SDL2 та SDL_mixer |
| `TEMPLATE_APP_SDL2_GIT` | репозиторій першоджерела | git-репозиторій вихідних кодів SDL2 |
| `TEMPLATE_APP_SDL2_GIT_TAG` | `release-2.32.10` | версія SDL2, на якій слід зафіксуватись |
| `TEMPLATE_APP_SDL2_MIXER_GIT` | репозиторій першоджерела | git-репозиторій вихідних кодів SDL_mixer |
| `TEMPLATE_APP_SDL2_MIXER_GIT_TAG` | `release-2.8.1` | версія SDL_mixer, на якій слід зафіксуватись |

Модуль `cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake` спочатку шукає системні бібліотеки і лише потім вдається до побудови через FetchContent — так само, як це робить кожен інший механізм вмикання сторонніх бібліотек у даному проекті. Використовується виключно звукова підсистема SDL2: жодного вікна, жодного рендерера і жодного OpenGL.

**Сам по собі SDL2 декодує лише файли RIFF/WAVE**, тоді як OpenGameArt розміщує свої матеріали і у форматі `.ogg`, і у форматі `.mp3`, тому саме декодери бібліотеки-супутника `SDL_mixer` роблять їх чутними взагалі. Беруться лише ті декодери, які SDL_mixer містить у власних вихідних кодах, — stb_vorbis для `.ogg`, minimp3 для `.mp3` та drflac для `.flac`, — тому побудова через FetchContent не потребує жодної сторонньої бібліотеки, а декодери Opus, MOD, MIDI та WavPack, кожен з яких вимагає встановленої у системі бібліотеки, вимкнено, щоб не завалювати конфігурування на вузлі, де такої немає.

Проте те, які саме це формати, є власною справою рушія — так само, як і питання, чи був рушій узагалі вбудований. **Ані те, ані інше ніколи не сягає коду, що викликає**: клас `OpenGameArtSoundsController` тримає набір і програвач разом і відповідає на обидва питання самостійно.

```cpp
#include "src/opengameartaudio/controller/OpenGameArtSoundsController.h"

auto controller = opengameartaudio::OpenGameArtSoundsController::create(sounds);

auto sound = controller->draw();   // звук, який рушій дійсно декодує
                                   // (будь-який звук набору, якщо жодного такого немає)

if (controller->playable()) {      // чи є рушій узагалі
  controller->play(sound);         // повертається, щойно звук відтворено
}
```

Контролер запитує у програвача, які розширення той підтримує, замість того щоб називати якесь із них, тому рушій, доданий, замінений чи прибраний згодом, не змінює нічого у наведеному вище коді.

Вимикання `ENABLE_SDL2_AUDIO` прибирає програвач і залишає решту підсистеми — покажчик, псевдоніми і маніфести ресурсів — недоторканою. Ті самі вихідні коди й надалі компілюються: реалізація `OpenGameArtSoundPlayerFactory::create`, яку обирає побудова, відповідає або програвачем, або нульовим вказівником, тому **жодне місце виклику не містить препроцесорного розгалуження**.

### Рівні під сподом

`OpenGameArtSdlMixerSoundPlayer` — це і є рушій SDL2, і він залишається доступним для програми, яка бажає керувати ним напряму:

```cpp
#include "src/opengameartaudio/player/OpenGameArtSdlMixerSoundPlayer.h"

auto player = opengameartaudio::OpenGameArtSdlMixerSoundPlayer::create();

player->supports("ogg");  // true
player->supports("mid");  // false, декодера MIDI не піднято
```

Розширення, за які програвач відповідає, — це ті, які дійсно підняв виклик `Mix_Init`, а не написаний руками перелік, тому встановлений у системі SDL_mixer з більшою кількістю декодерів, ніж має побудова через FetchContent, використовується на всі свої можливості.

### Випадковий вибір звуку

Демонстрація, що відтворює на кожному запуску один і той самий клац, доводить небагато, тому `OpenGameArtRandomSound` витягує звук з усього доступного набору. Зерно можна задати, і саме це дозволяє тесту попросити повторюваний вибір:

```cpp
#include "src/opengameartaudio/player/OpenGameArtRandomSound.h"

opengameartaudio::OpenGameArtRandomSound drawn;

auto any = drawn.pick(sounds);             // будь-який звук взагалі
auto vorbis = drawn.pick(sounds, "ogg");  // лише те, що програвач дійсно декодує
```

### Демонстрація

Метод `Application::run` даної гілки поєднує усі три складові: повідомляє, скільки звуків містять налаштовані набори, витягує придатний для відтворення, друкує шлях до його файлу і обидва шляхи у системах ресурсів, та відтворює його:

```
INF : The OpenGameArt packs carry 8 sounds at /.../resources/opengameart-audio
INF : The drawn cc0-footsteps/Audio/step_grass_01.wav sound file: /.../step_grass_01.wav
INF : ... published under: CC0-1.0
INF : ... embedded into the Qt resources: :/sounds/cc0-footsteps/Audio/step_grass_01.wav
INF : ... embedded into the GResource ones: /ua/org/kytok/template/CppAppTemplate/sounds/cc0-footsteps/Audio/step_grass_01.wav
INF : Playing the cc0-footsteps/Audio/step_grass_01.wav sound ...
```

Якщо набори порожні або серед них немає звуку у форматі, який декодує програвач, демонстрація повідомляє про це і завершується коректно, а не з помилкою.
