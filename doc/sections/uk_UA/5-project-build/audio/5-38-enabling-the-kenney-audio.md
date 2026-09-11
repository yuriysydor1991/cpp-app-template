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
| `TEMPLATE_APP_KENNEY_AUDIO_URL_TEMPLATE` | адреса першоджерела | адреса завантаження окремого набору, де `<pack>` заміняється назвою набору |
| `TEMPLATE_APP_KENNEY_AUDIO_DIR` | порожнє | вже наявна директорія з наборами, яку слід використати замість завантаження |
| `KENNEY_AUDIO_EXTENSIONS` | `ogg;wav;mp3` | розширення звукових файлів, які слід обрати з наборів |
| `KENNEY_AUDIO_QT_RESOURCE_PREFIX` | `/sounds` | префікс згенерованих маніфестів `.qrc` |
| `KENNEY_AUDIO_GRESOURCE_PREFIX` | `/ua/org/kytok/template/<binary>/sounds` | префікс згенерованих маніфестів `.gresource.xml` |
| `KENNEY_AUDIO_GENERATE_FULL_MANIFESTS` | `ON` | генерує маніфести, що містять усі доступні звуки |

**Перед першим завантаженням необхідно перевірити значення `TEMPLATE_APP_KENNEY_AUDIO_URL_TEMPLATE` за адресою [kenney.nl](https://kenney.nl/assets)**: архіви наборів є звичайними файлами для завантаження, а не версіонованим API, тому їхні адреси залишаються справою сайту першоджерела і можуть змінюватись.

### Завантаження наборів вручну

Хост, етап налаштування якого не має власного доступу до мережі, директорія наборів, спільна для декількох дерев побудови, і бажання тримати завантажене поза деревом побудови — усе це обслуговує скрипт `misc/scripts/fetch-kenney-audio.sh`:

```
misc/scripts/fetch-kenney-audio.sh ~/kenney-audio

cmake -S . -B build -DTEMPLATE_APP_KENNEY_AUDIO_DIR=~/kenney-audio
```

Скрипт приймає директорію призначення як свій єдиний аргумент, зважає на змінні середовища `KENNEY_AUDIO_PACKS` та `KENNEY_AUDIO_URL_TEMPLATE`, завантажує за допомогою `curl` або `wget` (залежно від того, що доступне) і не чіпає вже розпакований набір.

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

Дана гілка навмисно не містить жодного звукового рушія, точно так само, як гілка `appFontAwesome` не містить жодного інструментарію графічного інтерфейсу: вона відповідає за те, щоб зробити ресурси доступними, і ні за що більше. Достатньо передати `filePath` звуку (або його шлях у системі ресурсів) тому рушію, який програма вже використовує — SDL, SFML, OpenAL чи miniaudio — і гілка поєднується з будь-яким з них.
