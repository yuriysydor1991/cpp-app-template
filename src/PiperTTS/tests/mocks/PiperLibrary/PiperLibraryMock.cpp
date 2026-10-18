#include "PiperLibraryMock.h"

#include <piper.h>

#include <string>
#include <utility>
#include <vector>

namespace pipertts
{

PiperLibraryMock::PiperLibraryMock()
{
  using ::testing::_;
  using ::testing::Return;

  ON_CALL(*this, Create(_, _)).WillByDefault(Return(synthesizer()));
  ON_CALL(*this, SynthesizeStart(_)).WillByDefault(Return(PIPER_OK));
  ON_CALL(*this, SynthesizeNext(_)).WillByDefault([](auto* const chunk) {
    return speak(chunk, {}, true);
  });

  instance = this;
}

PiperLibraryMock::~PiperLibraryMock()
{
  instance = nullptr;
  chunkSamples.clear();
}

int PiperLibraryMock::speak(piper_audio_chunk* const chunk,
                            std::vector<float> samples, const bool last)
{
  chunkSamples = std::move(samples);

  chunk->samples = chunkSamples.data();
  chunk->num_samples = chunkSamples.size();
  chunk->sample_rate = SAMPLE_RATE;
  chunk->is_last = last;

  return last ? PIPER_DONE : PIPER_OK;
}

piper_synthesizer* PiperLibraryMock::synthesizer()
{
  // The libpiper keeps the synthesizer opaque and the controller never looks
  // into it, so any address serves as one.
  static char created{};

  return reinterpret_cast<piper_synthesizer*>(&created);
}

}  // namespace pipertts

using pipertts::PiperLibraryMock;

piper_synthesizer* piper_create(const char* const model_path,
                                [[maybe_unused]] const char* const config_path,
                                const char* const espeak_data_path)
{
  return PiperLibraryMock::instance->Create(model_path, espeak_data_path);
}

void piper_free(piper_synthesizer* const synth)
{
  PiperLibraryMock::instance->Free(synth);
}

int piper_synthesize_start(
    [[maybe_unused]] piper_synthesizer* const synth, const char* const text,
    [[maybe_unused]] const piper_synthesize_options* const options)
{
  return PiperLibraryMock::instance->SynthesizeStart(text);
}

int piper_synthesize_next([[maybe_unused]] piper_synthesizer* const synth,
                          piper_audio_chunk* const chunk)
{
  return PiperLibraryMock::instance->SynthesizeNext(chunk);
}
