## Enabling the Freesound sound effects

The [Freesound](https://freesound.org) CC0 sound effect categories are made available to the project by the `ENABLE_FREESOUND_AUDIO` CMake variable, which is `ON` by default on this branch:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_FREESOUND_AUDIO=ON
```

The enabler downloads every configured category, unpacks it into a resources directory of the build tree, keeps it **intact** and reachable both from CMake and from the C++ code, and leaves the decision of what ends up inside the application binary to the developer. No browser, no sound by sound "save as" ritual and no network access at the application run time.

Freesound publishes the categories under the [CC0](https://creativecommons.org/publicdomain/zero/1.0/) terms, so they need no attribution and stay usable commercially. **The categories are never committed into this repository**: they are fetched at the configure time, exactly the way the Font Awesome icon set is on the `appFontAwesome` branch.

### The enabler variables

The `cmake/enablers/audio/template-project-freesound-audio-enabler.cmake` module declares the following:

| Variable | Default | Meaning |
| --- | --- | --- |
| `ENABLE_FREESOUND_AUDIO` | `ON` | enables the whole integration |
| `TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST` | `misc/freesound-sounds.txt` | the manifest naming every sound together with it's download URL and it's license |
| `TEMPLATE_APP_FREESOUND_AUDIO_DIR` | empty | an already available categories directory to reuse instead of downloading one |
| `FREESOUND_AUDIO_EXTENSIONS` | `ogg;wav;mp3` | the sound file extensions to pick out of the categories |
| `FREESOUND_AUDIO_QT_RESOURCE_PREFIX` | `/sounds` | the prefix of the generated `.qrc` manifests |
| `FREESOUND_AUDIO_GRESOURCE_PREFIX` | `/ua/org/kytok/template/<binary>/sounds` | the prefix of the generated `.gresource.xml` manifests |
| `FREESOUND_AUDIO_GENERATE_FULL_MANIFESTS` | `ON` | generates the manifests carrying every available sound |

### The sounds manifest

Freesound publishes it's submissions under CC0, CC-BY and CC-BY-NC alike, **one license per sound** rather than one for the whole database, so this branch records the provenance of every single file. The `misc/freesound-sounds.txt` manifest is the single place naming **which** sound is used, **where** it came from and **what** it is licensed under. Every line follows the

```
<category>/<file>|<download URL>|<license>
```

form, the `#` starting a comment and the empty lines being skipped:

```
interface/click.ogg|<the preview address of the submission>|CC0-1.0
feedback/notification.ogg|<the preview address of the submission>|CC-BY-4.0
```

The category is simply the subdirectory the file is downloaded into and the first part of it's alias, so the grouping is the developer's own rather than anything the site imposes.

**The manifest ships with five CC0 submissions of two categories** - two interface clicks and three feedback beeps - so the branch configures, builds and runs as it is checked out, while picking further submissions, and reading the license of each one at [freesound.org](https://freesound.org), stays the developer's own decision. A sound file sitting in the sounds directory with no manifest entry is refused, so the provenance can not silently go missing.

The Freesound API needs an account token and the `/download/` address of a submission answers a logged in account alone - an anonymous request lands on the login page - so the recorded address is the publicly reachable preview one, `cdn.freesound.org/previews/<first 3 digits of the id>/<id>_<uploader id>-hq.ogg`. The submission itself stays reachable as `freesound.org/s/<id>` and names it's uploader there, so the id inside the recorded address is the provenance of the very file.

The license and the source travel all the way into the binary, so the code answers for both:

```cpp
auto click = sounds->find("interface", "click.ogg");

click->license();    // "CC0-1.0"
click->sourceUrl();  // "https://cdn.freesound.org/previews/623/623175_11545182-hq.ogg"
```

That is what makes the attribution of a CC-BY sound possible at all, and the `misc/scripts/fetch-freesound-audio.sh` script writes the very same table into a `LICENSES.md` next to the downloaded files, so the directory carries it's provenance even once it leaves the build tree.

### Downloading the sounds by hand

A host whose configure step reaches no network of it's own, a categories directory shared between several build trees and a wish to keep the downloads away from the build tree are all served by the `misc/scripts/fetch-freesound-audio.sh` script:

```
misc/scripts/fetch-freesound-audio.sh ~/freesound-audio

cmake -S . -B build -DTEMPLATE_APP_FREESOUND_AUDIO_DIR=~/freesound-audio
```

The script takes the target directory as it's single argument, obeys the `FREESOUND_AUDIO_MANIFEST` environment variable, downloads through `curl` or `wget` (whichever is available) and leaves an already downloaded sound alone.

### Reaching the sounds from the C++ code

The enabler generates the sound index out of the very categories in use, so the whole set is reachable with no directory scanning at the run time and with no sound names hand written into the sources:

```cpp
#include "src/freesoundaudio/sounds/FreesoundSounds.h"

auto sounds = freesoundaudio::FreesoundSounds::create();

// every sound of every configured category
for (const auto& sound : sounds->all()) {
  sound->name();       // "click_001"
  sound->alias();      // "interface-sounds/Audio/click_001.ogg"
  sound->filePath();   // the absolute path inside the categories directory
}

// the sounds of a single category
auto interfaceSounds = sounds->ofPack("interface-sounds");

// a single sound by it's category and category relative path
auto click = sounds->find("interface-sounds", "Audio/click_001.ogg");

// every sound which name carries a given part
auto clicks = sounds->search("click");
```

### Embedding the sounds into the binary

Every category stays intact inside the categories directory and only the sounds an application actually asks for end up inside it's binary. Select them with the `template_project_freesound_audio_write_qrc` (Qt) or the `template_project_freesound_audio_write_gresource` (Gtkmm) function, then hand the written manifest over to the resource compiler of the toolkit in use:

```cmake
template_project_freesound_audio_write_qrc(
  "${CMAKE_CURRENT_BINARY_DIR}/freesound-audio.qrc"
  SOUNDS
    interface-sounds/Audio/click_001.ogg
    interface-sounds/Audio/confirmation_001.ogg
)
```

Requesting neither `PACKS` nor `SOUNDS` selects the whole available set. The manifests carrying everything are generated already, at `generated/freesoundaudio/freesound-audio-all.qrc` and `generated/freesoundaudio/freesound-audio-all.gresource.xml` of the build directory.

The sounds keep their `<category>/<path>` aliases inside the manifests, so the `FreesoundQtResourcePath` and the `FreesoundGResourcePath` classes resolve them at the run time:

```cpp
#include "src/freesoundaudio/resources/FreesoundQtResourcePath.h"

auto qtPath = freesoundaudio::FreesoundQtResourcePath::create();

qtPath->of(click);     // ":/sounds/interface-sounds/Audio/click_001.ogg"
qtPath->uriOf(click);  // "qrc:/sounds/interface-sounds/Audio/click_001.ogg"
```

The `COMPRESSED` flag of the GResource writer stays available for the uncompressed `.wav` members of a category alone: the `.ogg` and the `.mp3` ones carry an already compressed stream, so letting GLib zlib them a second time costs build time and gains nothing.

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

**The bare SDL2 decodes the RIFF/WAVE files alone**, while the sounds Freesound serves anonymously are the `.ogg` previews, so the decoders of the `SDL_mixer` satellite library are what makes them audible at all. Only the decoders SDL_mixer carries inside it's own sources are taken - the stb_vorbis `.ogg` one, the minimp3 `.mp3` one and the drflac `.flac` one - so a FetchContent build asks for no third party library of it's own, while the Opus, MOD, MIDI and WavPack ones, each needing a library installed on the host, are switched off rather than failing the configure of a host carrying none.

Which formats those are is the backend's own business, though, and so is the question of whether a backend was built in at all. **Neither ever reaches the calling code**: `FreesoundSoundsController` keeps the set and the player together and answers both questions on it's own.

```cpp
#include "src/freesoundaudio/controller/FreesoundSoundsController.h"

auto controller = freesoundaudio::FreesoundSoundsController::create(sounds);

auto sound = controller->draw();   // a sound the backend really decodes
                                   // (any sound of the set when it decodes none)

if (controller->playable()) {      // is there a backend at all
  controller->play(sound);         // returns once the sound has been played
}
```

The controller asks the player which extensions it supports instead of naming one, so a backend gained, swapped or dropped later changes nothing in the code above.

Switching `ENABLE_SDL2_AUDIO` off drops the player and leaves the rest of the subsystem - the index, the aliases and the resource manifests - untouched. The very same sources still compile: the `FreesoundSoundPlayerFactory::create` implementation the build picks answers with a player or with a nullptr one, so **no calling place carries a preprocessor branch**.

### The layers underneath

`FreesoundSdlMixerSoundPlayer` is the SDL2 backend itself and stays reachable for an application wanting to drive it directly:

```cpp
#include "src/freesoundaudio/player/FreesoundSdlMixerSoundPlayer.h"

auto player = freesoundaudio::FreesoundSdlMixerSoundPlayer::create();

player->supports("ogg");  // true
player->supports("mid");  // false, no MIDI decoder is brought up
```

The extensions answered for are the ones `Mix_Init` really brought up rather than a hand written list, so a SDL_mixer installed with more decoders than the FetchContent build carries is used for what it really decodes.

### Drawing a sound at random

A demo playing the very same click on every run proves little, so `FreesoundRandomSound` draws one out of the whole available set. The seed is takeable, which is what lets a test ask for a repeatable draw:

```cpp
#include "src/freesoundaudio/player/FreesoundRandomSound.h"

freesoundaudio::FreesoundRandomSound drawn;

auto any = drawn.pick(sounds);             // any sound at all
auto vorbis = drawn.pick(sounds, "ogg");  // only what the player really decodes
```

### The demo

`Application::run` of this branch puts the three together: it reports how many sounds the configured packs carry, draws a playable one, prints it's file path and both resource system paths, and plays it:

```
INF : The Freesound packs carry 5 sounds at /.../resources/freesound-audio
INF : The drawn feedback/confirmation.ogg sound file: /.../feedback/confirmation.ogg
INF : ... published under CC0-1.0 at https://cdn.freesound.org/previews/581/581603_5487341-hq.ogg
INF : ... embedded into the Qt resources: :/sounds/feedback/confirmation.ogg
INF : ... embedded into the GResource ones: /ua/org/kytok/template/CppAppTemplate/sounds/feedback/confirmation.ogg
INF : Playing the feedback/confirmation.ogg sound ...
```

With the packs empty, or with no sound of a format the player decodes, the demo says so and returns cleanly instead of failing.
