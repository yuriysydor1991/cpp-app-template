#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTEXT_CLASS_H

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace cfitsioi
{

/**
 * @brief The class that holds everything both of the custom components
 * operate by: the FITS file to work with, the data read out of it and the
 * data to write into it.
 *
 * The CFITSIOController takes it's every parameter out of an instance of the
 * current class and fills it's every result into it, while the
 * WCSLIBController takes the header out of the very same instance to convert
 * the image coordinates. Neither of the components reaches for the other one:
 * the data alone travels between them.
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

  /// @brief The header keywords carrying a text value, by their names.
  using keywords_map = std::map<std::string, std::string>;

  /// @brief The header keywords carrying a numeric value, by their names.
  using numeric_keywords_map = std::map<std::string, double>;

  using CFITSIOContextPtr = std::shared_ptr<CFITSIOContext>;

  virtual ~CFITSIOContext() = default;
  CFITSIOContext() = default;

  /// @brief Provides the path of the FITS file to operate on.
  const std::string& get_path() const;

  /// @brief Sets the path of the FITS file to operate on. The read call opens
  /// it and the write one creates or updates it.
  void set_path(const std::string& newValue);

  /// @brief Provides the image width and height, both of them zeroed until a
  /// read or a set call fills them.
  const image_size& get_image_size() const;

  /// @brief Sets the image width and height for the write call to create the
  /// image by. The read call refills the value out of the file.
  void set_image_size(const image_size& newValue);

  /// @brief Provides the image pixels. The reference is a modifiable one,
  /// since the CFITSIOController reads the image straight into it and copies
  /// no whole image that way.
  pixels_buffer& get_pixels();

  /// @brief Provides the image pixels of an unmodifiable context.
  const pixels_buffer& get_pixels() const;

  /// @brief Sets the image pixels for the write call to put into the image.
  void set_pixels(const pixels_buffer& newValue);

  /// @brief Provides the FITS header keyrecords string, empty until a read or
  /// a set call fills it. That is the form the WCSLIBController takes.
  const std::string& get_header() const;

  /// @brief Sets the FITS header keyrecords string for the WCSLIBController
  /// to convert the coordinates by.
  void set_header(const std::string& newValue);

  /// @brief Provides the text valued header keywords. The reference is a
  /// modifiable one, since the read call fills it straight in.
  keywords_map& get_keywords();

  /// @brief Provides the text valued header keywords of an unmodifiable
  /// context.
  const keywords_map& get_keywords() const;

  /// @brief Sets the text valued header keywords for the write call to put
  /// into the header. The read call refills them out of the file, unquoted.
  void set_keywords(const keywords_map& newValue);

  /// @brief Provides the numeric header keywords the write call puts into the
  /// header unquoted, the way the WCS parsers need them. The read call fills
  /// no numeric keyword, since a read one arrives as it's text.
  const numeric_keywords_map& get_numeric_keywords() const;

  /// @brief Sets the numeric header keywords for the write call to put into
  /// the header.
  void set_numeric_keywords(const numeric_keywords_map& newValue);

  /// @brief Provides the count of the HDUs (the blocks a FITS file is built
  /// of) the read call has found, zero until then.
  int get_hdu_count() const;

  /// @brief Sets the count of the HDUs of the file.
  void set_hdu_count(const int newValue);

  /// @brief Tells whether the read call skips the image and fetches the
  /// header alone.
  bool get_read_header_only() const;

  /// @brief Raise it to make the read call fetch the header alone, which
  /// leaves the pixels of the context untouched.
  void set_read_header_only(const bool newValue);

  /// @brief Tells whether the write call updates the header of an already
  /// existing file instead of creating a whole image.
  bool get_write_header_only() const;

  /// @brief Raise it to make the write call update the header of an already
  /// existing file, which leaves the pixels of that file untouched.
  void set_write_header_only(const bool newValue);

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

  /// @brief The text valued header keywords. See the
  /// CFITSIOContext::set_keywords setter.
  keywords_map mkeywords;

  /// @brief The numeric header keywords. See the
  /// CFITSIOContext::set_numeric_keywords setter.
  numeric_keywords_map mnumeric_keywords;

  /// @brief The HDUs count of the file. See the
  /// CFITSIOContext::set_hdu_count setter.
  int mhdu_count{0};

  /// @brief The header only read flag. See the
  /// CFITSIOContext::set_read_header_only setter.
  bool mread_header_only{false};

  /// @brief The header only write flag. See the
  /// CFITSIOContext::set_write_header_only setter.
  bool mwrite_header_only{false};
};

using CFITSIOContextPtr = CFITSIOContext::CFITSIOContextPtr;

}  // namespace cfitsioi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTEXT_CLASS_H
