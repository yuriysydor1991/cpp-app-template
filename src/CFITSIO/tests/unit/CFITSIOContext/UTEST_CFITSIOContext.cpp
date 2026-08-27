#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "src/CFITSIO/CFITSIOContext.h"

using namespace cfitsioi;
using namespace testing;

class UTEST_CFITSIOContext : public Test
{
 public:
  UTEST_CFITSIOContext() : ctx{CFITSIOContext::create()} {}

  inline static const std::string expectedPath{"/tmp/an-image.fits"};
  inline static const std::string expectedHeader{"SIMPLE  =  T"};
  inline static const CFITSIOContext::pixels_buffer expectedPixels{1.0, 2.0,
                                                                   3.0, 4.0};
  inline static const CFITSIOContext::image_size expectedSize{2, 2};

  CFITSIOContextPtr ctx;
};

TEST_F(UTEST_CFITSIOContext, create_success)
{
  EXPECT_NE(ctx, nullptr);

  EXPECT_TRUE(ctx->get_path().empty());
  EXPECT_TRUE(ctx->get_pixels().empty());
  EXPECT_TRUE(ctx->get_header().empty());
  EXPECT_EQ(ctx->get_image_size(), CFITSIOContext::image_size(0, 0));
}

TEST_F(UTEST_CFITSIOContext, setting_the_path)
{
  ctx->set_path(expectedPath);

  EXPECT_EQ(ctx->get_path(), expectedPath);

  ctx->set_path({});

  EXPECT_TRUE(ctx->get_path().empty());
}

TEST_F(UTEST_CFITSIOContext, setting_the_image_size)
{
  ctx->set_image_size(expectedSize);

  EXPECT_EQ(ctx->get_image_size(), expectedSize);
}

TEST_F(UTEST_CFITSIOContext, setting_the_pixels)
{
  ctx->set_pixels(expectedPixels);

  EXPECT_EQ(ctx->get_pixels(), expectedPixels);

  ctx->set_pixels({});

  EXPECT_TRUE(ctx->get_pixels().empty());
}

TEST_F(UTEST_CFITSIOContext, setting_the_header)
{
  ctx->set_header(expectedHeader);

  EXPECT_EQ(ctx->get_header(), expectedHeader);

  ctx->set_header({});

  EXPECT_TRUE(ctx->get_header().empty());
}

TEST_F(UTEST_CFITSIOContext, pixels_are_filled_in_place_and_not_copied)
{
  // The modifiable accessor is what lets the CFITSIOController read a whole
  // image straight into the context.
  auto& pixels = ctx->get_pixels();

  pixels.resize(expectedPixels.size());

  EXPECT_EQ(ctx->get_pixels().size(), expectedPixels.size());
  EXPECT_EQ(&pixels, &ctx->get_pixels());
}

TEST_F(UTEST_CFITSIOContext, an_unmodifiable_context_gives_it_s_pixels_out)
{
  ctx->set_pixels(expectedPixels);

  const CFITSIOContextPtr readOnly = ctx;

  EXPECT_EQ(std::as_const(*readOnly).get_pixels(), expectedPixels);
}
