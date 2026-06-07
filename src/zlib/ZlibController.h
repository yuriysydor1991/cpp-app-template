#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ZLIBCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ZLIBCONTROLLER_CLASS_H

#include <memory>
#include <string>
#include <vector>

/**
 * @brief The zlib compression adaptor subsystem namespace.
 */
namespace zlibi
{

/**
 * @brief A small zlib wrapper that hides the streaming boilerplate behind a few
 * simple compress / uncompress methods (in memory and to / from gzip files).
 *
 * The in-memory methods use the zlib (deflate) wrapper; the file methods use the
 * gzip (.gz) container. All methods log and return an empty result / false on a
 * zlib error instead of throwing, so they are trivial to call.
 */
class ZlibController
{
 public:
  using buffer = std::vector<unsigned char>;
  using ZlibControllerPtr = std::shared_ptr<ZlibController>;

  virtual ~ZlibController() = default;
  ZlibController() = default;
  ZlibController(const ZlibController&) = delete;
  ZlibController& operator=(const ZlibController&) = delete;

  /**
   * @brief Compresses a buffer in memory with the zlib (deflate) wrapper.
   *
   * @param input The data to compress (may be empty).
   *
   * @return The compressed bytes, or an empty buffer on a zlib error.
   */
  virtual buffer compress(const buffer& input);

  /**
   * @brief Decompresses a buffer produced by compress().
   *
   * @param input The compressed data.
   *
   * @return The original bytes, or an empty buffer on a zlib error or empty
   * input.
   */
  virtual buffer uncompress(const buffer& input);

  /**
   * @brief Compresses a buffer and stores it as a gzip (.gz) file.
   *
   * @param path The destination file path.
   * @param input The data to compress.
   *
   * @return Returns true on success and false on any I/O or zlib error.
   */
  virtual bool compress_to_file(const std::string& path, const buffer& input);

  /**
   * @brief Reads and decompresses a gzip (.gz) file.
   *
   * @param path The source file path.
   *
   * @return The decompressed bytes, or an empty buffer on any I/O or zlib error.
   */
  virtual buffer uncompress_from_file(const std::string& path);

  /**
   * @brief Creates a ready to use controller instance.
   *
   * @return The created controller.
   */
  static ZlibControllerPtr create();
};

using ZlibControllerPtr = ZlibController::ZlibControllerPtr;

}  // namespace zlibi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ZLIBCONTROLLER_CLASS_H
