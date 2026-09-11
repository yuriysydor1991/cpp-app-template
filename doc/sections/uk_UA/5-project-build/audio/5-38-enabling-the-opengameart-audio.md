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

Дана гілка навмисно не містить жодного звукового рушія, точно так само, як гілка `appFontAwesome` не містить жодного інструментарію графічного інтерфейсу: вона відповідає за те, щоб зробити ресурси доступними, і ні за що більше. Достатньо передати `filePath` звуку (або його шлях у системі ресурсів) тому рушію, який програма вже використовує — SDL, SFML, OpenAL чи miniaudio — і гілка поєднується з будь-яким з них.
