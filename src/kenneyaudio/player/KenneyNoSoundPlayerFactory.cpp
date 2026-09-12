#include "src/kenneyaudio/player/IKenneySoundPlayer.h"
#include "src/kenneyaudio/player/KenneySoundPlayerFactory.h"

namespace kenneyaudio
{

// Compiled in place of the KenneySdlMixerSoundPlayerFactory one whenever no
// audio backend is enabled, so the packs stay reachable with nothing to play
// them.
IKenneySoundPlayerPtr KenneySoundPlayerFactory::create() { return {}; }

}  // namespace kenneyaudio
