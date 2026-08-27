#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "src/CFITSIO/CFITSIOController.h"

using namespace cfitsioi;
using namespace testing;

class UTEST_CFITSIOController : public Test
{
 public:
  UTEST_CFITSIOController() : controller{CFITSIOController::create()} {}

  CFITSIOControllerPtr controller;
};

TEST_F(UTEST_CFITSIOController, create_success)
{
  EXPECT_NE(controller, nullptr);
  EXPECT_FALSE(controller->is_open());
  EXPECT_EQ(controller->last_status(), 0);
  EXPECT_TRUE(controller->get().empty());
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
  EXPECT_FALSE(controller->open({}));
  EXPECT_FALSE(controller->is_open());
}

TEST_F(UTEST_CFITSIOController, open_of_a_missing_file_fails)
{
  EXPECT_FALSE(controller->open("/tmp/this/path/does/not/exist.fits"));
  EXPECT_FALSE(controller->is_open());
  EXPECT_NE(controller->last_status(), 0);
  EXPECT_FALSE(controller->last_error().empty());
}

TEST_F(UTEST_CFITSIOController, create_image_with_empty_path_fails)
{
  EXPECT_FALSE(controller->create_image({}, {8, 8}));
  EXPECT_FALSE(controller->is_open());
}

TEST_F(UTEST_CFITSIOController, create_image_with_empty_size_fails)
{
  EXPECT_FALSE(controller->create_image("/tmp/never-created.fits", {0, 8}));
  EXPECT_FALSE(controller->create_image("/tmp/never-created.fits", {8, 0}));
  EXPECT_FALSE(controller->create_image("/tmp/never-created.fits", {-1, -1}));
  EXPECT_FALSE(controller->is_open());
}

TEST_F(UTEST_CFITSIOController, create_image_into_a_missing_directory_fails)
{
  EXPECT_FALSE(
      controller->create_image("/tmp/this/path/does/not/exist.fits", {8, 8}));
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
  EXPECT_TRUE(controller->read().empty());
  EXPECT_TRUE(controller->get().empty());
}

TEST_F(UTEST_CFITSIOController, write_without_open_fails)
{
  EXPECT_FALSE(controller->write({1.0, 2.0, 3.0, 4.0}));
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
  EXPECT_TRUE(controller->read_header().empty());
}

TEST_F(UTEST_CFITSIOController, keyword_with_empty_name_fails)
{
  EXPECT_TRUE(controller->read_keyword({}).empty());
  EXPECT_FALSE(controller->write_keyword({}, "a value"));
}
