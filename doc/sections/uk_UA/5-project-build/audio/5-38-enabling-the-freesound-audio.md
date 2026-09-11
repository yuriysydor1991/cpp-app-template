## Вмикання звукових ефектів Freesound

Набори звукових ефектів [Freesound](https://freesound.nl/assets) під ліцензією CC0 стають доступними проекту за допомогою змінної CMake `ENABLE_FREESOUND_AUDIO`, яка на даній гілці типово має значення `ON`:

```
# Всередині кореневої директорії з вихідними кодами

cmake -S . -B build -DENABLE_FREESOUND_AUDIO=ON
```

Механізм вмикання завантажує кожен налаштований набір, розпаковує його у директорію ресурсів дерева побудови, зберігає його **недоторканим** і доступним як з CMake, так і з коду C++, а рішення про те, що саме потрапить до виконуваного файлу програми, залишає за розробником. Жодного браузера, жодного ритуалу «зберегти як» для кожного окремого звуку і жодного доступу до мережі під час роботи програми.

Freesound публікує набори на умовах [CC0](https://creativecommons.org/publicdomain/zero/1.0/), тому вони не потребують зазначення авторства і залишаються придатними для комерційного використання. **Набори ніколи не потрапляють до даного репозиторію**: вони завантажуються під час налаштування, точно так само, як набір іконок Font Awesome на гілці `appFontAwesome`.

### Змінні механізму вмикання

Модуль `cmake/enablers/audio/template-project-freesound-audio-enabler.cmake` оголошує наступне:

| Змінна | Типове значення | Призначення |
| --- | --- | --- |
| `ENABLE_FREESOUND_AUDIO` | `ON` | вмикає усю інтеграцію |
| `TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST` | `misc/freesound-categories.txt` | маніфест, що називає кожен набір разом з адресою його архіву і його ліцензією |
| `TEMPLATE_APP_FREESOUND_AUDIO_DIR` | порожнє | вже наявна директорія з наборами, яку слід використати замість завантаження |
| `FREESOUND_AUDIO_EXTENSIONS` | `ogg;wav;mp3` | розширення звукових файлів, які слід обрати з наборів |
| `FREESOUND_AUDIO_QT_RESOURCE_PREFIX` | `/sounds` | префікс згенерованих маніфестів `.qrc` |
| `FREESOUND_AUDIO_GRESOURCE_PREFIX` | `/ua/org/kytok/template/<binary>/sounds` | префікс згенерованих маніфестів `.gresource.xml` |
| `FREESOUND_AUDIO_GENERATE_FULL_MANIFESTS` | `ON` | генерує маніфести, що містять усі доступні звуки |

### Маніфест звуків

Freesound публікує свої матеріали під ліцензіями CC0, CC-BY та CC-BY-NC водночас, **по одній ліцензії на звук**, а не одній на всю базу, тому дана гілка фіксує походження кожного окремого файлу. Маніфест `misc/freesound-sounds.txt` є єдиним місцем, що називає, **який** звук використовується, **звідки** він походить і **під якою** ліцензією опублікований. Кожен рядок має вигляд

```
<категорія>/<файл>|<адреса завантаження>|<ліцензія>
```

де `#` починає коментар, а порожні рядки пропускаються:

```
interface/click.ogg|https://freesound.org/people/<автор>/sounds/<id>/download/<файл>|CC0-1.0
interface/notification.ogg|https://freesound.org/people/<автор>/sounds/<id>/download/<файл>|CC-BY-4.0
```

Категорія — це лише піддиректорія, до якої завантажується файл, і перша частина його псевдоніма, тому групування є власним рішенням розробника, а не чимось, що нав'язує сайт.

**Маніфест навмисно постачається порожнім, і етап налаштування зупиняється, доки його не буде заповнено**: вибір потрібних матеріалів — і читання ліцензії кожного з них на [freesound.org](https://freesound.org) — є рішенням, яке дана гілка відмовляється приймати замість розробника. Звуковий файл, що лежить у директорії звуків без запису у маніфесті, також відхиляється, тому походження не може мовчки загубитись.

API Freesound потребує токена облікового запису, тому записана адреса є тією адресою, за якою звук дійсно доступний, а не викликом API, що його могла б зробити сама побудова.

Ліцензія і джерело потрапляють аж до виконуваного файлу, тому код відповідає за обидва:

```cpp
auto click = sounds->find("interface", "click.ogg");

click->license();    // "CC0-1.0"
click->sourceUrl();  // "https://freesound.org/people/<автор>/sounds/<id>/..."
```

Саме це робить можливим зазначення авторства для звуку під ліцензією CC-BY, а скрипт `misc/scripts/fetch-freesound-audio.sh` записує ту саму таблицю до файлу `LICENSES.md` поруч із завантаженими файлами, тому директорія несе своє походження навіть після того, як покине дерево побудови.

### Завантаження звуків вручну

Хост, етап налаштування якого не має власного доступу до мережі, директорія наборів, спільна для декількох дерев побудови, і бажання тримати завантажене поза деревом побудови — усе це обслуговує скрипт `misc/scripts/fetch-freesound-audio.sh`:

```
misc/scripts/fetch-freesound-audio.sh ~/freesound-audio

cmake -S . -B build -DTEMPLATE_APP_FREESOUND_AUDIO_DIR=~/freesound-audio
```

Скрипт приймає директорію призначення як свій єдиний аргумент, зважає на змінні середовища `FREESOUND_AUDIO_PACKS` та `FREESOUND_AUDIO_URL_TEMPLATE`, завантажує за допомогою `curl` або `wget` (залежно від того, що доступне) і не чіпає вже розпакований набір.

### Доступ до звуків з коду C++

Механізм вмикання генерує покажчик звуків з тих самих наборів, що використовуються, тому увесь набір доступний без сканування директорій під час роботи і без жодної назви звуку, написаної у вихідних кодах вручну:

```cpp
#include "src/freesoundaudio/sounds/FreesoundSounds.h"

auto sounds = freesoundaudio::FreesoundSounds::create();

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

Кожен набір залишається недоторканим всередині директорії наборів, і лише ті звуки, які програма дійсно запитує, потрапляють до її виконуваного файлу. Обрати їх можна за допомогою функції `template_project_freesound_audio_write_qrc` (Qt) або `template_project_freesound_audio_write_gresource` (Gtkmm), після чого записаний маніфест передається компілятору ресурсів того інструментарію, що використовується:

```cmake
template_project_freesound_audio_write_qrc(
  "${CMAKE_CURRENT_BINARY_DIR}/freesound-audio.qrc"
  SOUNDS
    interface-sounds/Audio/click_001.ogg
    interface-sounds/Audio/confirmation_001.ogg
)
```

Запит без `PACKS` і без `SOUNDS` обирає увесь доступний набір. Маніфести, що містять усе, генеруються вже зараз, у файлах `generated/freesoundaudio/freesound-audio-all.qrc` та `generated/freesoundaudio/freesound-audio-all.gresource.xml` директорії побудови.

Всередині маніфестів звуки зберігають свої псевдоніми виду `<набір>/<шлях>`, тому класи `FreesoundQtResourcePath` та `FreesoundGResourcePath` розв'язують їх під час роботи:

```cpp
#include "src/freesoundaudio/resources/FreesoundQtResourcePath.h"

auto qtPath = freesoundaudio::FreesoundQtResourcePath::create();

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

Проте те, які саме це формати, є власною справою рушія — так само, як і питання, чи був рушій узагалі вбудований. **Ані те, ані інше ніколи не сягає коду, що викликає**: клас `FreesoundSoundsController` тримає набір і програвач разом і відповідає на обидва питання самостійно.

```cpp
#include "src/freesoundaudio/controller/FreesoundSoundsController.h"

auto controller = freesoundaudio::FreesoundSoundsController::create(sounds);

auto sound = controller->draw();   // звук, який рушій дійсно декодує
                                   // (будь-який звук набору, якщо жодного такого немає)

if (controller->playable()) {      // чи є рушій узагалі
  controller->play(sound);         // повертається, щойно звук відтворено
}
```

Контролер запитує у програвача, які розширення той підтримує, замість того щоб називати якесь із них, тому рушій, доданий, замінений чи прибраний згодом, не змінює нічого у наведеному вище коді.

Вимикання `ENABLE_SDL2_AUDIO` прибирає програвач і залишає решту підсистеми — покажчик, псевдоніми і маніфести ресурсів — недоторканою. Ті самі вихідні коди й надалі компілюються: реалізація `FreesoundSoundPlayerFactory::create`, яку обирає побудова, відповідає або програвачем, або нульовим вказівником, тому **жодне місце виклику не містить препроцесорного розгалуження**.

### Рівні під сподом

`FreesoundSdlSoundPlayer` — це і є рушій SDL2, і він залишається доступним для програми, яка бажає керувати ним напряму:

```cpp
#include "src/freesoundaudio/player/FreesoundSdlSoundPlayer.h"

auto player = freesoundaudio::FreesoundSdlSoundPlayer::create();

player->supports("wav");  // true
player->supports("ogg");  // false, це територія SDL_mixer
```

### Випадковий вибір звуку

Демонстрація, що відтворює на кожному запуску один і той самий клац, доводить небагато, тому `FreesoundRandomSound` витягує звук з усього доступного набору. Зерно можна задати, і саме це дозволяє тесту попросити повторюваний вибір:

```cpp
#include "src/freesoundaudio/player/FreesoundRandomSound.h"

freesoundaudio::FreesoundRandomSound drawn;

auto any = drawn.pick(sounds);          // будь-який звук взагалі
auto wave = drawn.pick(sounds, "wav");  // лише те, що програвач дійсно декодує
```

### Демонстрація

Метод `Application::run` даної гілки поєднує усі три складові: повідомляє, скільки звуків містять налаштовані набори, витягує придатний для відтворення, друкує шлях до його файлу і обидва шляхи у системах ресурсів, та відтворює його:

```
INF : The Freesound categories carry 6 sounds at /.../resources/freesound-audio
INF : The drawn impacts/thud.wav sound file: /.../thud.wav
INF : ... published under CC0-1.0 at https://freesound.org/people/<author>/sounds/<id>/...
INF : ... embedded into the Qt resources: :/sounds/impacts/thud.wav
INF : ... embedded into the GResource ones: /ua/org/kytok/template/CppAppTemplate/sounds/impacts/thud.wav
INF : Playing the impacts/thud.wav sound ...
```

Якщо набори порожні або серед них немає звуку у форматі, який декодує програвач, демонстрація повідомляє про це і завершується коректно, а не з помилкою.
