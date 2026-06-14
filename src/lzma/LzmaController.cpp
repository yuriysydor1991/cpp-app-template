#include "src/lzma/LzmaController.h"

#include <lzma.h>

#include <array>
#include <cstddef>
#include <cstdint>

#include "src/log/log.h"

namespace lzmai
{

namespace
{
constexpr std::size_t CHUNK = 16384U;
constexpr std::uint32_t PRESET = LZMA_PRESET_DEFAULT;
}  // namespace

LzmaController::buffer LzmaController::compress(const buffer& input)
{
  buffer out(lzma_stream_buffer_bound(input.size()));
  std::size_t out_pos = 0;

  const lzma_ret rc =
      lzma_easy_buffer_encode(PRESET, LZMA_CHECK_CRC64, nullptr, input.data(),
                              input.size(), out.data(), &out_pos, out.size());

  if (rc != LZMA_OK) {
    LOGE("liblzma compression failed with code " << rc);
    return {};
  }

  out.resize(out_pos);

  LOGT("Compressed " << input.size() << " bytes into " << out.size());

  return out;
}

LzmaController::buffer LzmaController::uncompress(const buffer& input)
{
  buffer out;

  if (input.empty()) {
    return out;
  }

  lzma_stream strm = LZMA_STREAM_INIT;
  if (lzma_stream_decoder(&strm, UINT64_MAX, 0) != LZMA_OK) {
    LOGE("liblzma decoder initialization failed");
    return {};
  }

  strm.next_in = input.data();
  strm.avail_in = input.size();

  std::array<std::uint8_t, CHUNK> chunk{};
  lzma_ret rc = LZMA_OK;
  do {
    strm.next_out = chunk.data();
    strm.avail_out = chunk.size();
    rc = lzma_code(&strm, LZMA_FINISH);
    if (rc != LZMA_OK && rc != LZMA_STREAM_END) {
      lzma_end(&strm);
      LOGE("liblzma decompression failed with code " << rc);
      return {};
    }
    out.insert(out.end(), chunk.data(),
               chunk.data() + (chunk.size() - strm.avail_out));
  } while (rc != LZMA_STREAM_END);

  lzma_end(&strm);

  LOGT("Decompressed " << input.size() << " bytes into " << out.size());

  return out;
}

LzmaController::LzmaControllerPtr LzmaController::create()
{
  return std::make_shared<LzmaController>();
}

}  // namespace lzmai
