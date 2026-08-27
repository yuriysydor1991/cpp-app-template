#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>

#include "src/CFITSIO/CFITSIOController.h"

using namespace cfitsioi;
using namespace testing;

class CTEST_CFITSIOController : public Test
{
 public:
  CTEST_CFITSIOController() : controller{CFITSIOController::create()} {}

  ~CTEST_CFITSIOController() override
  {
    controller->close();

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
  static CFITSIOController::pixels_buffer make_pixels()
  {
    CFITSIOController::pixels_buffer pixels(WIDTH * HEIGHT);

    for (CFITSIOController::pixels_buffer::size_type i = 0; i < pixels.size();
         ++i) {
      pixels[i] = static_cast<double>(i);
    }

    return pixels;
  }

  bool write_sample_image()
  {
    return controller->create_image(fits_path(), {WIDTH, HEIGHT}) &&
           controller->write(make_pixels()) &&
           controller->write_keyword("OBJECT", OBJECT, "the sample object") &&
           controller->close();
  }

  static constexpr const long WIDTH = 8;
  static constexpr const long HEIGHT = 4;
  static constexpr const char* OBJECT = "Template project sample";

  CFITSIOControllerPtr controller;
};

TEST_F(CTEST_CFITSIOController, create_write_and_close_success)
{
  EXPECT_TRUE(write_sample_image());
  EXPECT_FALSE(controller->is_open());
  EXPECT_TRUE(std::filesystem::exists(fits_path()));
}

TEST_F(CTEST_CFITSIOController, written_image_is_read_back)
{
  ASSERT_TRUE(write_sample_image());
  ASSERT_TRUE(controller->open(fits_path()));

  EXPECT_TRUE(controller->is_open());
  EXPECT_EQ(controller->get_image_size(),
            CFITSIOController::image_size(WIDTH, HEIGHT));
  EXPECT_EQ(controller->get_hdu_count(), 1);
  EXPECT_EQ(controller->read(), make_pixels());
  EXPECT_EQ(controller->get(), make_pixels());
  EXPECT_EQ(controller->read_keyword("OBJECT"), OBJECT);
}

TEST_F(CTEST_CFITSIOController, existing_image_gets_overwritten)
{
  ASSERT_TRUE(write_sample_image());
  EXPECT_TRUE(controller->create_image(fits_path(), {HEIGHT, WIDTH}));
  EXPECT_EQ(controller->get_image_size(),
            CFITSIOController::image_size(HEIGHT, WIDTH));
}

TEST_F(CTEST_CFITSIOController, keyword_of_an_open_image_gets_updated)
{
  ASSERT_TRUE(write_sample_image());
  ASSERT_TRUE(controller->open(fits_path(), true));

  EXPECT_TRUE(controller->write_keyword("OBJECT", "another object"));
  EXPECT_EQ(controller->read_keyword("OBJECT"), "another object");
}

TEST_F(CTEST_CFITSIOController, readonly_image_rejects_a_keyword_write)
{
  ASSERT_TRUE(write_sample_image());
  ASSERT_TRUE(controller->open(fits_path()));

  // The CFITSIO keeps the written keyword in a buffer of it's own, so a read
  // only file reports the refusal at the closing flush and not at the write.
  EXPECT_TRUE(controller->write_keyword("OBJECT", "another object"));
  EXPECT_FALSE(controller->close());
  EXPECT_NE(controller->last_status(), 0);
}

TEST_F(CTEST_CFITSIOController, missing_keyword_read_fails)
{
  ASSERT_TRUE(write_sample_image());
  ASSERT_TRUE(controller->open(fits_path()));

  EXPECT_TRUE(controller->read_keyword("NOSUCHKW").empty());
  EXPECT_NE(controller->last_status(), 0);
}

TEST_F(CTEST_CFITSIOController, write_of_a_mismatching_pixels_count_fails)
{
  ASSERT_TRUE(controller->create_image(fits_path(), {WIDTH, HEIGHT}));

  EXPECT_FALSE(controller->write({1.0, 2.0}));
  EXPECT_FALSE(controller->write({}));
}

TEST_F(CTEST_CFITSIOController, open_of_a_non_fits_file_fails)
{
  std::ofstream{plain_path()} << "not a FITS file at all\n";

  EXPECT_FALSE(controller->open(plain_path()));
  EXPECT_FALSE(controller->is_open());
  EXPECT_NE(controller->last_status(), 0);
}

TEST_F(CTEST_CFITSIOController, reopen_replaces_the_held_file)
{
  ASSERT_TRUE(write_sample_image());
  ASSERT_TRUE(controller->open(fits_path()));
  ASSERT_FALSE(controller->read().empty());

  EXPECT_FALSE(controller->open("/tmp/this/path/does/not/exist.fits"));
  EXPECT_FALSE(controller->is_open());
  EXPECT_TRUE(controller->read().empty());
}
