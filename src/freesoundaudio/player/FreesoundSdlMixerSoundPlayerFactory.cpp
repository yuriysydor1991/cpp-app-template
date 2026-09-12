#include "src/freesoundaudio/player/FreesoundSdlMixerSoundPlayer.h"
#include "src/freesoundaudio/player/FreesoundSoundPlayerFactory.h"
#include "src/freesoundaudio/player/IFreesoundSoundPlayer.h"

namespace freesoundaudio
{

// Compiled in place of the FreesoundNoSoundPlayerFactory one whenever the SDL2
// audio enabler ran, so the choice of a backend stays a build time decision.
IFreesoundSoundPlayerPtr FreesoundSoundPlayerFactory::create()
{
  return FreesoundSdlMixerSoundPlayer::create();
}

}  // namespace freesoundaudio
