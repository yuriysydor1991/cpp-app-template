#include "src/CFITSIO/CFITSIOContext.h"

#include <memory>
#include <string>

namespace cfitsioi
{

const std::string& CFITSIOContext::get_path() const { return mpath; }

void CFITSIOContext::set_path(const std::string& newValue) { mpath = newValue; }

const CFITSIOContext::image_size& CFITSIOContext::get_image_size() const
{
  return msize;
}

void CFITSIOContext::set_image_size(const image_size& newValue)
{
  msize = newValue;
}

CFITSIOContext::pixels_buffer& CFITSIOContext::get_pixels() { return mpixels; }

const CFITSIOContext::pixels_buffer& CFITSIOContext::get_pixels() const
{
  return mpixels;
}

void CFITSIOContext::set_pixels(const pixels_buffer& newValue)
{
  mpixels = newValue;
}

const std::string& CFITSIOContext::get_header() const { return mheader; }

void CFITSIOContext::set_header(const std::string& newValue)
{
  mheader = newValue;
}

CFITSIOContextPtr CFITSIOContext::create()
{
  return std::make_shared<CFITSIOContext>();
}

}  // namespace cfitsioi
