#include "RHVoiceLibraryMock.h"

#include <RHVoice.h>

#include <string>
#include <vector>

namespace rhvoice
{

RHVoiceLibraryMock::RHVoiceLibraryMock()
{
  using ::testing::_;
  using ::testing::Return;

  ON_CALL(*this, NewTtsEngine(_)).WillByDefault(Return(ENGINE));
  ON_CALL(*this, NewMessage(_, _, _, _, _)).WillByDefault(Return(MESSAGE));
  ON_CALL(*this, Speak(_)).WillByDefault(Return(1));

  instance = this;
}

RHVoiceLibraryMock::~RHVoiceLibraryMock()
{
  instance = nullptr;
  callbacks = {};
}

int RHVoiceLibraryMock::speak(const int sampleRate,
                              const std::vector<short>& wav,
                              void* const userData)
{
  callbacks.set_sample_rate(sampleRate, userData);

  return callbacks.play_speech(wav.data(),
                               static_cast<unsigned int>(wav.size()), userData);
}

}  // namespace rhvoice

using rhvoice::RHVoiceLibraryMock;

RHVoice_tts_engine RHVoice_new_tts_engine(
    const RHVoice_init_params* const initParams)
{
  RHVoiceLibraryMock::callbacks = initParams->callbacks;

  return RHVoiceLibraryMock::instance->NewTtsEngine(*initParams);
}

void RHVoice_delete_tts_engine(const RHVoice_tts_engine engine)
{
  RHVoiceLibraryMock::instance->DeleteTtsEngine(engine);
}

RHVoice_message RHVoice_new_message(const RHVoice_tts_engine engine,
                                    const char* const text,
                                    const unsigned int length,
                                    const RHVoice_message_type type,
                                    const RHVoice_synth_params* const params,
                                    void* const userData)
{
  return RHVoiceLibraryMock::instance->NewMessage(
      engine, std::string(text, length), type, *params, userData);
}

int RHVoice_speak(const RHVoice_message message)
{
  return RHVoiceLibraryMock::instance->Speak(message);
}

void RHVoice_delete_message(const RHVoice_message message)
{
  RHVoiceLibraryMock::instance->DeleteMessage(message);
}
