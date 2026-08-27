#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTEXT_CLASS_H

#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace cfitsioi
{

/**
 * @brief The class that holds the FITS data both of the custom components
 * operate by.
 *
 * The CFITSIOController reads a FITS file into it and writes the pixels it
 * holds back, while the WCSLIBController takes the header out of it to
 * convert the image coordinates. Neither of the components reaches for the
 * other one: the data alone travels between them, through an instance of the
 * current class.
 *
 * All the data members are private ones, so the held data is reachable
 * through the appropriate access methods only.
 */
class CFITSIOContext
{
 public:
  /// @brief The pixels of a whole image, row by row.
  using pixels_buffer = std::vector<double>;

  /// @brief The image width and the image height, in pixels.
  using image_size = std::tuple<long, long>;

  using CFITSIOContextPtr = std::shared_ptr<CFITSIOContext>;

  virtual ~CFITSIOContext() = default;
  CFITSIOContext() = default;

  /// @brief Provides the path of the FITS file to operate on.
  const std::string& get_path() const;

  /// @brief Sets the path of the FITS file to operate on. The
  /// CFITSIOController opens and creates the file of that very path.
  void set_path(const std::string& newValue);

  /// @brief Provides the image width and height, both of them zeroed until a
  /// read or a set call fills them.
  const image_size& get_image_size() const;

  /// @brief Sets the image width and height. The CFITSIOController creates
  /// the image of that very size and refills the value on every read.
  void set_image_size(const image_size& newValue);

  /// @brief Provides the image pixels. The reference is a modifiable one,
  /// since the CFITSIOController reads the image straight into it and copies
  /// no whole image that way.
  pixels_buffer& get_pixels();

  /// @brief Provides the image pixels of an unmodifiable context.
  const pixels_buffer& get_pixels() const;

  /// @brief Sets the image pixels for the CFITSIOController to write.
  void set_pixels(const pixels_buffer& newValue);

  /// @brief Provides the FITS header keyrecords string, empty until a read or
  /// a set call fills it.
  const std::string& get_header() const;

  /// @brief Sets the FITS header keyrecords string for the WCSLIBController
  /// to convert the coordinates by.
  void set_header(const std::string& newValue);

  static CFITSIOContextPtr create();

 private:
  /// @brief The FITS file path. See the CFITSIOContext::set_path setter.
  std::string mpath;

  /// @brief The image width and height. See the
  /// CFITSIOContext::set_image_size setter.
  image_size msize{0, 0};

  /// @brief The image pixels. See the CFITSIOContext::set_pixels setter.
  pixels_buffer mpixels;

  /// @brief The FITS header keyrecords. See the CFITSIOContext::set_header
  /// setter.
  std::string mheader;
};

using CFITSIOContextPtr = CFITSIOContext::CFITSIOContextPtr;

}  // namespace cfitsioi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTEXT_CLASS_H
