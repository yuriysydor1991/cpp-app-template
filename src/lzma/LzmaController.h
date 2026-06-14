#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LZMACONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LZMACONTROLLER_CLASS_H

#include <memory>
#include <vector>

/**
 * @brief The liblzma (XZ Utils) compression adaptor subsystem namespace.
 */
namespace lzmai
{

/**
 * @brief A small liblzma wrapper that hides the streaming boilerplate behind a
 * couple of simple in-memory compress / uncompress methods.
 *
 * The methods produce / consume the modern `.xz` (LZMA2) container. All methods
 * log and return an empty result on a liblzma error instead of throwing, so
 * they are trivial to call.
 */
class LzmaController
{
 public:
  using buffer = std::vector<unsigned char>;
  using LzmaControllerPtr = std::shared_ptr<LzmaController>;

  virtual ~LzmaController() = default;
  LzmaController() = default;
  LzmaController(const LzmaController&) = delete;
  LzmaController& operator=(const LzmaController&) = delete;

  /**
   * @brief Compresses a buffer in memory into the `.xz` (LZMA2) container.
   *
   * @param input The data to compress (may be empty).
   *
   * @return The compressed bytes, or an empty buffer on a liblzma error.
   */
  virtual buffer compress(const buffer& input);

  /**
   * @brief Decompresses a `.xz` buffer produced by compress().
   *
   * @param input The compressed data.
   *
   * @return The original bytes, or an empty buffer on a liblzma error or empty
   * input.
   */
  virtual buffer uncompress(const buffer& input);

  /**
   * @brief Creates a ready to use controller instance.
   *
   * @return The created controller.
   */
  static LzmaControllerPtr create();
};

using LzmaControllerPtr = LzmaController::LzmaControllerPtr;

}  // namespace lzmai

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LZMACONTROLLER_CLASS_H
