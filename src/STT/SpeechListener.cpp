#include "src/STT/SpeechListener.h"

#include <memory>
#include <string>
#include <thread>
#include <utility>

#include "src/STT/ISpeechRecognizer.h"
#include "src/STT/Microphone.h"
#include "src/log/log.h"

namespace stt
{

SpeechListener::SpeechListener(ISpeechRecognizerPtr recognizer,
                               MicrophonePtr microphone)
    : mrecognizer{std::move(recognizer)}, mmicrophone{std::move(microphone)}
{
}

bool SpeechListener::init(const std::string& model)
{
  minitialized = mrecognizer->init(model);

  return minitialized;
}

SpeechListener::result SpeechListener::listen()
{
  if (!minitialized) {
    LOGE("The speech listener has no model loaded");
    return {};
  }

  if (!mmicrophone->open(ISpeechRecognizer::SAMPLE_RATE)) {
    return {};
  }

  std::this_thread::sleep_for(LISTEN_STEP);

  const auto utterance = mdetector.feed(mmicrophone->read());

  if (utterance.empty()) {
    return result{""};
  }

  LOGD("Recognizing the " << utterance.size() * 1000U /
                                 ISpeechRecognizer::SAMPLE_RATE
                          << " ms utterance");

  return mrecognizer->recognize(utterance);
}

SpeechListenerPtr SpeechListener::create()
{
  return std::make_shared<SpeechListener>(ISpeechRecognizer::create(),
                                          Microphone::create());
}

}  // namespace stt
