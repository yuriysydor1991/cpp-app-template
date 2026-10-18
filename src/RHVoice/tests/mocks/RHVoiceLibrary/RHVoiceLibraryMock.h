#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RHVOICELIBRARYMOCK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RHVOICELIBRARYMOCK_CLASS_H

#include <RHVoice.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>

namespace rhvoice
{

/**
 * @brief The mock of the RHVoice library calls the RHVoiceController makes.
 * The RHVoiceLibraryMock.cpp file defines the RHVoice functions in place of
 * the library, which the unit test links not, and forwards them to the
 * RHVoiceLibraryMock::instance one, so a test controls the engine.
 */
class RHVoiceLibraryMock
{
 public:
  /// @brief Makes the created mock the forwarded one, every call of it a
  /// successful one by default.
  RHVoiceLibraryMock();
  virtual ~RHVoiceLibraryMock();
  RHVoiceLibraryMock(const RHVoiceLibraryMock&) = delete;
  RHVoiceLibraryMock& operator=(const RHVoiceLibraryMock&) = delete;

  MOCK_METHOD(RHVoice_tts_engine, NewTtsEngine,
              (const RHVoice_init_params& params));
  MOCK_METHOD(void, DeleteTtsEngine, (RHVoice_tts_engine engine));
  MOCK_METHOD(RHVoice_message, NewMessage,
              (RHVoice_tts_engine engine, const std::string& text,
               RHVoice_message_type type, const RHVoice_synth_params& params,
               void* userData));
  MOCK_METHOD(int, Speak, (RHVoice_message message));
  MOCK_METHOD(void, DeleteMessage, (RHVoice_message message));

  /**
   * @brief Hands the given sample rate and samples over to the callbacks of
   * the created engine the way the RHVoice does while speaking.
   *
   * @return Returns the result of the samples callback.
   */
  static int speak(int sampleRate, const std::vector<short>& wav,
                   void* userData);

  /// @brief The sample rate the tests speak at.
  inline static constexpr const int SAMPLE_RATE = 24000;

  /// @brief The engine and the message handles the mock gives out, which
  /// nothing dereferences.
  inline static char handles[2]{};
  inline static const RHVoice_tts_engine ENGINE{
      reinterpret_cast<RHVoice_tts_engine>(&handles[0])};
  inline static const RHVoice_message MESSAGE{
      reinterpret_cast<RHVoice_message>(&handles[1])};

  inline static RHVoiceLibraryMock* instance{nullptr};
  inline static RHVoice_callbacks callbacks{};
};

}  // namespace rhvoice

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RHVOICELIBRARYMOCK_CLASS_H
