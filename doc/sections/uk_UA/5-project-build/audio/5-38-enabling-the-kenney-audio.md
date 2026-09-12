## Вмикання звукових ефектів Kenney

Набори звукових ефектів [Kenney](https://kenney.nl/assets) під ліцензією CC0 стають доступними проекту за допомогою змінної CMake `ENABLE_KENNEY_AUDIO`, яка на даній гілці типово має значення `ON`:

```
# Всередині кореневої директорії з вихідними кодами

cmake -S . -B build -DENABLE_KENNEY_AUDIO=ON
```

Механізм вмикання завантажує кожен налаштований набір, розпаковує його у директорію ресурсів дерева побудови, зберігає його **недоторканим** і доступним як з CMake, так і з коду C++, а рішення про те, що саме потрапить до виконуваного файлу програми, залишає за розробником. Жодного браузера, жодного ритуалу «зберегти як» для кожного окремого звуку і жодного доступу до мережі під час роботи програми.

Kenney публікує набори на умовах [CC0](https://creativecommons.org/publicdomain/zero/1.0/), тому вони не потребують зазначення авторства і залишаються придатними для комерційного використання. **Набори ніколи не потрапляють до даного репозиторію**: вони завантажуються під час налаштування, точно так само, як набір іконок Font Awesome на гілці `appFontAwesome`.

### Змінні механізму вмикання

Модуль `cmake/enablers/audio/template-project-kenney-audio-enabler.cmake` оголошує наступне:

| Змінна | Типове значення | Призначення |
| --- | --- | --- |
| `ENABLE_KENNEY_AUDIO` | `ON` | вмикає усю інтеграцію |
| `KENNEY_AUDIO_PACKS` | `interface-sounds;impact-sounds;digital-audio;ui-audio` | набори, які необхідно зробити доступними |
| `TEMPLATE_APP_KENNEY_AUDIO_PAGE_TEMPLATE` | сторінка першоджерела | сторінка окремого набору, з якої зчитується адреса архіву, де `<pack>` заміняється назвою набору |
| `TEMPLATE_APP_KENNEY_AUDIO_DIR` | порожнє | вже наявна директорія з наборами, яку слід використати замість завантаження |
| `KENNEY_AUDIO_EXTENSIONS` | `ogg;wav;mp3` | розширення звукових файлів, які слід обрати з наборів |
| `KENNEY_AUDIO_QT_RESOURCE_PREFIX` | `/sounds` | префікс згенерованих маніфестів `.qrc` |
| `KENNEY_AUDIO_GRESOURCE_PREFIX` | `/ua/org/kytok/template/<binary>/sounds` | префікс згенерованих маніфестів `.gresource.xml` |
| `KENNEY_AUDIO_GENERATE_FULL_MANIFESTS` | `ON` | генерує маніфести, що містять усі доступні звуки |

**Адреса архіву зчитується зі сторінки самого набору, а не записується тут**: вона містить хеш вмісту, який сайт перегенеровує щоразу, коли набір оновлюється, тому написана руками адреса застаріває замість того, щоб хоч щось завантажити, тоді як сторінка, яка її називає, залишається доступною за назвою набору.

### Завантаження наборів вручну

Хост, етап налаштування якого не має власного доступу до мережі, директорія наборів, спільна для декількох дерев побудови, і бажання тримати завантажене поза деревом побудови — усе це обслуговує скрипт `misc/scripts/fetch-kenney-audio.sh`:

```
misc/scripts/fetch-kenney-audio.sh ~/kenney-audio

cmake -S . -B build -DTEMPLATE_APP_KENNEY_AUDIO_DIR=~/kenney-audio
```

Скрипт приймає директорію призначення як свій єдиний аргумент, зважає на змінні середовища `KENNEY_AUDIO_PACKS` та `KENNEY_AUDIO_PAGE_TEMPLATE`, завантажує за допомогою `curl` або `wget` (залежно від того, що доступне) і не чіпає вже розпакований набір.

### Доступ до звуків з коду C++

Механізм вмикання генерує покажчик звуків з тих самих наборів, що використовуються, тому увесь набір доступний без сканування директорій під час роботи і без жодної назви звуку, написаної у вихідних кодах вручну:

```cpp
#include "src/kenneyaudio/sounds/KenneySounds.h"

auto sounds = kenneyaudio::KenneySounds::create();

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

Кожен набір залишається недоторканим всередині директорії наборів, і лише ті звуки, які програма дійсно запитує, потрапляють до її виконуваного файлу. Обрати їх можна за допомогою функції `template_project_kenney_audio_write_qrc` (Qt) або `template_project_kenney_audio_write_gresource` (Gtkmm), після чого записаний маніфест передається компілятору ресурсів того інструментарію, що використовується:

```cmake
template_project_kenney_audio_write_qrc(
  "${CMAKE_CURRENT_BINARY_DIR}/kenney-audio.qrc"
  SOUNDS
    interface-sounds/Audio/click_001.ogg
    interface-sounds/Audio/confirmation_001.ogg
)
```

Запит без `PACKS` і без `SOUNDS` обирає увесь доступний набір. Маніфести, що містять усе, генеруються вже зараз, у файлах `generated/kenneyaudio/kenney-audio-all.qrc` та `generated/kenneyaudio/kenney-audio-all.gresource.xml` директорії побудови.

Всередині маніфестів звуки зберігають свої псевдоніми виду `<набір>/<шлях>`, тому класи `KenneyQtResourcePath` та `KenneyGResourcePath` розв'язують їх під час роботи:

```cpp
#include "src/kenneyaudio/resources/KenneyQtResourcePath.h"

auto qtPath = kenneyaudio::KenneyQtResourcePath::create();

qtPath->of(click);     // ":/sounds/interface-sounds/Audio/click_001.ogg"
qtPath->uriOf(click);  // "qrc:/sounds/interface-sounds/Audio/click_001.ogg"
```

Прапорець `COMPRESSED` функції запису GResource залишається корисним виключно для нестиснених членів набору у форматі `.wav`: файли `.ogg` та `.mp3` вже містять стиснений потік, тому повторне стиснення їх засобами GLib коштує часу побудови і не дає нічого.

### Відтворення звуків

Гілка постачає програвач, тому набори не лише доступні, а й чутні. Його побудовано на **звуковій підсистемі SDL2** і вмикається він змінною CMake `ENABLE_SDL2_AUDIO`, яка типово має значення `ON`:

| Змінна | Типове значення | Призначення |
| --- | --- | --- |
| `ENABLE_SDL2_AUDIO` | `ON` | будує програвач звуку на основі SDL2 |
| `TEMPLATE_APP_SDL2_GIT` | репозиторій першоджерела | git-репозиторій вихідних кодів SDL2 |
| `TEMPLATE_APP_SDL2_GIT_TAG` | `release-2.32.10` | версія SDL2, на якій слід зафіксуватись |

Модуль `cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake` спочатку шукає SDL2 у системі і лише потім вдається до побудови через FetchContent — так само, як це робить кожен інший механізм вмикання сторонніх бібліотек у даному проекті. Використовується виключно звукова підсистема SDL2: жодного вікна, жодного рендерера і жодного OpenGL.

**Сам по собі SDL2 декодує лише файли RIFF/WAVE.** Стиснені формати є справою окремої бібліотеки `SDL_mixer`, тому звук `.ogg` чи `.mp3` відхиляється з повідомленням, яке його називає, а не передається до звукового пристрою як шум.

Проте те, які саме це формати, є власною справою рушія — так само, як і питання, чи був рушій узагалі вбудований. **Ані те, ані інше ніколи не сягає коду, що викликає**: клас `KenneySoundsController` тримає набір і програвач разом і відповідає на обидва питання самостійно.

```cpp
#include "src/kenneyaudio/controller/KenneySoundsController.h"

auto controller = kenneyaudio::KenneySoundsController::create(sounds);

auto sound = controller->draw();   // звук, який рушій дійсно декодує
                                   // (будь-який звук набору, якщо жодного такого немає)

if (controller->playable()) {      // чи є рушій узагалі
  controller->play(sound);         // повертається, щойно звук відтворено
}
```

Контролер запитує у програвача, які розширення той підтримує, замість того щоб називати якесь із них, тому рушій, доданий, замінений чи прибраний згодом, не змінює нічого у наведеному вище коді.

Вимикання `ENABLE_SDL2_AUDIO` прибирає програвач і залишає решту підсистеми — покажчик, псевдоніми і маніфести ресурсів — недоторканою. Ті самі вихідні коди й надалі компілюються: реалізація `KenneySoundPlayerFactory::create`, яку обирає побудова, відповідає або програвачем, або нульовим вказівником, тому **жодне місце виклику не містить препроцесорного розгалуження**.

### Рівні під сподом

`KenneySdlSoundPlayer` — це і є рушій SDL2, і він залишається доступним для програми, яка бажає керувати ним напряму:

```cpp
#include "src/kenneyaudio/player/KenneySdlSoundPlayer.h"

auto player = kenneyaudio::KenneySdlSoundPlayer::create();

player->supports("wav");  // true
player->supports("ogg");  // false, це територія SDL_mixer
```

### Випадковий вибір звуку

Демонстрація, що відтворює на кожному запуску один і той самий клац, доводить небагато, тому `KenneyRandomSound` витягує звук з усього доступного набору. Зерно можна задати, і саме це дозволяє тесту попросити повторюваний вибір:

```cpp
#include "src/kenneyaudio/player/KenneyRandomSound.h"

kenneyaudio::KenneyRandomSound drawn;

auto any = drawn.pick(sounds);          // будь-який звук взагалі
auto wave = drawn.pick(sounds, "wav");  // лише те, що програвач дійсно декодує
```

### Демонстрація

Метод `Application::run` даної гілки поєднує усі три складові: повідомляє, скільки звуків містять налаштовані набори, витягує придатний для відтворення, друкує шлях до його файлу і обидва шляхи у системах ресурсів, та відтворює його:

```
INF : The Kenney packs carry 12 sounds at /.../resources/kenney-audio
INF : The drawn interface-sounds/Audio/confirmation_001.wav sound file: /.../confirmation_001.wav
INF : ... embedded into the Qt resources: :/sounds/interface-sounds/Audio/confirmation_001.wav
INF : ... embedded into the GResource ones: /ua/org/kytok/template/CppAppTemplate/sounds/interface-sounds/Audio/confirmation_001.wav
INF : Playing the interface-sounds/Audio/confirmation_001.wav sound ...
```

Якщо набори порожні або серед них немає звуку у форматі, який декодує програвач, демонстрація повідомляє про це і завершується коректно, а не з помилкою.
