#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "src/zlib/ZlibController.h"

using namespace zlibi;
using buffer = ZlibController::buffer;

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

buffer from_string(const std::string& s)
{
  return buffer(s.begin(), s.end());
}

}  // namespace

class CTEST_ZlibController : public testing::Test
{
 protected:
  ZlibController zlib;  // exercises the real zlib library

  void expect_in_memory_round_trip(const buffer& data)
  {
    const buffer compressed = zlib.compress(data);
    const buffer restored = zlib.uncompress(compressed);
    EXPECT_EQ(restored, data);
  }

  void expect_file_round_trip(const std::string& path, const buffer& data)
  {
    ASSERT_TRUE(zlib.compress_to_file(path, data));
    const buffer restored = zlib.uncompress_from_file(path);
    EXPECT_EQ(restored, data);
    std::remove(path.c_str());
  }
};

// --- in-memory compress / uncompress over different data sets ---------------

TEST_F(CTEST_ZlibController, round_trip_empty)
{
  expect_in_memory_round_trip({});
}

TEST_F(CTEST_ZlibController, round_trip_single_byte)
{
  expect_in_memory_round_trip(filled(1, 0x42));
}

TEST_F(CTEST_ZlibController, round_trip_all_zeros)
{
  expect_in_memory_round_trip(filled(100000, 0x00));
}

TEST_F(CTEST_ZlibController, round_trip_all_ones)
{
  expect_in_memory_round_trip(filled(100000, 0xFF));
}

TEST_F(CTEST_ZlibController, round_trip_alternating_zeros_and_ones)
{
  expect_in_memory_round_trip(alternating(100000));
}

TEST_F(CTEST_ZlibController, round_trip_pseudo_random)
{
  expect_in_memory_round_trip(pseudo_random(50000));
}

TEST_F(CTEST_ZlibController, round_trip_short_text)
{
  expect_in_memory_round_trip(from_string("Hello, compressed sentence!"));
}

TEST_F(CTEST_ZlibController, round_trip_medium_text)
{
  std::string text;
  for (int i = 0; i < 100; ++i) {
    text += "The quick brown fox jumps over the lazy dog. ";
  }
  expect_in_memory_round_trip(from_string(text));
}

TEST_F(CTEST_ZlibController, round_trip_large_text)
{
  std::string text;
  for (int i = 0; i < 20000; ++i) {
    text += "line " + std::to_string(i) + ": some repetitive-ish payload\n";
  }
  expect_in_memory_round_trip(from_string(text));
}

// --- compression actually shrinks highly compressible data -----------------

TEST_F(CTEST_ZlibController, repetitive_data_is_actually_compressed)
{
  const buffer data = filled(100000, 0x00);
  const buffer compressed = zlib.compress(data);

  EXPECT_FALSE(compressed.empty());
  EXPECT_LT(compressed.size(), data.size());
}

// --- gzip file creation round trips ----------------------------------------

TEST_F(CTEST_ZlibController, file_round_trip_text)
{
  expect_file_round_trip(
      "ctest_zlib_text.gz",
      from_string("Hello, compressed sentence! Stored in a .gz file."));
}

TEST_F(CTEST_ZlibController, file_round_trip_all_zeros)
{
  expect_file_round_trip("ctest_zlib_zeros.gz", filled(50000, 0x00));
}

TEST_F(CTEST_ZlibController, file_round_trip_pseudo_random)
{
  expect_file_round_trip("ctest_zlib_random.gz", pseudo_random(50000));
}

TEST_F(CTEST_ZlibController, uncompress_from_missing_file_returns_empty)
{
  EXPECT_TRUE(zlib.uncompress_from_file("ctest_zlib_does_not_exist.gz").empty());
}
