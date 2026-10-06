#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WHISPERCONTROLLERSPY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WHISPERCONTROLLERSPY_CLASS_H

#include <gmock/gmock.h>

#include "src/WhisperCPP/WhisperController.h"

namespace whisperi
{

/**
 * @brief The real WhisperController with the transcription mocked, so a test
 * sees the audio the listening hands over to it.
 */
class WhisperControllerSpy : public WhisperController
{
 public:
  MOCK_METHOD(result, transcribe, (const samples& audio), (override));
};

}  // namespace whisperi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WHISPERCONTROLLERSPY_CLASS_H
