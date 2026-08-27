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
 * A single instance holds a single open FITS file at a time and carries no
 * data of it's own: it reads into the given CFITSIOContext and writes out of
 * it. Every call reports it's outcome through the return value and leaves the
 * CFITSIO status code of the performed call in the last_status accessor, so
 * nothing throws.
 */
class CFITSIOController
{
 public:
  /// @brief The context both of the custom components operate by.
  using context = CFITSIOContextPtr;

  using pixels_buffer = CFITSIOContext::pixels_buffer;
  using image_size = CFITSIOContext::image_size;

  using CFITSIOControllerPtr = std::shared_ptr<CFITSIOController>;

  virtual ~CFITSIOController();
  CFITSIOController() = default;
  CFITSIOController(const CFITSIOController&) = delete;
  CFITSIOController(CFITSIOController&&) = delete;

  /**
   * @brief Opens the already existing FITS file the context points at and
   * moves onto it's first image.
   *
   * @param ctx The context carrying the file path. The whole CFITSIO extended
   * file name syntax is welcome there, so an "image.fits[2]" alike image
   * selector works too.
   * @param writable Pass true to open the file for the writing as well.
   *
   * @return Returns true when the file has been opened.
   */
  virtual bool open(const context& ctx, const bool writable = false);

  /**
   * @brief Creates a FITS file holding a single double precision image of the
   * path and the size the context carries and leaves it open for the writing.
   * An already existing file of the same path gets overwritten.
   *
   * @param ctx The context carrying the file path and the image size.
   *
   * @return Returns true when the file and it's image have been created.
   */
  virtual bool create_image(const context& ctx);

  /// @brief Writes the pending changes out and closes the held file, if any.
  virtual bool close();

  virtual bool is_open() const;

  /**
   * @brief Gives the width and the height of the open image, both of them
   * zeroed while no file is open or the open one holds no image.
   */
  virtual image_size get_image_size();

  /// @brief Gives the count of the HDUs (the blocks a FITS file is built of)
  /// of the open file, zero on any error.
  virtual int get_hdu_count();

  /**
   * @brief Reads the whole open image into the pixels buffer of the context
   * and refills the image size it carries.
   *
   * @param ctx The context to read into.
   *
   * @return Returns true when the pixels have been read.
   */
  virtual bool read(const context& ctx);

  /**
   * @brief Writes the pixels the context carries over the whole open image.
   *
   * @param ctx The context to write out of. It must carry as many pixels as
   * the open image holds.
   *
   * @return Returns true when the pixels have been written.
   */
  virtual bool write(const context& ctx);

  /**
   * @brief Reads the whole header of the open file into the context as the
   * FITS keyrecords string of exactly 80 characters per record, the very form
   * the WCSLIBController takes.
   *
   * @param ctx The context to read into.
   *
   * @return Returns true when the header has been read.
   */
  virtual bool read_header(const context& ctx);

  /**
   * @brief Reads a header keyword of the open file as a string.
   *
   * @param name The keyword name, "OBJECT" or "BITPIX", for example.
   *
   * @return Returns the keyword value, empty in case of any error.
   */
  virtual std::string read_keyword(const std::string& name);

  /**
   * @brief Writes a header keyword into the open file, replacing the already
   * present one of the same name.
   *
   * @param name The keyword name to write.
   * @param value The keyword value to write.
   * @param comment The optional keyword description.
   *
   * @return Returns true when the keyword has been written.
   */
  virtual bool write_keyword(const std::string& name, const std::string& value,
                             const std::string& comment = {});

  /**
   * @brief Writes a floating point header keyword into the open file,
   * replacing the already present one of the same name. The string overload
   * above quotes it's value instead, which the numeric keyword readers (the
   * WCS parsers among them) reject.
   *
   * @param name The keyword name to write.
   * @param value The keyword value to write.
   * @param comment The optional keyword description.
   *
   * @return Returns true when the keyword has been written.
   */
  virtual bool write_keyword(const std::string& name, const double value,
                             const std::string& comment = {});

  /// @brief Gives the CFITSIO status code of the last performed call, where
  /// the zero one reports a success.
  virtual int last_status() const;

  /// @brief Gives the CFITSIO description of the last_status value.
  virtual std::string last_error() const;

  static CFITSIOControllerPtr create();

 private:
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
