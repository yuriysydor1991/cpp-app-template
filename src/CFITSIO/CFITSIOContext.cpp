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

CFITSIOContext::keywords_map& CFITSIOContext::get_keywords()
{
  return mkeywords;
}

const CFITSIOContext::keywords_map& CFITSIOContext::get_keywords() const
{
  return mkeywords;
}

void CFITSIOContext::set_keywords(const keywords_map& newValue)
{
  mkeywords = newValue;
}

const CFITSIOContext::numeric_keywords_map&
CFITSIOContext::get_numeric_keywords() const
{
  return mnumeric_keywords;
}

void CFITSIOContext::set_numeric_keywords(const numeric_keywords_map& newValue)
{
  mnumeric_keywords = newValue;
}

int CFITSIOContext::get_hdu_count() const { return mhdu_count; }

void CFITSIOContext::set_hdu_count(const int newValue)
{
  mhdu_count = newValue;
}

bool CFITSIOContext::get_read_header_only() const { return mread_header_only; }

void CFITSIOContext::set_read_header_only(const bool newValue)
{
  mread_header_only = newValue;
}

bool CFITSIOContext::get_write_header_only() const
{
  return mwrite_header_only;
}

void CFITSIOContext::set_write_header_only(const bool newValue)
{
  mwrite_header_only = newValue;
}

CFITSIOContextPtr CFITSIOContext::create()
{
  return std::make_shared<CFITSIOContext>();
}

}  // namespace cfitsioi
