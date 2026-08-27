#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H

#include <fitsio.h>

#include <memory>
#include <string>

#include "src/CFITSIO/CFITSIOContext.h"

/**
 * @brief The CFITSIO adaptor subsystem namespace.
 */
namespace cfitsioi
{

/**
 * @brief The CFITSIO two dimensional image reader and writer class.
 *
 * The whole surface of it is a read and a write call, both of them taking a
 * single CFITSIOContext and nothing else: every parameter of an operation and
 * every result of it lives in that context. The file gets opened and closed
 * inside a call, so an instance holds no data and no file of it's own between
 * the calls.
 *
 * Nothing throws: both of the calls report their outcome through the return
 * value and leave the CFITSIO status code of the failed call in the
 * last_status accessor.
 */
class CFITSIOController
{
 public:
  /// @brief The context both of the custom components operate by.
  using context = CFITSIOContextPtr;

  using CFITSIOControllerPtr = std::shared_ptr<CFITSIOController>;

  virtual ~CFITSIOController();
  CFITSIOController() = default;
  CFITSIOController(const CFITSIOController&) = delete;
  CFITSIOController(CFITSIOController&&) = delete;

  /**
   * @brief Reads the FITS file the context points at into that very context:
   * it's header keyrecords, it's keywords, it's HDUs count and, unless the
   * context asks for the header alone, it's image size and pixels.
   *
   * @param ctx The context carrying the file path and the
   * CFITSIOContext::get_read_header_only flag.
   *
   * @return Returns true when everything asked for has been read.
   */
  virtual bool read(const context& ctx);

  /**
   * @brief Writes the context out into the FITS file it points at: it's
   * keywords and, unless the context asks for the header alone, a freshly
   * created image of it's size holding it's pixels.
   *
   * An already existing file gets overwritten by a whole write and updated in
   * place by a header only one.
   *
   * @param ctx The context carrying the file path, the data to write and the
   * CFITSIOContext::get_write_header_only flag.
   *
   * @return Returns true when everything has been written.
   */
  virtual bool write(const context& ctx);

  /// @brief Gives the CFITSIO status code of the last performed call, where
  /// the zero one reports a success.
  virtual int last_status() const;

  /// @brief Gives the CFITSIO description of the last_status value.
  virtual std::string last_error() const;

  static CFITSIOControllerPtr create();

 private:
  /// @brief Opens the file of the context, for the writing as well when asked.
  bool open(const context& ctx, const bool writable);

  /// @brief Creates the file of the context holding a double precision image
  /// of the size it carries, overwriting an already existing one.
  bool create(const context& ctx);

  /// @brief Reads the header keyrecords, the keywords and the HDUs count.
  bool read_header(const context& ctx);

  /// @brief Reads the keywords carrying a value into the context, unquoting
  /// the text ones.
  bool read_keywords(const context& ctx);

  /// @brief Reads the image size and it's pixels into the context.
  bool read_image(const context& ctx);

  /// @brief Writes the keywords of the context into the open header.
  bool write_keywords(const context& ctx);

  /// @brief Writes the pixels of the context over the open image.
  bool write_image(const context& ctx);

  /**
   * @brief Closes the held file, keeping the status of the operation which
   * has led here, since the closing one would hide it.
   *
   * @param done The outcome of that operation.
   *
   * @return Returns true when both the operation and the closing succeeded.
   */
  bool release(const bool done);

  /**
   * @brief Drops the status of the previous call and tells whether a file is
   * open, so every call above starts with a clean CFITSIO status.
   */
  bool prepare();

  /// @brief Tells whether the given context is there to operate by.
  static bool valid(const context& ctx);

  /**
   * @brief Logs the CFITSIO error of the just performed call, if any.
   *
   * @param action The description of the performed call for the log message.
   *
   * @return Returns true when the call left no error behind.
   */
  bool succeeded(const std::string& action) const;

  /// @brief The FITS images of the controller are the two dimensional ones.
  inline static constexpr const int IMAGE_AXES = 2;

  fitsfile* fits{nullptr};
  int status{0};
};

using CFITSIOControllerPtr = CFITSIOController::CFITSIOControllerPtr;

}  // namespace cfitsioi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H
