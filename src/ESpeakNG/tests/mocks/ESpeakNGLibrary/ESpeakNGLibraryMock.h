#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ESPEAKNGLIBRARYMOCK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ESPEAKNGLIBRARYMOCK_CLASS_H

#include <espeak-ng/espeak_ng.h>
#include <gmock/gmock.h>

#include <cstddef>
#include <string>
#include <vector>

namespace espeakng
{

/**
 * @brief The mock of the eSpeak NG library calls the ESpeakNGController
 * makes. The ESpeakNGLibraryMock.cpp file defines the eSpeak NG functions in
 * place of the library, which the unit test links not, and forwards them to
 * the ESpeakNGLibraryMock::instance one, so a test controls the engine.
 */
class ESpeakNGLibraryMock
{
 public:
  /// @brief Makes the created mock the forwarded one, every call of it a
  /// successful one by default.
  ESpeakNGLibraryMock();
  virtual ~ESpeakNGLibraryMock();
  ESpeakNGLibraryMock(const ESpeakNGLibraryMock&) = delete;
  ESpeakNGLibraryMock& operator=(const ESpeakNGLibraryMock&) = delete;

  MOCK_METHOD(espeak_ng_STATUS, Initialize, ());
  MOCK_METHOD(espeak_ng_STATUS, InitializeOutput,
              (espeak_ng_OUTPUT_MODE outputMode));
  MOCK_METHOD(espeak_ng_STATUS, SetVoiceByName, (const std::string& name));
  MOCK_METHOD(espeak_ng_STATUS, Synthesize,
              (const std::string& text, std::size_t size, unsigned int flags,
               void* userData));
  MOCK_METHOD(int, GetSampleRate, ());
  MOCK_METHOD(espeak_ng_STATUS, Terminate, ());

  /**
   * @brief Hands the given samples over to the synthesis callback the way
   * the eSpeak NG does, the empty ones as the end of the synthesis.
   *
   * @return Returns the callback result.
   */
  static int speak(std::vector<short> wav, void* userData);

  /// @brief The sample rate the mock reports by default.
  inline static constexpr const int SAMPLE_RATE = 22050;

  inline static ESpeakNGLibraryMock* instance{nullptr};
  inline static t_espeak_callback* callback{nullptr};
};

}  // namespace espeakng

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ESPEAKNGLIBRARYMOCK_CLASS_H
