#include "src/kenneyaudio/player/IKenneySoundPlayer.h"
#include "src/kenneyaudio/player/KenneySdlSoundPlayer.h"
#include "src/kenneyaudio/player/KenneySoundPlayerFactory.h"

namespace kenneyaudio
{

// Compiled in place of the KenneyNoSoundPlayerFactory one whenever the SDL2
// audio enabler ran, so the choice of a backend stays a build time decision.
IKenneySoundPlayerPtr KenneySoundPlayerFactory::create()
{
  return KenneySdlSoundPlayer::create();
}

}  // namespace kenneyaudio
