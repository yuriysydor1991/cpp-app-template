#include "src/TTS/WavWriter.h"

#include <climits>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <memory>
#include <ostream>
#include <string>

#include "src/log/log.h"

namespace tts
{

namespace
{

/// @brief The 16-bit samples size, the block one of the mono speech.
constexpr std::uint16_t BYTES_PER_SAMPLE{2U};

/// @brief The bytes the RIFF chunk size counts besides the samples: the WAVE
/// id, the format chunk and the data chunk header.
constexpr std::uint32_t RIFF_HEADERS_SIZE{36U};

/// @brief The size of the format chunk of the PCM samples.
constexpr std::uint32_t FORMAT_CHUNK_SIZE{16U};

/// @brief The format code of the integer PCM samples.
constexpr std::uint16_t PCM_FORMAT{1U};

/// @brief The channels count of the mono speech.
constexpr std::uint16_t MONO{1U};

/// @brief Puts the given field into the stream in the little endian byte
/// order, the one of every WAV field, as wide as the type of it.
template <typename Field>
void put(std::ostream& out, const Field value)
{
  for (std::size_t byte = 0U; byte < sizeof(Field); ++byte) {
    out.put(static_cast<char>((value >> (CHAR_BIT * byte)) & UCHAR_MAX));
  }
}

}  // namespace

bool WavWriter::write(const Speech& speech, const std::string& path)
{
  std::ofstream file{path, std::ofstream::binary | std::ofstream::trunc};

  if (!file) {
    LOGE("Fail to open the " << path << " WAV file for writing");
    return false;
  }

  const auto& pcm = speech.get_samples();
  const auto rate = static_cast<std::uint32_t>(speech.get_sample_rate());
  const auto dataSize =
      static_cast<std::uint32_t>(pcm.size() * BYTES_PER_SAMPLE);

  // The RIFF header, the PCM format chunk of a single channel and the data
  // chunk header.
  file << "RIFF";
  put(file, RIFF_HEADERS_SIZE + dataSize);
  file << "WAVEfmt ";
  put(file, FORMAT_CHUNK_SIZE);
  put(file, PCM_FORMAT);
  put(file, MONO);
  put(file, rate);
  put(file, rate * BYTES_PER_SAMPLE);
  put(file, BYTES_PER_SAMPLE);
  put(file, static_cast<std::uint16_t>(CHAR_BIT * BYTES_PER_SAMPLE));
  file << "data";
  put(file, dataSize);

  for (const Speech::sample value : pcm) {
    put(file, static_cast<std::uint16_t>(value));
  }

  file.close();

  if (!file) {
    LOGE("Fail to write the " << path << " WAV file");
    return false;
  }

  LOGD("The " << speech.get_duration().count() << " ms speech is written into "
              << path);

  return true;
}

WavWriterPtr WavWriter::create() { return std::make_shared<WavWriter>(); }

}  // namespace tts
