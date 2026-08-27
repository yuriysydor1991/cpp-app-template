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
  }

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
    ctx->set_pixels(make_pixels());

    return controller->create_image(ctx) && controller->write(ctx) &&
           controller->write_keyword("OBJECT", OBJECT, "the sample object") &&
           controller->close();
  }

  static constexpr const long WIDTH = 8;
  static constexpr const long HEIGHT = 4;
  static constexpr const char* OBJECT = "Template project sample";
  static constexpr const double REFERENCE = 10.5;
  static constexpr const std::string::size_type KEYRECORD_LENGTH = 80U;

  CFITSIOControllerPtr controller;
  CFITSIOContextPtr ctx;
};

TEST_F(CTEST_CFITSIOController, create_write_and_close_success)
{
  EXPECT_TRUE(write_sample_image());
  EXPECT_FALSE(controller->is_open());
  EXPECT_TRUE(std::filesystem::exists(fits_path()));
}

TEST_F(CTEST_CFITSIOController, written_image_is_read_back_into_the_context)
{
  ASSERT_TRUE(write_sample_image());

  // Dropping what the writing has left behind, so the reading alone refills it.
  ctx->set_pixels({});
  ctx->set_image_size({0, 0});

  ASSERT_TRUE(controller->open(ctx));
  ASSERT_TRUE(controller->read(ctx));

  EXPECT_TRUE(controller->is_open());
  EXPECT_EQ(ctx->get_image_size(), CFITSIOContext::image_size(WIDTH, HEIGHT));
  EXPECT_EQ(ctx->get_pixels(), make_pixels());
  EXPECT_EQ(controller->get_image_size(),
            CFITSIOContext::image_size(WIDTH, HEIGHT));
  EXPECT_EQ(controller->get_hdu_count(), 1);
  EXPECT_EQ(controller->read_keyword("OBJECT"), OBJECT);
}

TEST_F(CTEST_CFITSIOController, existing_image_gets_overwritten)
{
  ASSERT_TRUE(write_sample_image());

  ctx->set_image_size({HEIGHT, WIDTH});

  EXPECT_TRUE(controller->create_image(ctx));
  EXPECT_EQ(controller->get_image_size(),
            CFITSIOContext::image_size(HEIGHT, WIDTH));
}

TEST_F(CTEST_CFITSIOController, keyword_of_an_open_image_gets_updated)
{
  ASSERT_TRUE(write_sample_image());
  ASSERT_TRUE(controller->open(ctx, true));

  EXPECT_TRUE(controller->write_keyword("OBJECT", "another object"));
  EXPECT_EQ(controller->read_keyword("OBJECT"), "another object");
}

TEST_F(CTEST_CFITSIOController, readonly_image_rejects_a_keyword_write)
{
  ASSERT_TRUE(write_sample_image());
  ASSERT_TRUE(controller->open(ctx));

  // The CFITSIO keeps the written keyword in a buffer of it's own, so a read
  // only file reports the refusal at the closing flush and not at the write.
  EXPECT_TRUE(controller->write_keyword("OBJECT", "another object"));
  EXPECT_FALSE(controller->close());
  EXPECT_NE(controller->last_status(), 0);
}

TEST_F(CTEST_CFITSIOController, numeric_keyword_is_read_back)
{
  ASSERT_TRUE(controller->create_image(ctx));

  // The numeric overload writes an unquoted value, which is what tells it
  // apart from the string one.
  EXPECT_TRUE(controller->write_keyword("CRVAL1", REFERENCE, "the reference"));
  EXPECT_EQ(std::stod(controller->read_keyword("CRVAL1")), REFERENCE);
}

TEST_F(CTEST_CFITSIOController,
       header_of_the_context_holds_the_written_keywords)
{
  ASSERT_TRUE(write_sample_image());
  ASSERT_TRUE(controller->open(ctx));
  ASSERT_TRUE(controller->read_header(ctx));

  const std::string& header = ctx->get_header();

  // Every keyrecord is exactly that long and the last one is always the END.
  ASSERT_FALSE(header.empty());
  EXPECT_EQ(header.size() % KEYRECORD_LENGTH, 0U);
  EXPECT_EQ(header.compare(header.size() - KEYRECORD_LENGTH, 3U, "END"), 0);

  EXPECT_NE(header.find("OBJECT"), std::string::npos);
  EXPECT_NE(header.find(OBJECT), std::string::npos);
  EXPECT_NE(header.find("NAXIS1"), std::string::npos);
}

TEST_F(CTEST_CFITSIOController, missing_keyword_read_fails)
{
  ASSERT_TRUE(write_sample_image());
  ASSERT_TRUE(controller->open(ctx));

  EXPECT_TRUE(controller->read_keyword("NOSUCHKW").empty());
  EXPECT_NE(controller->last_status(), 0);
}

TEST_F(CTEST_CFITSIOController, write_of_a_mismatching_pixels_count_fails)
{
  ASSERT_TRUE(controller->create_image(ctx));

  ctx->set_pixels({1.0, 2.0});

  EXPECT_FALSE(controller->write(ctx));

  ctx->set_pixels({});

  EXPECT_FALSE(controller->write(ctx));
}

TEST_F(CTEST_CFITSIOController, open_of_a_non_fits_file_fails)
{
  std::ofstream{plain_path()} << "not a FITS file at all\n";

  ctx->set_path(plain_path());

  EXPECT_FALSE(controller->open(ctx));
  EXPECT_FALSE(controller->is_open());
  EXPECT_NE(controller->last_status(), 0);
}

TEST_F(CTEST_CFITSIOController, reopen_replaces_the_held_file)
{
  ASSERT_TRUE(write_sample_image());
  ASSERT_TRUE(controller->open(ctx));
  ASSERT_TRUE(controller->read(ctx));
  ASSERT_FALSE(ctx->get_pixels().empty());

  ctx->set_path("/tmp/this/path/does/not/exist.fits");

  EXPECT_FALSE(controller->open(ctx));
  EXPECT_FALSE(controller->is_open());
  EXPECT_FALSE(controller->read(ctx));
  EXPECT_TRUE(ctx->get_pixels().empty());
}
