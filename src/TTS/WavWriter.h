#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WAVWRITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WAVWRITER_CLASS_H

#include <memory>
#include <string>

#include "src/TTS/Speech.h"

namespace tts
{

/**
 * @brief Writes the speech into the 16-bit PCM mono WAV (RIFF WAVE) file, the
 * one every audio player and editor opens.
 */
class WavWriter
{
 public:
  using WavWriterPtr = std::shared_ptr<WavWriter>;

  virtual ~WavWriter() = default;
  WavWriter() = default;

  /**
   * @brief Writes the given speech into the WAV file of the given path in
   * place of the previous contents of it.
   *
   * @param speech The speech to write.
   * @param path The WAV file path.
   *
   * @return Returns true on success and false otherwise.
   */
  virtual bool write(const Speech& speech, const std::string& path);

  static WavWriterPtr create();
};

using WavWriterPtr = WavWriter::WavWriterPtr;

}  // namespace tts

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WAVWRITER_CLASS_H
