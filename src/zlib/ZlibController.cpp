#include "src/zlib/ZlibController.h"

#include <zlib.h>

#include <array>
#include <memory>

#include "src/log/log.h"

namespace zlibi
{

namespace
{
constexpr std::size_t CHUNK = 16384U;
}  // namespace

ZlibController::buffer ZlibController::compress(const buffer& input)
{
  z_stream zs{};
  if (deflateInit(&zs, Z_BEST_COMPRESSION) != Z_OK) {
    LOGE("zlib deflateInit failed");
    return {};
  }

  zs.next_in = const_cast<Bytef*>(input.data());
  zs.avail_in = static_cast<uInt>(input.size());

  buffer out;
  std::array<unsigned char, CHUNK> chunk{};
  int rc = Z_OK;
  do {
    zs.next_out = chunk.data();
    zs.avail_out = static_cast<uInt>(chunk.size());
    rc = deflate(&zs, Z_FINISH);
    out.insert(out.end(), chunk.data(),
               chunk.data() + (chunk.size() - zs.avail_out));
  } while (rc == Z_OK);

  deflateEnd(&zs);

  if (rc != Z_STREAM_END) {
    LOGE("zlib deflate failed with code " << rc);
    return {};
  }

  LOGT("Compressed " << input.size() << " bytes into " << out.size());

  return out;
}

ZlibController::buffer ZlibController::uncompress(const buffer& input)
{
  buffer out;

  if (input.empty()) {
    return out;
  }

  z_stream zs{};
  if (inflateInit(&zs) != Z_OK) {
    LOGE("zlib inflateInit failed");
    return {};
  }

  zs.next_in = const_cast<Bytef*>(input.data());
  zs.avail_in = static_cast<uInt>(input.size());

  std::array<unsigned char, CHUNK> chunk{};
  int rc = Z_OK;
  do {
    zs.next_out = chunk.data();
    zs.avail_out = static_cast<uInt>(chunk.size());
    rc = inflate(&zs, Z_NO_FLUSH);
    if (rc != Z_OK && rc != Z_STREAM_END) {
      inflateEnd(&zs);
      LOGE("zlib inflate failed with code " << rc);
      return {};
    }
    out.insert(out.end(), chunk.data(),
               chunk.data() + (chunk.size() - zs.avail_out));
  } while (rc != Z_STREAM_END);

  inflateEnd(&zs);

  LOGT("Decompressed " << input.size() << " bytes into " << out.size());

  return out;
}

bool ZlibController::compress_to_file(const std::string& path,
                                      const buffer& input)
{
  gzFile file = gzopen(path.c_str(), "wb");
  if (file == nullptr) {
    LOGE("Failed to open the gzip file for writing: " << path);
    return false;
  }

  if (!input.empty() &&
      gzwrite(file, input.data(), static_cast<unsigned>(input.size())) == 0) {
    gzclose(file);
    LOGE("Failed to write the gzip file: " << path);
    return false;
  }

  if (gzclose(file) != Z_OK) {
    LOGE("Failed to finalize the gzip file: " << path);
    return false;
  }

  LOGT("Wrote " << input.size() << " bytes into the gzip file " << path);

  return true;
}

ZlibController::buffer ZlibController::uncompress_from_file(
    const std::string& path)
{
  buffer out;

  gzFile file = gzopen(path.c_str(), "rb");
  if (file == nullptr) {
    LOGE("Failed to open the gzip file for reading: " << path);
    return out;
  }

  std::array<unsigned char, CHUNK> chunk{};
  int read = 0;
  while ((read = gzread(file, chunk.data(), static_cast<unsigned>(chunk.size()))) >
         0) {
    out.insert(out.end(), chunk.data(), chunk.data() + read);
  }

  if (read < 0) {
    gzclose(file);
    LOGE("Failed to read the gzip file: " << path);
    return {};
  }

  gzclose(file);

  LOGT("Read " << out.size() << " bytes from the gzip file " << path);

  return out;
}

ZlibController::ZlibControllerPtr ZlibController::create()
{
  return std::make_shared<ZlibController>();
}

}  // namespace zlibi
