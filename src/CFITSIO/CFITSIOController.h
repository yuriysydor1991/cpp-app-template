#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H

#include <fitsio.h>

#include <memory>
#include <string>
#include <tuple>
#include <vector>

/**
 * @brief The CFITSIO adaptor subsystem namespace.
 */
namespace cfitsioi
{

/**
 * @brief The CFITSIO two dimensional image reader and writer class.
 *
 * A single instance holds a single open FITS file at a time. Every call
 * reports it's outcome through the return value and leaves the CFITSIO status
 * code of the performed call in the last_status accessor, so nothing throws.
 */
class CFITSIOController
{
 public:
  /// @brief The pixels of a whole image, row by row.
  using pixels_buffer = std::vector<double>;

  /// @brief The image width and the image height, in pixels.
  using image_size = std::tuple<long, long>;

  using CFITSIOControllerPtr = std::shared_ptr<CFITSIOController>;

  virtual ~CFITSIOController();
  CFITSIOController() = default;
  CFITSIOController(const CFITSIOController&) = delete;
  CFITSIOController(CFITSIOController&&) = delete;

  /**
   * @brief Opens an already existing FITS file and moves onto it's first
   * image.
   *
   * @param path The file to open. The whole CFITSIO extended file name syntax
   * is welcome here, so an "image.fits[2]" alike image selector works too.
   * @param writable Pass true to open the file for the writing as well.
   *
   * @return Returns true when the file has been opened.
   */
  virtual bool open(const std::string& path, const bool writable = false);

  /**
   * @brief Creates a FITS file holding a single double precision image of the
   * given size and leaves it open for the writing. An already existing file of
   * the same path gets overwritten.
   *
   * @param path The file to create.
   * @param size The width and the height of the image to create.
   *
   * @return Returns true when the file and it's image have been created.
   */
  virtual bool create_image(const std::string& path, const image_size& size);

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
   * @brief Reads the whole open image into the internal pixels buffer.
   *
   * @return Returns the pixels buffer, which is empty in case of any error.
   */
  virtual pixels_buffer& read();

  /**
   * @brief Writes the given pixels over the whole open image.
   *
   * @param pixels The pixels to write, as many of them as the open image
   * holds.
   *
   * @return Returns true when the pixels have been written.
   */
  virtual bool write(const pixels_buffer& pixels);

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
   * @brief Gives the buffer holding the pixels fetched by the last read call.
   *
   * @note This is the internal buffer accessor and not an image reading call.
   * Use the read one to perform it.
   */
  virtual pixels_buffer& get();

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

  pixels_buffer pbuff;
  fitsfile* fits{nullptr};
  int status{0};
};

using CFITSIOControllerPtr = CFITSIOController::CFITSIOControllerPtr;

}  // namespace cfitsioi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H
