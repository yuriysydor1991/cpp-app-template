#include "src/app/applications/Application.h"

#include <cassert>
#include <filesystem>
#include <memory>
#include <string>

#include "src/CFITSIO/CFITSIOController.h"
#include "src/WCSLIB/WCSLIBController.h"
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

/// @brief The sky coordinate the reference pixel of the sample image points
/// at, in degrees, and the degrees a single pixel of it spans.
constexpr const double SAMPLE_REFERENCE_X = 4.5;
constexpr const double SAMPLE_REFERENCE_Y = 2.5;
constexpr const double SAMPLE_REFERENCE_RA = 10.0;
constexpr const double SAMPLE_REFERENCE_DEC = 20.0;
constexpr const double SAMPLE_PIXEL_SCALE = 0.0002;

/// @brief The sample image spans the two celestial axes and no other.
constexpr const wcslibi::WCSLIBController::coordinates::size_type
    CELESTIAL_AXES = 2U;

/**
 * @brief Writes the sample image together with the WCS keywords which the
 * coordinate conversion of the run below reads back.
 */
bool write_sample(const cfitsioi::CFITSIOControllerPtr& fits,
                  const std::string& path)
{
  return fits->create_image(path, {SAMPLE_WIDTH, SAMPLE_HEIGHT}) &&
         fits->write(cfitsioi::CFITSIOController::pixels_buffer(
             SAMPLE_WIDTH * SAMPLE_HEIGHT, SAMPLE_PIXEL)) &&
         fits->write_keyword("OBJECT", SAMPLE_OBJECT) &&
         fits->write_keyword("CTYPE1", "RA---TAN") &&
         fits->write_keyword("CTYPE2", "DEC--TAN") &&
         fits->write_keyword("CUNIT1", "deg") &&
         fits->write_keyword("CUNIT2", "deg") &&
         fits->write_keyword("CRPIX1", SAMPLE_REFERENCE_X) &&
         fits->write_keyword("CRPIX2", SAMPLE_REFERENCE_Y) &&
         fits->write_keyword("CRVAL1", SAMPLE_REFERENCE_RA) &&
         fits->write_keyword("CRVAL2", SAMPLE_REFERENCE_DEC) &&
         fits->write_keyword("CDELT1", -SAMPLE_PIXEL_SCALE) &&
         fits->write_keyword("CDELT2", SAMPLE_PIXEL_SCALE) && fits->close();
}

}  // namespace

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  auto fits = cfitsioi::CFITSIOController::create();
  auto wcs = wcslibi::WCSLIBController::create();

  assert(fits != nullptr);
  assert(wcs != nullptr);

  const std::string path =
      (std::filesystem::temp_directory_path() / SAMPLE_FILENAME).string();

  if (!write_sample(fits, path)) {
    LOGE("Fail to write the " << path << " FITS image: " << fits->last_error());
    return INVALID;
  }

  if (!fits->open(path)) {
    LOGE("Fail to open the " << path << " FITS image: " << fits->last_error());
    return INVALID;
  }

  const auto pixels = fits->read();
  const auto [width, height] = fits->get_image_size();

  LOGI("Read the " << width << "x" << height << " FITS image of "
                   << pixels.size() << " pixels back from " << path
                   << ", holding the '" << fits->read_keyword("OBJECT")
                   << "' object");

  if (!wcs->parse(fits->read_header())) {
    LOGE("Fail to parse the " << path
                              << " FITS coordinates: " << wcs->last_error());
    return INVALID;
  }

  const auto world = wcs->to_world({SAMPLE_REFERENCE_X, SAMPLE_REFERENCE_Y});

  if (world.size() < CELESTIAL_AXES) {
    LOGE("Fail to convert the reference pixel of the "
         << path << " FITS image: " << wcs->last_error());
    return INVALID;
  }

  LOGI("Its " << wcs->get_axis_type(0) << " / " << wcs->get_axis_type(1)
              << " reference pixel points at " << world[0] << ", " << world[1]
              << " degrees");

  return 0;
}

}  // namespace app
