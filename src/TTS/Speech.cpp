#include "src/TTS/Speech.h"

#include <chrono>
#include <utility>

namespace tts
{

Speech::Speech(samples pcm, const int sampleRate)
    : msamples{std::move(pcm)}, msample_rate{sampleRate}
{
}

const Speech::samples& Speech::get_samples() const { return msamples; }

int Speech::get_sample_rate() const { return msample_rate; }

std::chrono::milliseconds Speech::get_duration() const
{
  if (msample_rate <= 0) {
    return std::chrono::milliseconds{0};
  }

  return std::chrono::milliseconds{std::chrono::seconds{
             static_cast<std::chrono::seconds::rep>(msamples.size())}} /
         msample_rate;
}

}  // namespace tts
