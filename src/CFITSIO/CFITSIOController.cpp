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
  // A failure has nobody left to report itself to here, so the handle gets
  // released and nothing else.
  if (fits != nullptr) {
    fits_close_file(fits, &status);
  }
}

bool CFITSIOController::read(const context& ctx)
{
  if (!valid(ctx) || !open(ctx, false)) {
    return false;
  }

  return release(read_header(ctx) &&
                 (ctx->get_read_header_only() || read_image(ctx)));
}

bool CFITSIOController::write(const context& ctx)
{
  if (!valid(ctx)) {
    return false;
  }

  // The header only write updates an already existing file, while the whole
  // one replaces it with a freshly created image.
  const bool headerOnly = ctx->get_write_header_only();

  if (!(headerOnly ? open(ctx, true) : create(ctx))) {
    return false;
  }

  return release((headerOnly || write_image(ctx)) && write_keywords(ctx));
}

int CFITSIOController::last_status() const { return status; }

std::string CFITSIOController::last_error() const
{
  char text[FLEN_ERRMSG] = {};

  fits_get_errstatus(status, text);

  return text;
}

bool CFITSIOController::open(const context& ctx, const bool writable)
{
  const std::string path = ctx->get_path();

  assert(!path.empty());

  if (path.empty()) {
    LOGE("The FITS context carries no file path");
    return false;
  }

  status = 0;

  fits_open_file(&fits, path.c_str(), writable ? READWRITE : READONLY, &status);

  return succeeded("open the " + path + " FITS file");
}

bool CFITSIOController::create(const context& ctx)
{
  const std::string path = ctx->get_path();
  const auto [width, height] = ctx->get_image_size();

  assert(!path.empty());

  if (path.empty() || width <= 0 || height <= 0) {
    LOGE("Invalid FITS image requested: '" << path << "' of " << width << "x"
                                           << height);
    return false;
  }

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

bool CFITSIOController::read_header(const context& ctx)
{
  ctx->set_header({});
  ctx->set_hdu_count(0);
  ctx->get_keywords().clear();

  if (!prepare()) {
    return false;
  }

  int hdus = 0;

  fits_get_num_hdus(fits, &hdus, &status);

  if (!succeeded("count the FITS file HDUs")) {
    return false;
  }

  ctx->set_hdu_count(hdus);

  char* records = nullptr;
  int recordsCount = 0;

  fits_hdr2str(fits, 0, nullptr, 0, &records, &recordsCount, &status);

  const bool fetched = succeeded("read the FITS header");

  if (fetched && records != nullptr) {
    ctx->set_header(records);
  }

  // The CFITSIO allocates that buffer itself, so it releases it as well, and
  // it skips the release for a non zero status left behind by the call above.
  int releaseStatus = 0;

  fits_free_memory(records, &releaseStatus);

  return fetched && read_keywords(ctx);
}

bool CFITSIOController::read_keywords(const context& ctx)
{
  int count = 0;

  fits_get_hdrspace(fits, &count, nullptr, &status);

  if (!succeeded("count the FITS header keywords")) {
    return false;
  }

  auto& keywords = ctx->get_keywords();

  for (int index = 1; index <= count; ++index) {
    char name[FLEN_KEYWORD] = {};
    char value[FLEN_VALUE] = {};

    fits_read_keyn(fits, index, name, value, nullptr, &status);

    if (!succeeded("read a FITS header keyword")) {
      return false;
    }

    // A commentary keyword carries no value at all, so there is nothing of it
    // to keep, and a text valued one arrives quoted, so it gets fetched once
    // again by it's name, which is the call that unquotes it.
    if (name[0] == '\0' || value[0] == '\0') {
      continue;
    }

    if (value[0] == '\'') {
      fits_read_key(fits, TSTRING, name, value, nullptr, &status);

      if (!succeeded(std::string{"unquote the "} + name + " FITS keyword")) {
        return false;
      }
    }

    keywords[name] = value;
  }

  return true;
}

bool CFITSIOController::read_image(const context& ctx)
{
  auto& pixels = ctx->get_pixels();

  pixels.clear();
  ctx->set_image_size({0, 0});

  if (!prepare()) {
    return false;
  }

  int bitpix = 0;
  int naxis = 0;
  long naxes[IMAGE_AXES] = {0, 0};

  fits_get_img_param(fits, IMAGE_AXES, &bitpix, &naxis, naxes, &status);

  if (!succeeded("read the FITS image parameters")) {
    return false;
  }

  if (naxis != IMAGE_AXES) {
    LOGE("The FITS file holds a " << naxis
                                  << " axes image instead of a two "
                                     "dimensional one");
    return false;
  }

  ctx->set_image_size({naxes[0], naxes[1]});

  const LONGLONG count = static_cast<LONGLONG>(naxes[0]) * naxes[1];

  if (count <= 0) {
    LOGE("The FITS image holds no pixel at all");
    return false;
  }

  pixels.resize(static_cast<CFITSIOContext::pixels_buffer::size_type>(count));

  // The null value and the null flag pointers are the optional ones and stay
  // omitted here, which turns the undefined pixels check off.
  fits_read_img(fits, TDOUBLE, 1, count, nullptr, pixels.data(), nullptr,
                &status);

  if (!succeeded("read the FITS image pixels")) {
    pixels.clear();
    return false;
  }

  return true;
}

bool CFITSIOController::write_keywords(const context& ctx)
{
  if (!prepare()) {
    return false;
  }

  for (const auto& [name, value] : ctx->get_keywords()) {
    fits_update_key(fits, TSTRING, name.c_str(),
                    const_cast<char*>(value.c_str()), nullptr, &status);

    if (!succeeded("write the " + name + " FITS keyword")) {
      return false;
    }
  }

  for (const auto& [name, value] : ctx->get_numeric_keywords()) {
    double written = value;

    fits_update_key(fits, TDOUBLE, name.c_str(), &written, nullptr, &status);

    if (!succeeded("write the " + name + " FITS keyword")) {
      return false;
    }
  }

  return true;
}

bool CFITSIOController::write_image(const context& ctx)
{
  if (!prepare()) {
    return false;
  }

  const auto& pixels = ctx->get_pixels();
  const auto [width, height] = ctx->get_image_size();

  const LONGLONG expected = static_cast<LONGLONG>(width) * height;
  const LONGLONG given = static_cast<LONGLONG>(pixels.size());

  if (expected <= 0 || given != expected) {
    LOGE("The context carries " << given << " pixels while it's image holds "
                                << expected);
    return false;
  }

  // The CFITSIO reads the pixels through a pointer of it's own, so the
  // constness gets dropped right here and nowhere else.
  fits_write_img(fits, TDOUBLE, 1, given, const_cast<double*>(pixels.data()),
                 &status);

  return succeeded("write the FITS image pixels");
}

bool CFITSIOController::release(const bool done)
{
  const int performed = status;

  status = 0;

  if (fits != nullptr) {
    fits_close_file(fits, &status);
    fits = nullptr;
  }

  const bool closed = succeeded("close the FITS file");

  if (!done) {
    status = performed;
  }

  return done && closed;
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

bool CFITSIOController::valid(const context& ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid FITS context provided");
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
