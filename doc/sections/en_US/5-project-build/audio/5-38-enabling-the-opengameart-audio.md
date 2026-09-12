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

The branch ships a player, so the packs are not only reachable but audible. It is built upon the **SDL2 audio subsystem** and the **SDL_mixer decoders**, and enabled by the `ENABLE_SDL2_AUDIO` CMake variable, which is `ON` by default:

| Variable | Default | Meaning |
| --- | --- | --- |
| `ENABLE_SDL2_AUDIO` | `ON` | builds the sound player against SDL2 and SDL_mixer |
| `TEMPLATE_APP_SDL2_GIT` | the upstream repository | the SDL2 git source repository |
| `TEMPLATE_APP_SDL2_GIT_TAG` | `release-2.32.10` | the SDL2 release to pin |
| `TEMPLATE_APP_SDL2_MIXER_GIT` | the upstream repository | the SDL_mixer git source repository |
| `TEMPLATE_APP_SDL2_MIXER_GIT_TAG` | `release-2.8.1` | the SDL_mixer release to pin |

The `cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake` module probes the system libraries first and falls back to a FetchContent build, the same way every other third party enabler of this project does. Only the audio subsystem of SDL2 is used - no window, no renderer and no OpenGL.

**The bare SDL2 decodes the RIFF/WAVE files alone**, while OpenGameArt hosts it's submissions as `.ogg` and `.mp3` alike, so the decoders of the `SDL_mixer` satellite library are what makes those audible at all. Only the decoders SDL_mixer carries inside it's own sources are taken - the stb_vorbis `.ogg` one, the minimp3 `.mp3` one and the drflac `.flac` one - so a FetchContent build asks for no third party library of it's own, while the Opus, MOD, MIDI and WavPack ones, each needing a library installed on the host, are switched off rather than failing the configure of a host carrying none.

Which formats those are is the backend's own business, though, and so is the question of whether a backend was built in at all. **Neither ever reaches the calling code**: `OpenGameArtSoundsController` keeps the set and the player together and answers both questions on it's own.

```cpp
#include "src/opengameartaudio/controller/OpenGameArtSoundsController.h"

auto controller = opengameartaudio::OpenGameArtSoundsController::create(sounds);

auto sound = controller->draw();   // a sound the backend really decodes
                                   // (any sound of the set when it decodes none)

if (controller->playable()) {      // is there a backend at all
  controller->play(sound);         // returns once the sound has been played
}
```

The controller asks the player which extensions it supports instead of naming one, so a backend gained, swapped or dropped later changes nothing in the code above.

Switching `ENABLE_SDL2_AUDIO` off drops the player and leaves the rest of the subsystem - the index, the aliases and the resource manifests - untouched. The very same sources still compile: the `OpenGameArtSoundPlayerFactory::create` implementation the build picks answers with a player or with a nullptr one, so **no calling place carries a preprocessor branch**.

### The layers underneath

`OpenGameArtSdlMixerSoundPlayer` is the SDL2 backend itself and stays reachable for an application wanting to drive it directly:

```cpp
#include "src/opengameartaudio/player/OpenGameArtSdlMixerSoundPlayer.h"

auto player = opengameartaudio::OpenGameArtSdlMixerSoundPlayer::create();

player->supports("ogg");  // true
player->supports("mid");  // false, no MIDI decoder is brought up
```

The extensions answered for are the ones `Mix_Init` really brought up rather than a hand written list, so a SDL_mixer installed with more decoders than the FetchContent build carries is used for what it really decodes.

### Drawing a sound at random

A demo playing the very same click on every run proves little, so `OpenGameArtRandomSound` draws one out of the whole available set. The seed is takeable, which is what lets a test ask for a repeatable draw:

```cpp
#include "src/opengameartaudio/player/OpenGameArtRandomSound.h"

opengameartaudio::OpenGameArtRandomSound drawn;

auto any = drawn.pick(sounds);             // any sound at all
auto vorbis = drawn.pick(sounds, "ogg");  // only what the player really decodes
```

### The demo

`Application::run` of this branch puts the three together: it reports how many sounds the configured packs carry, draws a playable one, prints it's file path and both resource system paths, and plays it:

```
INF : The OpenGameArt packs carry 8 sounds at /.../resources/opengameart-audio
INF : The drawn cc0-footsteps/Audio/step_grass_01.wav sound file: /.../step_grass_01.wav
INF : ... published under: CC0-1.0
INF : ... embedded into the Qt resources: :/sounds/cc0-footsteps/Audio/step_grass_01.wav
INF : ... embedded into the GResource ones: /ua/org/kytok/template/CppAppTemplate/sounds/cc0-footsteps/Audio/step_grass_01.wav
INF : Playing the cc0-footsteps/Audio/step_grass_01.wav sound ...
```

With the packs empty, or with no sound of a format the player decodes, the demo says so and returns cleanly instead of failing.
