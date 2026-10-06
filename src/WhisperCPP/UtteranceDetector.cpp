#include "src/WhisperCPP/UtteranceDetector.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <numeric>
#include <ratio>

namespace whisperi
{

UtteranceDetector::UtteranceDetector(const std::size_t sampleRate)
    : frameSamples{
          std::max<std::size_t>(sampleRate * FRAME_MS / std::milli::den, 1U)}
{
}

UtteranceDetector::samples UtteranceDetector::feed(const samples& captured)
{
  pending.insert(pending.end(), captured.cbegin(), captured.cend());

  samples complete;
  std::size_t examined = 0U;

  while (complete.empty() && examined + frameSamples <= pending.size()) {
    complete = collect(pending.data() + examined);
    examined += frameSamples;
  }

  pending.erase(pending.cbegin(),
                pending.cbegin() + static_cast<std::ptrdiff_t>(examined));

  return complete;
}

bool UtteranceDetector::is_speech(const float* const frame)
{
  const float level =
      std::sqrt(std::inner_product(frame, frame + frameSamples, frame, 0.0F) /
                static_cast<float>(frameSamples));

  if (examinedFrames < LEAD_FRAMES) {
    ++examinedFrames;
    noiseFloor += (level - noiseFloor) / static_cast<float>(examinedFrames);
    return false;
  }

  const bool speech =
      level > std::max(noiseFloor * SPEECH_RATIO, MIN_SPEECH_LEVEL);

  noiseFloor +=
      (level - noiseFloor) * (level < noiseFloor ? FLOOR_FALL : FLOOR_RISE);

  return speech;
}

UtteranceDetector::samples UtteranceDetector::collect(const float* const frame)
{
  const bool speech = is_speech(frame);

  utterance.insert(utterance.end(), frame, frame + frameSamples);

  // Till the speech starts the lead audio is all the utterance keeps.
  if (speechFrames == 0U && !speech) {
    if (utterance.size() > LEAD_FRAMES * frameSamples) {
      utterance.erase(
          utterance.cbegin(),
          utterance.cbegin() + static_cast<std::ptrdiff_t>(frameSamples));
    }

    return {};
  }

  speechFrames += speech ? 1U : 0U;
  silentFrames = speech ? 0U : silentFrames + 1U;

  if (silentFrames < PAUSE_FRAMES &&
      utterance.size() < MAX_FRAMES * frameSamples) {
    return {};
  }

  samples complete;

  if (speechFrames >= MIN_SPEECH_FRAMES) {
    complete.swap(utterance);
  }

  utterance.clear();
  speechFrames = 0U;
  silentFrames = 0U;

  return complete;
}

}  // namespace whisperi
