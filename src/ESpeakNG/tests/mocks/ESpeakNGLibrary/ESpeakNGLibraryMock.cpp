#include "ESpeakNGLibraryMock.h"

#include <espeak-ng/espeak_ng.h>

#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>

namespace espeakng
{

ESpeakNGLibraryMock::ESpeakNGLibraryMock()
{
  using ::testing::_;
  using ::testing::Return;

  ON_CALL(*this, Initialize()).WillByDefault(Return(ENS_OK));
  ON_CALL(*this, InitializeOutput(_)).WillByDefault(Return(ENS_OK));
  ON_CALL(*this, SetVoiceByName(_)).WillByDefault(Return(ENS_OK));
  ON_CALL(*this, Synthesize(_, _, _, _)).WillByDefault(Return(ENS_OK));
  ON_CALL(*this, GetSampleRate()).WillByDefault(Return(SAMPLE_RATE));
  ON_CALL(*this, Terminate()).WillByDefault(Return(ENS_OK));

  instance = this;
}

ESpeakNGLibraryMock::~ESpeakNGLibraryMock()
{
  instance = nullptr;
  callback = nullptr;
}

int ESpeakNGLibraryMock::speak(std::vector<short> wav, void* const userData)
{
  espeak_EVENT event{};

  event.user_data = userData;

  return callback(wav.empty() ? nullptr : wav.data(),
                  static_cast<int>(wav.size()), &event);
}

}  // namespace espeakng

using espeakng::ESpeakNGLibraryMock;

void espeak_ng_GetStatusCodeMessage(const espeak_ng_STATUS status,
                                    char* const buffer, const size_t length)
{
  std::snprintf(buffer, length, "mocked status %X",
                static_cast<unsigned>(status));
}

void espeak_ng_InitializePath([[maybe_unused]] const char* const path) {}

espeak_ng_STATUS espeak_ng_Initialize(
    [[maybe_unused]] espeak_ng_ERROR_CONTEXT* const context)
{
  return ESpeakNGLibraryMock::instance->Initialize();
}

void espeak_ng_ClearErrorContext(espeak_ng_ERROR_CONTEXT* const context)
{
  *context = nullptr;
}

espeak_ng_STATUS espeak_ng_InitializeOutput(
    const espeak_ng_OUTPUT_MODE outputMode,
    [[maybe_unused]] const int bufferLength,
    [[maybe_unused]] const char* const device)
{
  return ESpeakNGLibraryMock::instance->InitializeOutput(outputMode);
}

void espeak_SetSynthCallback(t_espeak_callback* const synthCallback)
{
  ESpeakNGLibraryMock::callback = synthCallback;
}

espeak_ng_STATUS espeak_ng_SetVoiceByName(const char* const name)
{
  return ESpeakNGLibraryMock::instance->SetVoiceByName(name);
}

espeak_ng_STATUS espeak_ng_Synthesize(
    const void* const text, const size_t size,
    [[maybe_unused]] const unsigned int position,
    [[maybe_unused]] const espeak_POSITION_TYPE positionType,
    [[maybe_unused]] const unsigned int endPosition, const unsigned int flags,
    [[maybe_unused]] unsigned int* const uniqueIdentifier, void* const userData)
{
  return ESpeakNGLibraryMock::instance->Synthesize(
      static_cast<const char*>(text), size, flags, userData);
}

int espeak_ng_GetSampleRate()
{
  return ESpeakNGLibraryMock::instance->GetSampleRate();
}

espeak_ng_STATUS espeak_ng_Terminate()
{
  return ESpeakNGLibraryMock::instance->Terminate();
}
