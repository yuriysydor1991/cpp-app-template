#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>

#include "src/CFITSIO/CFITSIOContext.h"
#include "src/CFITSIO/CFITSIOController.h"

using namespace cfitsioi;
using namespace testing;

class CTEST_CFITSIOController : public Test
{
 public:
  CTEST_CFITSIOController()
      : controller{CFITSIOController::create()}, ctx{CFITSIOContext::create()}
  {
    ctx->set_path(fits_path());
    ctx->set_image_size({WIDTH, HEIGHT});
    ctx->set_pixels(make_pixels());
    ctx->set_keywords({{"OBJECT", OBJECT}});
    ctx->set_numeric_keywords({{"CRVAL1", REFERENCE}});
  }

  ~CTEST_CFITSIOController() override
  {
    std::error_code ec;
    std::filesystem::remove(fits_path(), ec);
    std::filesystem::remove(plain_path(), ec);
  }

  static std::string fits_path()
  {
    return path_of("CTEST_CFITSIOController.fits");
  }

  static std::string plain_path()
  {
    return path_of("CTEST_CFITSIOController.txt");
  }

  static std::string path_of(const std::string& filename)
  {
    return (std::filesystem::path{CTEST_CFITSIOController_DATA_DIR} / filename)
        .string();
  }

  /// @brief Fills a buffer of the WIDTH x HEIGHT pixels with the growing
  /// values, so every pixel of the written image differs from it's neighbours.
  static CFITSIOContext::pixels_buffer make_pixels()
  {
    CFITSIOContext::pixels_buffer pixels(WIDTH * HEIGHT);

    for (CFITSIOContext::pixels_buffer::size_type i = 0; i < pixels.size();
         ++i) {
      pixels[i] = static_cast<double>(i);
    }

    return pixels;
  }

  /// @brief Gives a context pointing at the written file and carrying nothing
  /// else, so a read call alone fills it.
  static CFITSIOContextPtr empty_context()
  {
    auto reading = CFITSIOContext::create();

    reading->set_path(fits_path());

    return reading;
  }

  static constexpr const long WIDTH = 8;
  static constexpr const long HEIGHT = 4;
  static constexpr const char* OBJECT = "Template project sample";
  static constexpr const double REFERENCE = 10.5;
  static constexpr const std::string::size_type KEYRECORD_LENGTH = 80U;

  CFITSIOControllerPtr controller;
  CFITSIOContextPtr ctx;
};

TEST_F(CTEST_CFITSIOController, write_creates_the_file)
{
  EXPECT_TRUE(controller->write(ctx));
  EXPECT_TRUE(std::filesystem::exists(fits_path()));
}

TEST_F(CTEST_CFITSIOController, written_image_is_read_back_into_a_context)
{
  ASSERT_TRUE(controller->write(ctx));

  auto reading = empty_context();

  ASSERT_TRUE(controller->read(reading));

  EXPECT_EQ(reading->get_image_size(),
            CFITSIOContext::image_size(WIDTH, HEIGHT));
  EXPECT_EQ(reading->get_pixels(), make_pixels());
  EXPECT_EQ(reading->get_hdu_count(), 1);
  EXPECT_EQ(reading->get_keywords().at("OBJECT"), OBJECT);
  EXPECT_EQ(std::stod(reading->get_keywords().at("CRVAL1")), REFERENCE);
  EXPECT_EQ(reading->get_keywords().at("NAXIS1"), std::to_string(WIDTH));
}

TEST_F(CTEST_CFITSIOController, read_fills_the_header_keyrecords)
{
  ASSERT_TRUE(controller->write(ctx));

  auto reading = empty_context();

  ASSERT_TRUE(controller->read(reading));

  const std::string& header = reading->get_header();

  // Every keyrecord is exactly that long and the last one is always the END.
  ASSERT_FALSE(header.empty());
  EXPECT_EQ(header.size() % KEYRECORD_LENGTH, 0U);
  EXPECT_EQ(header.compare(header.size() - KEYRECORD_LENGTH, 3U, "END"), 0);
  EXPECT_NE(header.find(OBJECT), std::string::npos);
}

TEST_F(CTEST_CFITSIOController, header_only_read_skips_the_pixels)
{
  ASSERT_TRUE(controller->write(ctx));

  auto reading = empty_context();

  reading->set_read_header_only(true);

  ASSERT_TRUE(controller->read(reading));

  EXPECT_FALSE(reading->get_header().empty());
  EXPECT_EQ(reading->get_keywords().at("OBJECT"), OBJECT);
  EXPECT_TRUE(reading->get_pixels().empty());
  EXPECT_EQ(reading->get_image_size(), CFITSIOContext::image_size(0, 0));
}

TEST_F(CTEST_CFITSIOController, header_only_write_keeps_the_pixels)
{
  ASSERT_TRUE(controller->write(ctx));

  auto updating = empty_context();

  updating->set_write_header_only(true);
  updating->set_keywords({{"OBJECT", "another object"}});

  ASSERT_TRUE(controller->write(updating));

  auto reading = empty_context();

  ASSERT_TRUE(controller->read(reading));

  EXPECT_EQ(reading->get_keywords().at("OBJECT"), "another object");
  EXPECT_EQ(reading->get_pixels(), make_pixels());
}

TEST_F(CTEST_CFITSIOController, whole_write_replaces_the_image)
{
  ASSERT_TRUE(controller->write(ctx));

  ctx->set_image_size({HEIGHT, WIDTH});
  ctx->set_pixels(CFITSIOContext::pixels_buffer(WIDTH * HEIGHT, 1.0));

  ASSERT_TRUE(controller->write(ctx));

  auto reading = empty_context();

  ASSERT_TRUE(controller->read(reading));

  EXPECT_EQ(reading->get_image_size(),
            CFITSIOContext::image_size(HEIGHT, WIDTH));
}

TEST_F(CTEST_CFITSIOController, write_of_a_mismatching_pixels_count_fails)
{
  ctx->set_pixels({1.0, 2.0});

  EXPECT_FALSE(controller->write(ctx));

  ctx->set_pixels({});

  EXPECT_FALSE(controller->write(ctx));
}

TEST_F(CTEST_CFITSIOController, read_of_a_non_fits_file_fails)
{
  std::ofstream{plain_path()} << "not a FITS file at all\n";

  auto reading = empty_context();

  reading->set_path(plain_path());

  EXPECT_FALSE(controller->read(reading));
  EXPECT_NE(controller->last_status(), 0);
}

TEST_F(CTEST_CFITSIOController, failed_read_keeps_it_s_own_status)
{
  auto reading = empty_context();

  reading->set_path("/tmp/this/path/does/not/exist.fits");

  EXPECT_FALSE(controller->read(reading));

  // The closing of the file would report a success of it's own, so the status
  // of the failure is the one that survives a call.
  EXPECT_NE(controller->last_status(), 0);
}

TEST_F(CTEST_CFITSIOController, repeated_calls_hold_no_file_in_between)
{
  ASSERT_TRUE(controller->write(ctx));
  ASSERT_TRUE(controller->write(ctx));

  auto reading = empty_context();

  ASSERT_TRUE(controller->read(reading));
  ASSERT_TRUE(controller->read(reading));

  EXPECT_EQ(reading->get_pixels(), make_pixels());
}
