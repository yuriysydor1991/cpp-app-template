#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHRECOGNIZERMOCK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHRECOGNIZERMOCK_CLASS_H

#include <gmock/gmock.h>

#include <string>

#include "src/STT/ISpeechRecognizer.h"

namespace stt
{

class ISpeechRecognizerMock : public ISpeechRecognizer
{
 public:
  ISpeechRecognizerMock()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, init(_)).WillByDefault(Return(true));
    ON_CALL(*this, recognize(_)).WillByDefault(Return(result{""}));
  }

  MOCK_METHOD(bool, init, (const std::string& model), (override));
  MOCK_METHOD(result, recognize, (const samples& audio), (override));
};

}  // namespace stt

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ISPEECHRECOGNIZERMOCK_CLASS_H
