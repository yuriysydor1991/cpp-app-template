#include <gtest/gtest.h>

#include "src/lzma/LzmaController.h"

using namespace lzmai;

TEST(UTEST_LzmaController, create_returns_an_instance)
{
  EXPECT_NE(LzmaController::create(), nullptr);
}

TEST(UTEST_LzmaController, empty_input_round_trips_to_empty)
{
  LzmaController lzma;

  const LzmaController::buffer compressed = lzma.compress({});
  const LzmaController::buffer restored = lzma.uncompress(compressed);

  EXPECT_TRUE(restored.empty());
}

TEST(UTEST_LzmaController, uncompress_of_garbage_returns_empty)
{
  LzmaController lzma;

  // Not a valid .xz stream - the controller must fail gracefully (empty).
  const LzmaController::buffer garbage{0x01, 0x02, 0x03, 0x04, 0x05};

  EXPECT_TRUE(lzma.uncompress(garbage).empty());
}
