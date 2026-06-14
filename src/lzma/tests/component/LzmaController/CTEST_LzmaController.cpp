#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "src/lzma/LzmaController.h"

using namespace lzmai;
using buffer = LzmaController::buffer;

namespace
{

buffer filled(std::size_t n, unsigned char value) { return buffer(n, value); }

buffer alternating(std::size_t n)
{
  buffer b(n);
  for (std::size_t i = 0; i < n; ++i) {
    b[i] = static_cast<unsigned char>((i % 2U == 0U) ? 0x00 : 0xFF);
  }
  return b;
}

buffer pseudo_random(std::size_t n)
{
  buffer b(n);
  std::uint32_t state = 0x12345678U;
  for (std::size_t i = 0; i < n; ++i) {
    state = state * 1664525U + 1013904223U;  // numerical recipes LCG
    b[i] = static_cast<unsigned char>(state >> 24);
  }
  return b;
}

buffer from_string(const std::string& s) { return buffer(s.begin(), s.end()); }

}  // namespace

class CTEST_LzmaController : public testing::Test
{
 protected:
  LzmaController lzma;  // exercises the real liblzma library

  void expect_in_memory_round_trip(const buffer& data)
  {
    const buffer compressed = lzma.compress(data);
    const buffer restored = lzma.uncompress(compressed);
    EXPECT_EQ(restored, data);
  }
};

// --- in-memory compress / uncompress over different data sets ---------------

TEST_F(CTEST_LzmaController, round_trip_empty)
{
  expect_in_memory_round_trip({});
}

TEST_F(CTEST_LzmaController, round_trip_single_byte)
{
  expect_in_memory_round_trip(filled(1, 0x42));
}

TEST_F(CTEST_LzmaController, round_trip_all_zeros)
{
  expect_in_memory_round_trip(filled(100000, 0x00));
}

TEST_F(CTEST_LzmaController, round_trip_all_ones)
{
  expect_in_memory_round_trip(filled(100000, 0xFF));
}

TEST_F(CTEST_LzmaController, round_trip_alternating_zeros_and_ones)
{
  expect_in_memory_round_trip(alternating(100000));
}

TEST_F(CTEST_LzmaController, round_trip_pseudo_random)
{
  expect_in_memory_round_trip(pseudo_random(50000));
}

TEST_F(CTEST_LzmaController, round_trip_short_text)
{
  expect_in_memory_round_trip(from_string("Hello, compressed sentence!"));
}

TEST_F(CTEST_LzmaController, round_trip_medium_text)
{
  std::string text;
  for (int i = 0; i < 100; ++i) {
    text += "The quick brown fox jumps over the lazy dog. ";
  }
  expect_in_memory_round_trip(from_string(text));
}

TEST_F(CTEST_LzmaController, round_trip_large_text)
{
  std::string text;
  for (int i = 0; i < 20000; ++i) {
    text += "line " + std::to_string(i) + ": some repetitive-ish payload\n";
  }
  expect_in_memory_round_trip(from_string(text));
}

// --- compression actually shrinks highly compressible data -----------------

TEST_F(CTEST_LzmaController, repetitive_data_is_actually_compressed)
{
  const buffer data = filled(100000, 0x00);
  const buffer compressed = lzma.compress(data);

  EXPECT_FALSE(compressed.empty());
  EXPECT_LT(compressed.size(), data.size());
}
