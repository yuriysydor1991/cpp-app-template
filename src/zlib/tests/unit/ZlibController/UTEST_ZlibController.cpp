#include <gtest/gtest.h>

#include "src/zlib/ZlibController.h"

using namespace zlibi;

TEST(UTEST_ZlibController, create_returns_an_instance)
{
  EXPECT_NE(ZlibController::create(), nullptr);
}

TEST(UTEST_ZlibController, empty_input_round_trips_to_empty)
{
  ZlibController zlib;

  const ZlibController::buffer compressed = zlib.compress({});
  const ZlibController::buffer restored = zlib.uncompress(compressed);

  EXPECT_TRUE(restored.empty());
}

TEST(UTEST_ZlibController, uncompress_of_garbage_returns_empty)
{
  ZlibController zlib;

  // Not a valid zlib stream - the controller must fail gracefully (empty).
  const ZlibController::buffer garbage{0x01, 0x02, 0x03, 0x04, 0x05};

  EXPECT_TRUE(zlib.uncompress(garbage).empty());
}
