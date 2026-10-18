#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PIPERLIBRARYMOCK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PIPERLIBRARYMOCK_CLASS_H

#include <gmock/gmock.h>
#include <piper.h>

#include <string>
#include <vector>

namespace pipertts
{

/**
 * @brief The mock of the libpiper calls the PiperController makes. The
 * PiperLibraryMock.cpp file defines the libpiper functions in place of the
 * library, which the unit test links not, and forwards them to the
 * PiperLibraryMock::instance one, so a test controls the engine.
 */
class PiperLibraryMock
{
 public:
  /// @brief Makes the created mock the forwarded one, which loads every voice
  /// and speaks the empty last chunk by default.
  PiperLibraryMock();
  virtual ~PiperLibraryMock();
  PiperLibraryMock(const PiperLibraryMock&) = delete;
  PiperLibraryMock& operator=(const PiperLibraryMock&) = delete;

  MOCK_METHOD(piper_synthesizer*, Create,
              (const std::string& modelPath,
               const std::string& espeakDataPath));
  MOCK_METHOD(void, Free, (piper_synthesizer * synthesizer));
  MOCK_METHOD(int, SynthesizeStart, (const std::string& text));
  MOCK_METHOD(int, SynthesizeNext, (piper_audio_chunk * chunk));

  /**
   * @brief Fills the given chunk with the given samples the way the libpiper
   * does.
   *
   * @return Returns the libpiper status of the chunk, the PIPER_DONE one for
   * the last chunk.
   */
  static int speak(piper_audio_chunk* chunk, std::vector<float> samples,
                   bool last);

  /// @brief Provides the synthesizer the mocked library creates by default.
  static piper_synthesizer* synthesizer();

  /// @brief The sample rate the mock reports.
  inline static constexpr const int SAMPLE_RATE = 22050;

  inline static PiperLibraryMock* instance{nullptr};
  /// @brief The samples of the last chunk, which the chunk points at.
  inline static std::vector<float> chunkSamples;
};

}  // namespace pipertts

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PIPERLIBRARYMOCK_CLASS_H
