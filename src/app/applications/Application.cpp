#include "src/app/applications/Application.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <string>

#include "src/CFITSIO/CFITSIOContext.h"
#include "src/CFITSIO/CFITSIOController.h"
#include "src/WCSLIB/WCSLIBController.h"
#include "src/app/CMDParamNames.h"
#include "src/log/log.h"

namespace app
{

namespace
{

/// @brief A celestial coordinate holds that many axes and no other.
constexpr const wcslibi::WCSLIBController::coordinates::size_type
    CELESTIAL_AXES = 2U;

/**
 * @brief Logs what the read image itself tells about it: the blocks the file
 * is built of, the image size, the pixel type and the range the pixels span.
 */
void report_image(const cfitsioi::CFITSIOControllerPtr& fits,
                  const cfitsioi::CFITSIOContextPtr& fctx)
{
  const auto [width, height] = fctx->get_image_size();

  LOGI("It holds " << fits->get_hdu_count() << " HDU(s) and a " << width << "x"
                   << height << " image of the " << fits->read_keyword("BITPIX")
                   << " BITPIX pixels");

  const auto& pixels = fctx->get_pixels();

  if (pixels.empty()) {
    LOGW("It carries no pixel to report about");
    return;
  }

  const auto [minimum, maximum] =
      std::minmax_element(pixels.cbegin(), pixels.cend());

  LOGI("Its " << pixels.size() << " pixels span from " << *minimum << " to "
              << *maximum);
}

/**
 * @brief Logs where the centre of the read image points at, as long as the
 * header the context carries holds the world coordinate system keywords.
 *
 * The context alone is what the WCSLIB component needs here, so no CFITSIO
 * call takes part in the conversion.
 */
void report_coordinates(const cfitsioi::CFITSIOContextPtr& fctx)
{
  auto wcs = wcslibi::WCSLIBController::create();

  assert(wcs != nullptr);

  if (!wcs->parse(fctx)) {
    LOGW("It carries no world coordinate system to report about");
    return;
  }

  const std::string first = wcs->get_axis_type(0);
  const std::string second = wcs->get_axis_type(1);

  // A header carrying no CTYPEi keyword still parses into a default linear
  // representation, whose axes carry no type and map the pixels onto
  // themselves, so there is no sky position to tell about.
  if (first.empty() || second.empty()) {
    LOGW("Its axes carry no coordinate type to convert them by");
    return;
  }

  const auto [width, height] = fctx->get_image_size();

  // The FITS pixels are counted from one, so the centre of an axis sits in
  // the middle between the first and the last pixel of it.
  const auto centre =
      wcs->to_world({(static_cast<double>(width) + 1.0) / 2.0,
                     (static_cast<double>(height) + 1.0) / 2.0});

  if (centre.size() < CELESTIAL_AXES) {
    LOGW("Fail to convert it's centre pixel: " << wcs->last_error());
    return;
  }

  LOGI("Its " << first << " / " << second << " centre points at " << centre[0]
              << ", " << centre[1] << " degrees");
}

}  // namespace

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  const std::string path = ctx->get_image_path();

  if (path.empty()) {
    LOGI("No FITS image to read: point at one with the "
         << CMDParamNames::IMAGEW << " or " << CMDParamNames::IMAGE
         << " <path> command line parameter");
    return 0;
  }

  auto fctx = cfitsioi::CFITSIOContext::create();
  auto fits = cfitsioi::CFITSIOController::create();

  assert(fctx != nullptr);
  assert(fits != nullptr);

  fctx->set_path(path);

  if (!fits->open(fctx)) {
    LOGE("Fail to open the " << path << " FITS image: " << fits->last_error());
    ctx->push_error("Fail to open the FITS image: " + path);
    return INVALID;
  }

  LOGI("Reading the " << path << " FITS image");

  if (!fits->read(fctx) || !fits->read_header(fctx)) {
    LOGE("Fail to read the " << path << " FITS image: " << fits->last_error());
    ctx->push_error("Fail to read the FITS image: " + path);
    return INVALID;
  }

  report_image(fits, fctx);
  report_coordinates(fctx);

  return 0;
}

}  // namespace app
