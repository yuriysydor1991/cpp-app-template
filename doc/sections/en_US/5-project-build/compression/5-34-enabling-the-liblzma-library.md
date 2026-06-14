## Enabling the liblzma library

In order to enable the [liblzma](https://tukaani.org/xz/) (XZ Utils) compression library (`.xz` / LZMA2, legacy `.lzma`) for the project by using the installed system one or by fetching it through the available connection set an `ON` value to the `ENABLE_LIBLZMA` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_LIBLZMA=ON
```

See the `cmake/enablers/compression/template-project-liblzma-enabler.cmake` module for the targets (`LibLZMA::LibLZMA` for a system install, `liblzma` for the FetchContent build) to link to your targets of interest.

### Compressing data of interest (copy-paste examples)

After `ENABLE_LIBLZMA=ON` and linking a liblzma target (e.g. `target_link_libraries(${PROJECT_BINARY_NAME} LibLZMA::LibLZMA)`), include `<lzma.h>` and copy-paste any of the snippets below.

The quickest way to compress a buffer of interest — one-shot, in-memory, into the `.xz` (LZMA2) container:

```cpp
#include <lzma.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

// preset: 0..9, optionally OR-ed with LZMA_PRESET_EXTREME. LZMA_CHECK_CRC64 is
// the .xz default integrity check.
std::vector<uint8_t> xz_compress(const std::vector<uint8_t>& input,
                                 uint32_t preset = LZMA_PRESET_DEFAULT)
{
  std::vector<uint8_t> out(lzma_stream_buffer_bound(input.size()));
  std::size_t out_pos = 0;
  lzma_ret rc = lzma_easy_buffer_encode(preset, LZMA_CHECK_CRC64, nullptr,
                                        input.data(), input.size(), out.data(),
                                        &out_pos, out.size());
  if (rc != LZMA_OK) {
    throw std::runtime_error("lzma_easy_buffer_encode failed");
  }
  out.resize(out_pos);
  return out;
}

// The decoded size is not stored in the .xz stream, so grow the output buffer
// and retry while the decoder reports it ran out of room.
std::vector<uint8_t> xz_uncompress(const std::vector<uint8_t>& input)
{
  std::vector<uint8_t> out(input.size() * 4 + 1024);
  for (;;) {
    std::size_t in_pos = 0;
    std::size_t out_pos = 0;
    uint64_t memlimit = UINT64_MAX;
    lzma_ret rc = lzma_stream_buffer_decode(&memlimit, 0, nullptr, input.data(),
                                            &in_pos, input.size(), out.data(),
                                            &out_pos, out.size());
    if (rc == LZMA_OK) {
      out.resize(out_pos);
      return out;
    }
    if (rc == LZMA_BUF_ERROR) {  // output buffer too small, grow and retry
      out.resize(out.size() * 2);
      continue;
    }
    throw std::runtime_error("lzma_stream_buffer_decode failed");
  }
}
```

### Streaming compression

For data that should not be held in memory all at once, drive the `lzma_stream`
encoder in a chunked loop (the same shape works for decoding via
`lzma_stream_decoder()`):

```cpp
#include <lzma.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

std::vector<uint8_t> xz_compress_stream(const std::vector<uint8_t>& input,
                                        uint32_t preset = LZMA_PRESET_DEFAULT)
{
  lzma_stream strm = LZMA_STREAM_INIT;
  if (lzma_easy_encoder(&strm, preset, LZMA_CHECK_CRC64) != LZMA_OK) {
    throw std::runtime_error("lzma_easy_encoder failed");
  }

  strm.next_in = input.data();  // next_in is a const uint8_t*, no cast needed
  strm.avail_in = input.size();

  std::vector<uint8_t> out;
  uint8_t buf[BUFSIZ];
  lzma_ret rc = LZMA_OK;
  do {
    strm.next_out = buf;
    strm.avail_out = sizeof(buf);
    rc = lzma_code(&strm, LZMA_FINISH);
    out.insert(out.end(), buf, buf + (sizeof(buf) - strm.avail_out));
  } while (rc == LZMA_OK);
  lzma_end(&strm);

  if (rc != LZMA_STREAM_END) {
    throw std::runtime_error("lzma_code failed");
  }
  return out;
}
```

**`.xz` vs legacy `.lzma`.** The snippets above produce the modern `.xz`
container (recommended). For the legacy `.lzma` (LZMA1 alone) format use
`lzma_alone_encoder()` / `lzma_alone_decoder()` with an `lzma_options_lzma`
filled by `lzma_lzma_preset()`. The `.xz` format adds integrity checks and
multiple-filter support and should be preferred for new data.
