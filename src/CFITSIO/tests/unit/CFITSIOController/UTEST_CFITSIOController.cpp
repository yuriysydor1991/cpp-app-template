#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "src/CFITSIO/CFITSIOContext.h"
#include "src/CFITSIO/CFITSIOController.h"

using namespace cfitsioi;
using namespace testing;

class UTEST_CFITSIOController : public Test
{
 public:
  UTEST_CFITSIOController()
      : controller{CFITSIOController::create()}, ctx{CFITSIOContext::create()}
  {
  }

  /// @brief Gives a context pointing at the given path, since every call
  /// below takes it's file out of the context and not out of an argument.
  CFITSIOContextPtr context_of(const std::string& path)
  {
    ctx->set_path(path);
    return ctx;
  }

  inline static const CFITSIOContext::image_size SAMPLE_SIZE{8, 8};
  inline static const CFITSIOContext::pixels_buffer SAMPLE_PIXELS{1.0, 2.0, 3.0,
                                                                  4.0};

  CFITSIOControllerPtr controller;
  CFITSIOContextPtr ctx;
};

TEST_F(UTEST_CFITSIOController, create_success)
{
  EXPECT_NE(controller, nullptr);
  EXPECT_FALSE(controller->is_open());
  EXPECT_EQ(controller->last_status(), 0);
}

TEST_F(UTEST_CFITSIOController, every_context_taking_call_needs_a_context)
{
  EXPECT_FALSE(controller->open({}));
  EXPECT_FALSE(controller->create_image({}));
  EXPECT_FALSE(controller->read({}));
  EXPECT_FALSE(controller->write({}));
  EXPECT_FALSE(controller->read_header({}));
}

TEST_F(UTEST_CFITSIOController, clean_status_is_described)
{
  EXPECT_FALSE(controller->last_error().empty());
}

TEST_F(UTEST_CFITSIOController, close_without_open_succeeds)
{
  EXPECT_TRUE(controller->close());
}

TEST_F(UTEST_CFITSIOController, open_with_empty_path_fails)
{
  EXPECT_FALSE(controller->open(context_of({})));
  EXPECT_FALSE(controller->is_open());
}

TEST_F(UTEST_CFITSIOController, open_of_a_missing_file_fails)
{
  EXPECT_FALSE(
      controller->open(context_of("/tmp/this/path/does/not/exist.fits")));
  EXPECT_FALSE(controller->is_open());
  EXPECT_NE(controller->last_status(), 0);
  EXPECT_FALSE(controller->last_error().empty());
}

TEST_F(UTEST_CFITSIOController, create_image_with_empty_path_fails)
{
  ctx->set_image_size(SAMPLE_SIZE);

  EXPECT_FALSE(controller->create_image(context_of({})));
  EXPECT_FALSE(controller->is_open());
}

TEST_F(UTEST_CFITSIOController, create_image_with_empty_size_fails)
{
  auto given = context_of("/tmp/never-created.fits");

  for (const auto& size :
       {CFITSIOContext::image_size{0, 8}, CFITSIOContext::image_size{8, 0},
        CFITSIOContext::image_size{-1, -1}}) {
    given->set_image_size(size);

    EXPECT_FALSE(controller->create_image(given));
  }

  EXPECT_FALSE(controller->is_open());
}

TEST_F(UTEST_CFITSIOController, create_image_into_a_missing_directory_fails)
{
  ctx->set_image_size(SAMPLE_SIZE);

  EXPECT_FALSE(controller->create_image(
      context_of("/tmp/this/path/does/not/exist.fits")));
  EXPECT_NE(controller->last_status(), 0);
}

TEST_F(UTEST_CFITSIOController, image_size_without_open_is_empty)
{
  EXPECT_EQ(controller->get_image_size(), CFITSIOController::image_size(0, 0));
}

TEST_F(UTEST_CFITSIOController, hdu_count_without_open_is_empty)
{
  EXPECT_EQ(controller->get_hdu_count(), 0);
}

TEST_F(UTEST_CFITSIOController, read_without_open_is_empty)
{
  EXPECT_FALSE(controller->read(ctx));
  EXPECT_TRUE(ctx->get_pixels().empty());
}

TEST_F(UTEST_CFITSIOController, write_without_open_fails)
{
  ctx->set_pixels(SAMPLE_PIXELS);

  EXPECT_FALSE(controller->write(ctx));
}

TEST_F(UTEST_CFITSIOController, read_keyword_without_open_is_empty)
{
  EXPECT_TRUE(controller->read_keyword("OBJECT").empty());
}

TEST_F(UTEST_CFITSIOController, write_keyword_without_open_fails)
{
  EXPECT_FALSE(controller->write_keyword("OBJECT", "a value"));
  EXPECT_FALSE(controller->write_keyword("CRVAL1", 10.0));
}

TEST_F(UTEST_CFITSIOController, read_header_without_open_is_empty)
{
  ctx->set_header("a leftover header");

  EXPECT_FALSE(controller->read_header(ctx));
  EXPECT_TRUE(ctx->get_header().empty());
}

TEST_F(UTEST_CFITSIOController, keyword_with_empty_name_fails)
{
  EXPECT_TRUE(controller->read_keyword({}).empty());
  EXPECT_FALSE(controller->write_keyword({}, "a value"));
}
