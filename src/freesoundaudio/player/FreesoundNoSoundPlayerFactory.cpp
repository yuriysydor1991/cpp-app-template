#include "src/freesoundaudio/player/FreesoundSoundPlayerFactory.h"
#include "src/freesoundaudio/player/IFreesoundSoundPlayer.h"

namespace freesoundaudio
{

// Compiled in place of the FreesoundSdlMixerSoundPlayerFactory one whenever no
// audio backend is enabled, so the packs stay reachable with nothing to play
// them.
IFreesoundSoundPlayerPtr FreesoundSoundPlayerFactory::create() { return {}; }

}  // namespace freesoundaudio
