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

  /// @brief Gives a context pointing at the given path, since both of the
  /// calls take their every parameter out of the context.
  CFITSIOContextPtr context_of(const std::string& path)
  {
    ctx->set_path(path);
    return ctx;
  }

  /// @brief Gives as many pixels as the SAMPLE_SIZE image holds.
  static CFITSIOContext::pixels_buffer sample_image()
  {
    const auto [width, height] = SAMPLE_SIZE;

    return CFITSIOContext::pixels_buffer(
        static_cast<CFITSIOContext::pixels_buffer::size_type>(width * height),
        1.0);
  }

  inline static const std::string MISSING_PATH{
      "/tmp/this/path/does/not/exist.fits"};
  inline static const CFITSIOContext::image_size SAMPLE_SIZE{8, 8};
  inline static const CFITSIOContext::pixels_buffer SAMPLE_PIXELS{1.0, 2.0, 3.0,
                                                                  4.0};

  CFITSIOControllerPtr controller;
  CFITSIOContextPtr ctx;
};

TEST_F(UTEST_CFITSIOController, create_success)
{
  EXPECT_NE(controller, nullptr);
  EXPECT_EQ(controller->last_status(), 0);
}

TEST_F(UTEST_CFITSIOController, clean_status_is_described)
{
  EXPECT_FALSE(controller->last_error().empty());
}

TEST_F(UTEST_CFITSIOController, both_calls_need_a_context)
{
  EXPECT_FALSE(controller->read({}));
  EXPECT_FALSE(controller->write({}));
}

TEST_F(UTEST_CFITSIOController, both_calls_need_a_path)
{
  ctx->set_image_size(SAMPLE_SIZE);
  ctx->set_pixels(sample_image());

  EXPECT_FALSE(controller->read(context_of({})));
  EXPECT_FALSE(controller->write(ctx));
}

TEST_F(UTEST_CFITSIOController, read_of_a_missing_file_fails)
{
  EXPECT_FALSE(controller->read(context_of(MISSING_PATH)));
  EXPECT_NE(controller->last_status(), 0);
  EXPECT_FALSE(controller->last_error().empty());
}

TEST_F(UTEST_CFITSIOController, read_of_a_missing_file_leaves_no_data_behind)
{
  ctx->set_pixels(SAMPLE_PIXELS);
  ctx->set_header("a leftover header");

  EXPECT_FALSE(controller->read(context_of(MISSING_PATH)));

  // The failing open leaves the context untouched, since the reading of it
  // never starts.
  EXPECT_EQ(ctx->get_pixels(), SAMPLE_PIXELS);
  EXPECT_EQ(ctx->get_header(), "a leftover header");
}

TEST_F(UTEST_CFITSIOController, write_of_an_empty_image_fails)
{
  auto given = context_of("/tmp/never-created.fits");

  for (const auto& size :
       {CFITSIOContext::image_size{0, 8}, CFITSIOContext::image_size{8, 0},
        CFITSIOContext::image_size{-1, -1}}) {
    given->set_image_size(size);

    EXPECT_FALSE(controller->write(given));
  }
}

TEST_F(UTEST_CFITSIOController, write_into_a_missing_directory_fails)
{
  ctx->set_image_size(SAMPLE_SIZE);

  EXPECT_FALSE(controller->write(context_of(MISSING_PATH)));
  EXPECT_NE(controller->last_status(), 0);
}

TEST_F(UTEST_CFITSIOController, header_only_write_into_a_missing_file_fails)
{
  ctx->set_write_header_only(true);
  ctx->set_keywords({{"OBJECT", "a value"}});

  EXPECT_FALSE(controller->write(context_of(MISSING_PATH)));
  EXPECT_NE(controller->last_status(), 0);
}
