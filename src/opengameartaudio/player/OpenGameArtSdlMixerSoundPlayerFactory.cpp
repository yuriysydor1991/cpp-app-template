#include "src/opengameartaudio/player/IOpenGameArtSoundPlayer.h"
#include "src/opengameartaudio/player/OpenGameArtSdlMixerSoundPlayer.h"
#include "src/opengameartaudio/player/OpenGameArtSoundPlayerFactory.h"

namespace opengameartaudio
{

// Compiled in place of the OpenGameArtNoSoundPlayerFactory one whenever the
// SDL2 audio enabler ran, so the choice of a backend stays a build time
// decision.
IOpenGameArtSoundPlayerPtr OpenGameArtSoundPlayerFactory::create()
{
  return OpenGameArtSdlMixerSoundPlayer::create();
}

}  // namespace opengameartaudio
