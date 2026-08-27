#include "src/WCSLIB/WCSLIBController.h"

#include <wcs.h>
#include <wcshdr.h>

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "src/log/log.h"

namespace wcslibi
{

namespace
{

/// @brief The wcspih call reports through the wcshdr_errmsg table and the
/// rest of the calls below report through the wcs_errmsg one.
constexpr const int WCSHDR_MESSAGES = WCSHDRERR_BAD_TABULAR_PARAMS + 1;
constexpr const int WCS_MESSAGES = WCSERR_UNSET + 1;

/// @brief Do not report the rejected keyrecords into the standard error.
constexpr const int REPORTING_SILENT = 0;

}  // namespace

WCSLIBController::~WCSLIBController()
{
  // Not the release call: it is a virtual one, so a destructor gains nothing
  // from it.
  if (parsed != nullptr) {
    wcsvfree(&count, &parsed);
  }
}

bool WCSLIBController::parse(const context& ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid FITS context provided");
    return false;
  }

  release();

  const std::string& header = ctx->get_header();

  const int records = static_cast<int>(header.size() / KEYRECORD_LENGTH);

  if (records == 0) {
    LOGE("The given FITS header holds no complete keyrecord");
    return false;
  }

  // The parser takes a modifiable buffer, although it only rewrites it for
  // the negative reporting values, which the silent one is not.
  std::string buffer{header};

  status = wcspih(buffer.data(), records, WCSHDR_all, REPORTING_SILENT,
                  &rejected, &count, &parsed);

  if (!succeeded("parse the FITS header", wcshdr_errmsg, WCSHDR_MESSAGES)) {
    return false;
  }

  if (count == 0) {
    LOGE("The given FITS header declares no coordinate representation");
    return false;
  }

  LOGT("Parsed " << count << " coordinate representation(s) out of " << records
                 << " keyrecord(s), rejecting " << rejected << " of them");

  return select(0);
}

bool WCSLIBController::select(const int index)
{
  status = 0;
  selected = nullptr;

  if (parsed == nullptr || index < 0 || index >= count) {
    LOGE("No coordinate representation of the " << index << " index parsed");
    return false;
  }

  selected = parsed + index;

  status = wcsset(selected);

  if (!succeeded("set the coordinate representation up", wcs_errmsg,
                 WCS_MESSAGES)) {
    selected = nullptr;
    return false;
  }

  return true;
}

void WCSLIBController::release()
{
  if (parsed != nullptr) {
    wcsvfree(&count, &parsed);
  }

  error.clear();

  parsed = nullptr;
  selected = nullptr;
  count = 0;
  rejected = 0;
  status = 0;
}

bool WCSLIBController::is_ready() const { return selected != nullptr; }

int WCSLIBController::get_representations_count() const { return count; }

int WCSLIBController::get_axes_count() const
{
  return selected == nullptr ? 0 : selected->naxis;
}

std::string WCSLIBController::get_axis_type(const int axis) const
{
  if (selected == nullptr || axis < 0 || axis >= selected->naxis) {
    LOGE("No axis of the " << axis << " index in the selected representation");
    return {};
  }

  return selected->ctype[axis];
}

WCSLIBController::coordinates WCSLIBController::to_world(
    const coordinates& pixel)
{
  if (!prepare(pixel)) {
    return {};
  }

  const int axes = selected->naxis;

  coordinates world(pixel.size());
  coordinates intermediate(pixel.size());

  double phi = 0.0;
  double theta = 0.0;
  int converted = 0;

  status = wcsp2s(selected, 1, axes, pixel.data(), intermediate.data(), &phi,
                  &theta, world.data(), &converted);

  if (!succeeded("convert the pixel coordinate into the world one", wcs_errmsg,
                 WCS_MESSAGES)) {
    return {};
  }

  return world;
}

WCSLIBController::coordinates WCSLIBController::to_pixel(
    const coordinates& world)
{
  if (!prepare(world)) {
    return {};
  }

  const int axes = selected->naxis;

  coordinates pixel(world.size());
  coordinates intermediate(world.size());

  double phi = 0.0;
  double theta = 0.0;
  int converted = 0;

  status = wcss2p(selected, 1, axes, world.data(), &phi, &theta,
                  intermediate.data(), pixel.data(), &converted);

  if (!succeeded("convert the world coordinate into the pixel one", wcs_errmsg,
                 WCS_MESSAGES)) {
    return {};
  }

  return pixel;
}

int WCSLIBController::get_rejected_count() const { return rejected; }

int WCSLIBController::last_status() const { return status; }

std::string WCSLIBController::last_error() const { return error; }

bool WCSLIBController::prepare(const coordinates& given)
{
  status = 0;

  if (selected == nullptr) {
    LOGE("No coordinate representation is selected");
    return false;
  }

  if (given.size() != static_cast<coordinates::size_type>(selected->naxis)) {
    LOGE("Got " << given.size()
                << " coordinate element(s) while the selected representation "
                   "holds "
                << selected->naxis << " axes");
    return false;
  }

  return true;
}

bool WCSLIBController::succeeded(const std::string& action,
                                 const char* const* messages,
                                 const int messagesCount)
{
  error = status >= 0 && status < messagesCount ? messages[status] : "";

  if (status != 0) {
    LOGE("Fail to " << action << ": " << error);
    return false;
  }

  LOGT("Managed to " << action);

  return true;
}

WCSLIBControllerPtr WCSLIBController::create()
{
  return std::make_shared<WCSLIBController>();
}

}  // namespace wcslibi
