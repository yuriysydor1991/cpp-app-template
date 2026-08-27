#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "src/CFITSIO/CFITSIOContext.h"
#include "src/WCSLIB/WCSLIBController.h"

using namespace wcslibi;
using namespace testing;

class UTEST_WCSLIBController : public Test
{
 public:
  UTEST_WCSLIBController()
      : controller{WCSLIBController::create()},
        ctx{cfitsioi::CFITSIOContext::create()}
  {
  }

  /// @brief Gives a context carrying the given header, since the parse call
  /// takes it out of the context and not out of an argument.
  cfitsioi::CFITSIOContextPtr context_of(const std::string& header)
  {
    ctx->set_header(header);
    return ctx;
  }

  /// @brief Pads the given keyword text up to the fixed FITS keyrecord length,
  /// since a header keyrecord carries no terminator of it's own.
  static std::string keyrecord(const std::string& text)
  {
    std::string padded{text};

    padded.resize(KEYRECORD_LENGTH, ' ');

    return padded;
  }

  /// @brief Builds the header of a plain tangential projection image whose
  /// reference pixel sits at the REFERENCE_PIXEL world coordinate.
  static std::string tan_header()
  {
    return keyrecord("SIMPLE  =                    T") +
           keyrecord("BITPIX  =                  -64") +
           keyrecord("NAXIS   =                    2") +
           keyrecord("NAXIS1  =                    8") +
           keyrecord("NAXIS2  =                    4") +
           keyrecord("CTYPE1  = 'RA---TAN'") +
           keyrecord("CTYPE2  = 'DEC--TAN'") +
           keyrecord("CRPIX1  =                  4.5") +
           keyrecord("CRPIX2  =                  2.5") +
           keyrecord("CRVAL1  =                 10.0") +
           keyrecord("CRVAL2  =                 20.0") +
           keyrecord("CDELT1  =              -0.0002") +
           keyrecord("CDELT2  =               0.0002") +
           keyrecord("CUNIT1  = 'deg'") + keyrecord("CUNIT2  = 'deg'") +
           keyrecord("END");
  }

  static constexpr const std::string::size_type KEYRECORD_LENGTH = 80U;
  static constexpr const double TOLERANCE = 1e-9;

  WCSLIBControllerPtr controller;
  cfitsioi::CFITSIOContextPtr ctx;
};

TEST_F(UTEST_WCSLIBController, parse_without_a_context_fails)
{
  EXPECT_FALSE(controller->parse({}));
  EXPECT_FALSE(controller->is_ready());
}

TEST_F(UTEST_WCSLIBController, create_success)
{
  EXPECT_NE(controller, nullptr);
  EXPECT_FALSE(controller->is_ready());
  EXPECT_EQ(controller->last_status(), 0);
  EXPECT_TRUE(controller->last_error().empty());
  EXPECT_EQ(controller->get_representations_count(), 0);
  EXPECT_EQ(controller->get_axes_count(), 0);
  EXPECT_EQ(controller->get_rejected_count(), 0);
}

TEST_F(UTEST_WCSLIBController, parse_of_an_empty_header_fails)
{
  EXPECT_FALSE(controller->parse(context_of({})));
  EXPECT_FALSE(controller->is_ready());
}

TEST_F(UTEST_WCSLIBController, parse_of_a_truncated_keyrecord_fails)
{
  EXPECT_FALSE(controller->parse(context_of("SIMPLE  =   T")));
  EXPECT_FALSE(controller->is_ready());
}

TEST_F(UTEST_WCSLIBController, parse_of_a_header_without_axes_fails)
{
  EXPECT_FALSE(controller->parse(context_of(
      keyrecord("SIMPLE  =                    T") + keyrecord("END"))));
  EXPECT_FALSE(controller->is_ready());
}

TEST_F(UTEST_WCSLIBController,
       header_without_wcs_keywords_maps_pixels_onto_themselves)
{
  // The axes count alone is enough for the parser to build a default linear
  // representation, whose axes carry no type and convert into themselves.
  ASSERT_TRUE(controller->parse(context_of(
      keyrecord("SIMPLE  =                    T") +
      keyrecord("BITPIX  =                  -64") +
      keyrecord("NAXIS   =                    2") +
      keyrecord("NAXIS1  =                    8") +
      keyrecord("NAXIS2  =                    4") + keyrecord("END"))));

  EXPECT_EQ(controller->get_axes_count(), 2);
  EXPECT_TRUE(controller->get_axis_type(0).empty());

  const auto world = controller->to_world({4.5, 2.5});

  ASSERT_EQ(world.size(), 2U);
  EXPECT_NEAR(world[0], 4.5, TOLERANCE);
  EXPECT_NEAR(world[1], 2.5, TOLERANCE);
}

TEST_F(UTEST_WCSLIBController, parse_of_a_tan_header_succeeds)
{
  ASSERT_TRUE(controller->parse(context_of(tan_header())));

  EXPECT_TRUE(controller->is_ready());
  EXPECT_EQ(controller->last_status(), 0);
  EXPECT_EQ(controller->get_representations_count(), 1);
  EXPECT_EQ(controller->get_axes_count(), 2);
  EXPECT_EQ(controller->get_rejected_count(), 0);
  EXPECT_EQ(controller->get_axis_type(0), "RA---TAN");
  EXPECT_EQ(controller->get_axis_type(1), "DEC--TAN");
}

TEST_F(UTEST_WCSLIBController, axis_type_out_of_range_is_empty)
{
  ASSERT_TRUE(controller->parse(context_of(tan_header())));

  EXPECT_TRUE(controller->get_axis_type(-1).empty());
  EXPECT_TRUE(controller->get_axis_type(2).empty());
}

TEST_F(UTEST_WCSLIBController,
       reference_pixel_converts_into_the_reference_value)
{
  ASSERT_TRUE(controller->parse(context_of(tan_header())));

  const auto world = controller->to_world({4.5, 2.5});

  ASSERT_EQ(world.size(), 2U);
  EXPECT_NEAR(world[0], 10.0, TOLERANCE);
  EXPECT_NEAR(world[1], 20.0, TOLERANCE);
}

TEST_F(UTEST_WCSLIBController,
       reference_value_converts_into_the_reference_pixel)
{
  ASSERT_TRUE(controller->parse(context_of(tan_header())));

  const auto pixel = controller->to_pixel({10.0, 20.0});

  ASSERT_EQ(pixel.size(), 2U);
  EXPECT_NEAR(pixel[0], 4.5, TOLERANCE);
  EXPECT_NEAR(pixel[1], 2.5, TOLERANCE);
}

TEST_F(UTEST_WCSLIBController, conversion_round_trip_keeps_the_coordinate)
{
  ASSERT_TRUE(controller->parse(context_of(tan_header())));

  const WCSLIBController::coordinates pixel{1.0, 4.0};

  const auto world = controller->to_world(pixel);

  ASSERT_EQ(world.size(), 2U);

  const auto restored = controller->to_pixel(world);

  ASSERT_EQ(restored.size(), 2U);
  EXPECT_NEAR(restored[0], pixel[0], TOLERANCE);
  EXPECT_NEAR(restored[1], pixel[1], TOLERANCE);
}

TEST_F(UTEST_WCSLIBController, conversion_of_a_mismatching_coordinate_fails)
{
  ASSERT_TRUE(controller->parse(context_of(tan_header())));

  EXPECT_TRUE(controller->to_world({1.0}).empty());
  EXPECT_TRUE(controller->to_pixel({1.0, 2.0, 3.0}).empty());
  EXPECT_TRUE(controller->to_world({}).empty());
}

TEST_F(UTEST_WCSLIBController, conversion_without_parse_fails)
{
  EXPECT_TRUE(controller->to_world({4.5, 2.5}).empty());
  EXPECT_TRUE(controller->to_pixel({10.0, 20.0}).empty());
}

TEST_F(UTEST_WCSLIBController, select_out_of_range_fails)
{
  ASSERT_TRUE(controller->parse(context_of(tan_header())));

  EXPECT_FALSE(controller->select(1));
  EXPECT_FALSE(controller->is_ready());

  EXPECT_TRUE(controller->select(0));
  EXPECT_TRUE(controller->is_ready());
}

TEST_F(UTEST_WCSLIBController, select_without_parse_fails)
{
  EXPECT_FALSE(controller->select(0));
  EXPECT_FALSE(controller->is_ready());
}

TEST_F(UTEST_WCSLIBController, release_frees_the_representations)
{
  ASSERT_TRUE(controller->parse(context_of(tan_header())));

  controller->release();

  EXPECT_FALSE(controller->is_ready());
  EXPECT_EQ(controller->get_representations_count(), 0);
  EXPECT_EQ(controller->get_axes_count(), 0);
  EXPECT_TRUE(controller->last_error().empty());
}

TEST_F(UTEST_WCSLIBController, reparse_replaces_the_representations)
{
  ASSERT_TRUE(controller->parse(context_of(tan_header())));
  ASSERT_TRUE(controller->parse(context_of(tan_header())));

  EXPECT_TRUE(controller->is_ready());
  EXPECT_EQ(controller->get_representations_count(), 1);
}
