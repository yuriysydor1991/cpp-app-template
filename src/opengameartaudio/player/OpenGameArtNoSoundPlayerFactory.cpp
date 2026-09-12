#include "src/opengameartaudio/player/IOpenGameArtSoundPlayer.h"
#include "src/opengameartaudio/player/OpenGameArtSoundPlayerFactory.h"

namespace opengameartaudio
{

// Compiled in place of the OpenGameArtSdlMixerSoundPlayerFactory one whenever
// no audio backend is enabled, so the packs stay reachable with nothing to
// play them.
IOpenGameArtSoundPlayerPtr OpenGameArtSoundPlayerFactory::create()
{
  return {};
}

}  // namespace opengameartaudio
