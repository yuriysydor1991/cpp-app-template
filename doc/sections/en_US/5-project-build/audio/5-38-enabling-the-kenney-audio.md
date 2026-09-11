## Enabling the Kenney sound effects

The [Kenney](https://kenney.nl/assets) CC0 sound effect packs are made available to the project by the `ENABLE_KENNEY_AUDIO` CMake variable, which is `ON` by default on this branch:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_KENNEY_AUDIO=ON
```

The enabler downloads every configured pack, unpacks it into a resources directory of the build tree, keeps it **intact** and reachable both from CMake and from the C++ code, and leaves the decision of what ends up inside the application binary to the developer. No browser, no sound by sound "save as" ritual and no network access at the application run time.

Kenney publishes the packs under the [CC0](https://creativecommons.org/publicdomain/zero/1.0/) terms, so they need no attribution and stay usable commercially. **The packs are never committed into this repository**: they are fetched at the configure time, exactly the way the Font Awesome icon set is on the `appFontAwesome` branch.

### The enabler variables

The `cmake/enablers/audio/template-project-kenney-audio-enabler.cmake` module declares the following:

| Variable | Default | Meaning |
| --- | --- | --- |
| `ENABLE_KENNEY_AUDIO` | `ON` | enables the whole integration |
| `KENNEY_AUDIO_PACKS` | `interface-sounds;impact-sounds;digital-audio;ui-audio` | the packs to make available |
| `TEMPLATE_APP_KENNEY_AUDIO_URL_TEMPLATE` | the upstream URL | the per pack download URL, the `<pack>` placeholder standing for the pack name |
| `TEMPLATE_APP_KENNEY_AUDIO_DIR` | empty | an already available packs directory to reuse instead of downloading one |
| `KENNEY_AUDIO_EXTENSIONS` | `ogg;wav;mp3` | the sound file extensions to pick out of the packs |
| `KENNEY_AUDIO_QT_RESOURCE_PREFIX` | `/sounds` | the prefix of the generated `.qrc` manifests |
| `KENNEY_AUDIO_GRESOURCE_PREFIX` | `/ua/org/kytok/template/<binary>/sounds` | the prefix of the generated `.gresource.xml` manifests |
| `KENNEY_AUDIO_GENERATE_FULL_MANIFESTS` | `ON` | generates the manifests carrying every available sound |

**Verify the `TEMPLATE_APP_KENNEY_AUDIO_URL_TEMPLATE` value against [kenney.nl](https://kenney.nl/assets) before the first fetch**: the pack archives are ordinary downloads rather than a versioned API, so their addresses are the upstream site's business and may change.

### Downloading the packs by hand

A host whose configure step reaches no network of it's own, a packs directory shared between several build trees and a wish to keep the downloads away from the build tree are all served by the `misc/scripts/fetch-kenney-audio.sh` script:

```
misc/scripts/fetch-kenney-audio.sh ~/kenney-audio

cmake -S . -B build -DTEMPLATE_APP_KENNEY_AUDIO_DIR=~/kenney-audio
```

The script takes the target directory as it's single argument, obeys the `KENNEY_AUDIO_PACKS` and the `KENNEY_AUDIO_URL_TEMPLATE` environment variables, downloads through `curl` or `wget` (whichever is available) and leaves an already unpacked pack alone.

### Reaching the sounds from the C++ code

The enabler generates the sound index out of the very packs in use, so the whole set is reachable with no directory scanning at the run time and with no sound names hand written into the sources:

```cpp
#include "src/kenneyaudio/sounds/KenneySounds.h"

auto sounds = kenneyaudio::KenneySounds::create();

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

Every pack stays intact inside the packs directory and only the sounds an application actually asks for end up inside it's binary. Select them with the `template_project_kenney_audio_write_qrc` (Qt) or the `template_project_kenney_audio_write_gresource` (Gtkmm) function, then hand the written manifest over to the resource compiler of the toolkit in use:

```cmake
template_project_kenney_audio_write_qrc(
  "${CMAKE_CURRENT_BINARY_DIR}/kenney-audio.qrc"
  SOUNDS
    interface-sounds/Audio/click_001.ogg
    interface-sounds/Audio/confirmation_001.ogg
)
```

Requesting neither `PACKS` nor `SOUNDS` selects the whole available set. The manifests carrying everything are generated already, at `generated/kenneyaudio/kenney-audio-all.qrc` and `generated/kenneyaudio/kenney-audio-all.gresource.xml` of the build directory.

The sounds keep their `<pack>/<path>` aliases inside the manifests, so the `KenneyQtResourcePath` and the `KenneyGResourcePath` classes resolve them at the run time:

```cpp
#include "src/kenneyaudio/resources/KenneyQtResourcePath.h"

auto qtPath = kenneyaudio::KenneyQtResourcePath::create();

qtPath->of(click);     // ":/sounds/interface-sounds/Audio/click_001.ogg"
qtPath->uriOf(click);  // "qrc:/sounds/interface-sounds/Audio/click_001.ogg"
```

The `COMPRESSED` flag of the GResource writer stays available for the uncompressed `.wav` members of a pack alone: the `.ogg` and the `.mp3` ones carry an already compressed stream, so letting GLib zlib them a second time costs build time and gains nothing.

### Playing the sounds

The branch ships a player, so the packs are not only reachable but audible. It is built upon the **SDL2 audio subsystem** and enabled by the `ENABLE_SDL2_AUDIO` CMake variable, which is `ON` by default:

| Variable | Default | Meaning |
| --- | --- | --- |
| `ENABLE_SDL2_AUDIO` | `ON` | builds the sound player against SDL2 |
| `TEMPLATE_APP_SDL2_GIT` | the upstream repository | the SDL2 git source repository |
| `TEMPLATE_APP_SDL2_GIT_TAG` | `release-2.32.10` | the SDL2 release to pin |

The `cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake` module probes the system SDL2 first and falls back to a FetchContent build, the same way every other third party enabler of this project does. Only the audio subsystem of SDL2 is used - no window, no renderer and no OpenGL.

**The bare SDL2 decodes the RIFF/WAVE files alone.** The compressed formats are the business of the separate `SDL_mixer` library, so a `.ogg` or a `.mp3` sound is refused with a message naming it rather than handed to the audio device as noise:

```cpp
#include "src/kenneyaudio/player/KenneySdlSoundPlayer.h"

auto player = kenneyaudio::KenneySdlSoundPlayer::create();

player->supports("wav");  // true
player->supports("ogg");  // false, SDL_mixer territory

player->play(sound);      // returns once the sound has been played to the end
```

Switching `ENABLE_SDL2_AUDIO` off drops the player and leaves the rest of the subsystem - the index, the aliases and the resource manifests - untouched, so the branch still composes with an application bringing it's own audio backend.

### Drawing a sound at random

A demo playing the very same click on every run proves little, so `KenneyRandomSound` draws one out of the whole available set. The seed is takeable, which is what lets a test ask for a repeatable draw:

```cpp
#include "src/kenneyaudio/player/KenneyRandomSound.h"

kenneyaudio::KenneyRandomSound drawn;

auto any = drawn.pick(sounds);          // any sound at all
auto wave = drawn.pick(sounds, "wav");  // only what the player really decodes
```

### The demo

`Application::run` of this branch puts the three together: it reports how many sounds the configured packs carry, draws a playable one, prints it's file path and both resource system paths, and plays it:

```
INF : The Kenney packs carry 12 sounds at /.../resources/kenney-audio
INF : The drawn interface-sounds/Audio/confirmation_001.wav sound file: /.../confirmation_001.wav
INF : ... embedded into the Qt resources: :/sounds/interface-sounds/Audio/confirmation_001.wav
INF : ... embedded into the GResource ones: /ua/org/kytok/template/CppAppTemplate/sounds/interface-sounds/Audio/confirmation_001.wav
INF : Playing the interface-sounds/Audio/confirmation_001.wav sound ...
```

With the packs empty, or with no sound of a format the player decodes, the demo says so and returns cleanly instead of failing.
