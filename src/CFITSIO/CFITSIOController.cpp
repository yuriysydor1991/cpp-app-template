#include "src/CFITSIO/CFITSIOController.h"

#include <cassert>
#include <memory>
#include <string>
#include <tuple>

#include "src/log/log.h"

namespace cfitsioi
{

CFITSIOController::~CFITSIOController()
{
  // Not the close call: it is a virtual one, so a destructor gains nothing
  // from it, while a failure has nobody left to report itself to anyway.
  if (fits != nullptr) {
    fits_close_file(fits, &status);
  }
}

bool CFITSIOController::open(const std::string& path, const bool writable)
{
  assert(!path.empty());

  if (path.empty()) {
    LOGE("No FITS file path provided");
    return false;
  }

  close();

  status = 0;

  fits_open_file(&fits, path.c_str(), writable ? READWRITE : READONLY, &status);

  return succeeded("open the " + path + " FITS file");
}

bool CFITSIOController::create_image(const std::string& path,
                                     const image_size& size)
{
  const auto [width, height] = size;

  assert(!path.empty());

  if (path.empty() || width <= 0 || height <= 0) {
    LOGE("Invalid FITS image requested: '" << path << "' of " << width << "x"
                                           << height);
    return false;
  }

  close();

  status = 0;

  // The exclamation mark prefix is the CFITSIO way of overwriting an already
  // existing file instead of failing on it.
  fits_create_file(&fits, ("!" + path).c_str(), &status);

  if (!succeeded("create the " + path + " FITS file")) {
    return false;
  }

  long naxes[IMAGE_AXES] = {width, height};

  fits_create_img(fits, DOUBLE_IMG, IMAGE_AXES, naxes, &status);

  return succeeded("create the image of the " + path + " FITS file");
}

bool CFITSIOController::close()
{
  if (fits == nullptr) {
    return true;
  }

  status = 0;

  fits_close_file(fits, &status);

  fits = nullptr;

  return succeeded("close the FITS file");
}

bool CFITSIOController::is_open() const { return fits != nullptr; }

CFITSIOController::image_size CFITSIOController::get_image_size()
{
  if (!prepare()) {
    return {0, 0};
  }

  int bitpix = 0;
  int naxis = 0;
  long naxes[IMAGE_AXES] = {0, 0};

  fits_get_img_param(fits, IMAGE_AXES, &bitpix, &naxis, naxes, &status);

  if (!succeeded("read the FITS image parameters") || naxis != IMAGE_AXES) {
    return {0, 0};
  }

  return {naxes[0], naxes[1]};
}

int CFITSIOController::get_hdu_count()
{
  if (!prepare()) {
    return 0;
  }

  int hdus = 0;

  fits_get_num_hdus(fits, &hdus, &status);

  if (!succeeded("count the FITS file HDUs")) {
    return 0;
  }

  return hdus;
}

CFITSIOController::pixels_buffer& CFITSIOController::read()
{
  pbuff.clear();

  const auto [width, height] = get_image_size();
  const LONGLONG pixels = static_cast<LONGLONG>(width) * height;

  if (pixels <= 0) {
    LOGE("No two dimensional FITS image to read");
    return pbuff;
  }

  pbuff.resize(static_cast<pixels_buffer::size_type>(pixels));

  // The null value and the null flag pointers are the optional ones and stay
  // omitted here, which turns the undefined pixels check off.
  fits_read_img(fits, TDOUBLE, 1, pixels, nullptr, pbuff.data(), nullptr,
                &status);

  if (!succeeded("read the FITS image pixels")) {
    pbuff.clear();
  }

  return pbuff;
}

bool CFITSIOController::write(const pixels_buffer& pixels)
{
  const auto [width, height] = get_image_size();
  const LONGLONG expected = static_cast<LONGLONG>(width) * height;
  const LONGLONG given = static_cast<LONGLONG>(pixels.size());

  if (expected <= 0 || given != expected) {
    LOGE("Got " << given << " pixels while the open FITS image holds "
                << expected);
    return false;
  }

  // The CFITSIO reads the pixels through a pointer of it's own, so the
  // constness gets dropped right here and nowhere else.
  fits_write_img(fits, TDOUBLE, 1, given, const_cast<double*>(pixels.data()),
                 &status);

  return succeeded("write the FITS image pixels");
}

std::string CFITSIOController::read_keyword(const std::string& name)
{
  assert(!name.empty());

  if (!prepare() || name.empty()) {
    return {};
  }

  char value[FLEN_VALUE] = {};

  fits_read_key(fits, TSTRING, name.c_str(), value, nullptr, &status);

  if (!succeeded("read the " + name + " FITS keyword")) {
    return {};
  }

  return value;
}

bool CFITSIOController::write_keyword(const std::string& name,
                                      const std::string& value,
                                      const std::string& comment)
{
  assert(!name.empty());

  if (!prepare() || name.empty()) {
    return false;
  }

  fits_update_key(fits, TSTRING, name.c_str(), const_cast<char*>(value.c_str()),
                  comment.empty() ? nullptr : comment.c_str(), &status);

  return succeeded("write the " + name + " FITS keyword");
}

CFITSIOController::pixels_buffer& CFITSIOController::get() { return pbuff; }

int CFITSIOController::last_status() const { return status; }

std::string CFITSIOController::last_error() const
{
  char text[FLEN_ERRMSG] = {};

  fits_get_errstatus(status, text);

  return text;
}

bool CFITSIOController::prepare()
{
  status = 0;

  if (fits == nullptr) {
    LOGE("No FITS file is open");
    return false;
  }

  return true;
}

bool CFITSIOController::succeeded(const std::string& action) const
{
  if (status != 0) {
    LOGE("Fail to " << action << ": " << last_error());
    return false;
  }

  LOGT("Managed to " << action);

  return true;
}

CFITSIOControllerPtr CFITSIOController::create()
{
  return std::make_shared<CFITSIOController>();
}

}  // namespace cfitsioi
