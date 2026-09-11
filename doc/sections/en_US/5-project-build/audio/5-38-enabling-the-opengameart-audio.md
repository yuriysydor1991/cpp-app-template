## Enabling the OpenGameArt sound effects

The [OpenGameArt](https://opengameart.nl/assets) CC0 sound effect packs are made available to the project by the `ENABLE_OPENGAMEART_AUDIO` CMake variable, which is `ON` by default on this branch:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_OPENGAMEART_AUDIO=ON
```

The enabler downloads every configured pack, unpacks it into a resources directory of the build tree, keeps it **intact** and reachable both from CMake and from the C++ code, and leaves the decision of what ends up inside the application binary to the developer. No browser, no sound by sound "save as" ritual and no network access at the application run time.

OpenGameArt publishes the packs under the [CC0](https://creativecommons.org/publicdomain/zero/1.0/) terms, so they need no attribution and stay usable commercially. **The packs are never committed into this repository**: they are fetched at the configure time, exactly the way the Font Awesome icon set is on the `appFontAwesome` branch.

### The enabler variables

The `cmake/enablers/audio/template-project-opengameart-audio-enabler.cmake` module declares the following:

| Variable | Default | Meaning |
| --- | --- | --- |
| `ENABLE_OPENGAMEART_AUDIO` | `ON` | enables the whole integration |
| `TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST` | `misc/opengameart-packs.txt` | the manifest naming every pack together with it's archive URL and it's license |
| `TEMPLATE_APP_OPENGAMEART_AUDIO_DIR` | empty | an already available packs directory to reuse instead of downloading one |
| `OPENGAMEART_AUDIO_EXTENSIONS` | `ogg;wav;mp3` | the sound file extensions to pick out of the packs |
| `OPENGAMEART_AUDIO_QT_RESOURCE_PREFIX` | `/sounds` | the prefix of the generated `.qrc` manifests |
| `OPENGAMEART_AUDIO_GRESOURCE_PREFIX` | `/ua/org/kytok/template/<binary>/sounds` | the prefix of the generated `.gresource.xml` manifests |
| `OPENGAMEART_AUDIO_GENERATE_FULL_MANIFESTS` | `ON` | generates the manifests carrying every available sound |

### The packs manifest

OpenGameArt hosts it's submissions under several different licenses, so this branch names no pack of it's own: the `misc/opengameart-packs.txt` manifest is the single place recording **which** pack is used, **where** it came from and **what** it is licensed under. Every line follows the

```
<pack>|<archive URL>|<license>
```

form, the `#` starting a comment and the empty lines being skipped:

```
cc0-interface-sfx|https://opengameart.org/sites/default/files/<archive>.zip|CC0-1.0
cc0-footsteps|https://opengameart.org/sites/default/files/<archive>.zip|CC0-1.0
```

**The manifest ships empty on purpose and the configure step stops until it is filled**: picking the submissions of interest - and reading the license of each one at [opengameart.org](https://opengameart.org) - is a decision this branch refuses to make on the developer's behalf. A pack with no recorded license is refused rather than silently assumed to be a CC0 one.

The recorded license travels all the way into the binary, so the code answers for it as well:

```cpp
auto pack = packs->find("cc0-interface-sfx");

pack->license();  // "CC0-1.0"
```

### Downloading the packs by hand

A host whose configure step reaches no network of it's own, a packs directory shared between several build trees and a wish to keep the downloads away from the build tree are all served by the `misc/scripts/fetch-opengameart-audio.sh` script:

```
misc/scripts/fetch-opengameart-audio.sh ~/opengameart-audio

cmake -S . -B build -DTEMPLATE_APP_OPENGAMEART_AUDIO_DIR=~/opengameart-audio
```

The script takes the target directory as it's single argument, obeys the `OPENGAMEART_AUDIO_PACKS` and the `OPENGAMEART_AUDIO_URL_TEMPLATE` environment variables, downloads through `curl` or `wget` (whichever is available) and leaves an already unpacked pack alone.

### Reaching the sounds from the C++ code

The enabler generates the sound index out of the very packs in use, so the whole set is reachable with no directory scanning at the run time and with no sound names hand written into the sources:

```cpp
#include "src/opengameartaudio/sounds/OpenGameArtSounds.h"

auto sounds = opengameartaudio::OpenGameArtSounds::create();

// every sound of every configured pack
for (const auto& sound : sounds->all()) {
  sound->name();       // "click_001"
  sound->alias();      // "interface-sounds/Audio/click_001.ogg"
  sound->filePath();   // the absolute path inside the packs directory
}

// the sounds of a single pack
auto interfaceSounds = sounds->ofPack("interface-sounds");

// a single sound by it's pack and pack relative path
auto click = sounds->find("interface-sounds", "Audio/click_001.ogg");

// every sound which name carries a given part
auto clicks = sounds->search("click");
```

### Embedding the sounds into the binary

Every pack stays intact inside the packs directory and only the sounds an application actually asks for end up inside it's binary. Select them with the `template_project_opengameart_audio_write_qrc` (Qt) or the `template_project_opengameart_audio_write_gresource` (Gtkmm) function, then hand the written manifest over to the resource compiler of the toolkit in use:

```cmake
template_project_opengameart_audio_write_qrc(
  "${CMAKE_CURRENT_BINARY_DIR}/opengameart-audio.qrc"
  SOUNDS
    interface-sounds/Audio/click_001.ogg
    interface-sounds/Audio/confirmation_001.ogg
)
```

Requesting neither `PACKS` nor `SOUNDS` selects the whole available set. The manifests carrying everything are generated already, at `generated/opengameartaudio/opengameart-audio-all.qrc` and `generated/opengameartaudio/opengameart-audio-all.gresource.xml` of the build directory.

The sounds keep their `<pack>/<path>` aliases inside the manifests, so the `OpenGameArtQtResourcePath` and the `OpenGameArtGResourcePath` classes resolve them at the run time:

```cpp
#include "src/opengameartaudio/resources/OpenGameArtQtResourcePath.h"

auto qtPath = opengameartaudio::OpenGameArtQtResourcePath::create();

qtPath->of(click);     // ":/sounds/interface-sounds/Audio/click_001.ogg"
qtPath->uriOf(click);  // "qrc:/sounds/interface-sounds/Audio/click_001.ogg"
```

The `COMPRESSED` flag of the GResource writer stays available for the uncompressed `.wav` members of a pack alone: the `.ogg` and the `.mp3` ones carry an already compressed stream, so letting GLib zlib them a second time costs build time and gains nothing.

### Playing the sounds

The branch carries no audio backend on purpose, exactly the way the `appFontAwesome` one carries no GUI toolkit: it answers for making the assets reachable and nothing more. Hand the `filePath` of a sound (or it's resource path) over to whatever backend the application already uses - the SDL, the SFML, the OpenAL or the miniaudio one - and the branch composes with any of them.
