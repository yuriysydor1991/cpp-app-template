#include "src/app/applications/Application.h"

#include <cassert>
#include <filesystem>
#include <memory>
#include <string>

#include "src/CFITSIO/CFITSIOController.h"
#include "src/log/log.h"

namespace app
{

namespace
{

constexpr const long SAMPLE_WIDTH = 8;
constexpr const long SAMPLE_HEIGHT = 4;
constexpr const double SAMPLE_PIXEL = 42.0;
constexpr const char* SAMPLE_OBJECT = "Template project sample";
constexpr const char* SAMPLE_FILENAME = "template-project-sample.fits";

}  // namespace

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  auto fits = cfitsioi::CFITSIOController::create();

  assert(fits != nullptr);

  const std::string path =
      (std::filesystem::temp_directory_path() / SAMPLE_FILENAME).string();

  const cfitsioi::CFITSIOController::pixels_buffer pixels(
      SAMPLE_WIDTH * SAMPLE_HEIGHT, SAMPLE_PIXEL);

  if (!fits->create_image(path, {SAMPLE_WIDTH, SAMPLE_HEIGHT}) ||
      !fits->write(pixels) || !fits->write_keyword("OBJECT", SAMPLE_OBJECT) ||
      !fits->close()) {
    LOGE("Fail to write the " << path << " FITS image: " << fits->last_error());
    return INVALID;
  }

  if (!fits->open(path)) {
    LOGE("Fail to open the " << path << " FITS image: " << fits->last_error());
    return INVALID;
  }

  const auto restored = fits->read();
  const auto [width, height] = fits->get_image_size();

  LOGI("Read the " << width << "x" << height << " FITS image of "
                   << restored.size() << " pixels back from " << path
                   << ", holding the '" << fits->read_keyword("OBJECT")
                   << "' object");

  return 0;
}

}  // namespace app
