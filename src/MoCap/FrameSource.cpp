#include "src/MoCap/FrameSource.h"

#include <charconv>
#include <memory>
#include <string>
#include <system_error>

#include "src/log/log.h"

namespace mocap
{

bool FrameSource::open(const std::string& input)
{
  int camera{0};
  const char* end = input.data() + input.size();
  const auto [last, error] = std::from_chars(input.data(), end, camera);
  const bool isCamera = !input.empty() && error == std::errc{} && last == end;

  if (!(isCamera ? mcapture.open(camera) : mcapture.open(input))) {
    LOGE("Fail to open the " << input << " input");
    return false;
  }

  return true;
}

bool FrameSource::read(cv::Mat& frame)
{
  return mcapture.read(frame) && !frame.empty();
}

FrameSourcePtr FrameSource::create() { return std::make_shared<FrameSource>(); }

}  // namespace mocap
