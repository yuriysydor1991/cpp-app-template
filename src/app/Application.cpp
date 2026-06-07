#include "src/app/Application.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/log/log.h"
#include "src/zlib/ZlibController.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  auto zlib = zlibi::ZlibController::create();

  assert(zlib != nullptr);

  const std::string sentence = "Hello, compressed sentence!";
  const zlibi::ZlibController::buffer original(sentence.begin(), sentence.end());

  const auto compressed = zlib->compress(original);
  const auto restored = zlib->uncompress(compressed);
  const std::string restoredSentence(restored.begin(), restored.end());

  LOGI("Original (" << original.size() << " bytes): " << sentence);
  LOGI("Compressed to " << compressed.size() << " bytes; restored ("
                        << restored.size() << " bytes): " << restoredSentence);

  if (restoredSentence == sentence) {
    LOGI("zlib compress / uncompress round-trip succeeded");
  } else {
    LOGE("zlib compress / uncompress round-trip mismatch");
  }

  return 0;
}

}  // namespace app
