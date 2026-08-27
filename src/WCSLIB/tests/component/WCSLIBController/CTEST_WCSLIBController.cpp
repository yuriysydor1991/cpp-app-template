#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "src/CFITSIO/CFITSIOController.h"
#include "src/WCSLIB/WCSLIBController.h"

using namespace wcslibi;
using namespace testing;

/**
 * @brief Converts the coordinates of a FITS image written onto the disk, so
 * the whole way from the CFITSIO header down to the WCSLIB conversion gets
 * covered.
 */
class CTEST_WCSLIBController : public Test
{
 public:
  CTEST_WCSLIBController()
      : controller{WCSLIBController::create()},
        fits{cfitsioi::CFITSIOController::create()}
  {
  }

  ~CTEST_WCSLIBController() override
  {
    fits->close();

    std::error_code ec;
    std::filesystem::remove(fits_path(), ec);
  }

  static std::string fits_path()
  {
    return (std::filesystem::path{CTEST_WCSLIBController_DATA_DIR} /
            "CTEST_WCSLIBController.fits")
        .string();
  }

  /// @brief Writes a tangential projection image whose reference pixel sits at
  /// the reference world coordinate below.
  bool write_wcs_image()
  {
    return fits->create_image(fits_path(), {WIDTH, HEIGHT}) &&
           fits->write(cfitsioi::CFITSIOController::pixels_buffer(
               WIDTH * HEIGHT, 1.0)) &&
           fits->write_keyword("CTYPE1", "RA---TAN") &&
           fits->write_keyword("CTYPE2", "DEC--TAN") &&
           fits->write_keyword("CUNIT1", "deg") &&
           fits->write_keyword("CUNIT2", "deg") &&
           fits->write_keyword("CRPIX1", REFERENCE_X) &&
           fits->write_keyword("CRPIX2", REFERENCE_Y) &&
           fits->write_keyword("CRVAL1", REFERENCE_RA) &&
           fits->write_keyword("CRVAL2", REFERENCE_DEC) &&
           fits->write_keyword("CDELT1", -PIXEL_SCALE) &&
           fits->write_keyword("CDELT2", PIXEL_SCALE) && fits->close();
  }

  static constexpr const long WIDTH = 8;
  static constexpr const long HEIGHT = 4;
  static constexpr const double REFERENCE_X = 4.5;
  static constexpr const double REFERENCE_Y = 2.5;
  static constexpr const double REFERENCE_RA = 10.0;
  static constexpr const double REFERENCE_DEC = 20.0;
  static constexpr const double PIXEL_SCALE = 0.0002;
  static constexpr const double TOLERANCE = 1e-9;

  WCSLIBControllerPtr controller;
  cfitsioi::CFITSIOControllerPtr fits;
};

TEST_F(CTEST_WCSLIBController, header_of_a_written_image_holds_whole_keyrecords)
{
  ASSERT_TRUE(write_wcs_image());
  ASSERT_TRUE(fits->open(fits_path()));

  const std::string header = fits->read_header();

  EXPECT_FALSE(header.empty());
  EXPECT_EQ(header.size() % 80U, 0U);
}

TEST_F(CTEST_WCSLIBController, header_of_a_written_image_gets_parsed)
{
  ASSERT_TRUE(write_wcs_image());
  ASSERT_TRUE(fits->open(fits_path()));

  ASSERT_TRUE(controller->parse(fits->read_header()));

  EXPECT_EQ(controller->get_representations_count(), 1);
  EXPECT_EQ(controller->get_axes_count(), 2);
  EXPECT_EQ(controller->get_rejected_count(), 0);
  EXPECT_EQ(controller->get_axis_type(0), "RA---TAN");
  EXPECT_EQ(controller->get_axis_type(1), "DEC--TAN");
}

TEST_F(CTEST_WCSLIBController, reference_pixel_of_a_written_image_converts)
{
  ASSERT_TRUE(write_wcs_image());
  ASSERT_TRUE(fits->open(fits_path()));
  ASSERT_TRUE(controller->parse(fits->read_header()));

  const auto world = controller->to_world({REFERENCE_X, REFERENCE_Y});

  ASSERT_EQ(world.size(), 2U);
  EXPECT_NEAR(world[0], REFERENCE_RA, TOLERANCE);
  EXPECT_NEAR(world[1], REFERENCE_DEC, TOLERANCE);
}

TEST_F(CTEST_WCSLIBController, image_corner_of_a_written_image_round_trips)
{
  ASSERT_TRUE(write_wcs_image());
  ASSERT_TRUE(fits->open(fits_path()));
  ASSERT_TRUE(controller->parse(fits->read_header()));

  const WCSLIBController::coordinates corner{1.0, 1.0};

  const auto world = controller->to_world(corner);

  ASSERT_EQ(world.size(), 2U);

  // The first axis runs backwards (the negative CDELT1), as the sky does.
  EXPECT_GT(world[0], REFERENCE_RA);
  EXPECT_LT(world[1], REFERENCE_DEC);

  const auto restored = controller->to_pixel(world);

  ASSERT_EQ(restored.size(), 2U);
  EXPECT_NEAR(restored[0], corner[0], TOLERANCE);
  EXPECT_NEAR(restored[1], corner[1], TOLERANCE);
}

TEST_F(CTEST_WCSLIBController,
       image_without_wcs_keywords_maps_pixels_onto_themselves)
{
  ASSERT_TRUE(fits->create_image(fits_path(), {WIDTH, HEIGHT}));
  ASSERT_TRUE(fits->close());
  ASSERT_TRUE(fits->open(fits_path()));

  // The axes count alone is enough for the parser to build a default linear
  // representation, whose axes carry no type and convert into themselves.
  ASSERT_TRUE(controller->parse(fits->read_header()));

  EXPECT_EQ(controller->get_axes_count(), 2);
  EXPECT_TRUE(controller->get_axis_type(0).empty());

  const auto world = controller->to_world({REFERENCE_X, REFERENCE_Y});

  ASSERT_EQ(world.size(), 2U);
  EXPECT_NEAR(world[0], REFERENCE_X, TOLERANCE);
  EXPECT_NEAR(world[1], REFERENCE_Y, TOLERANCE);
}
