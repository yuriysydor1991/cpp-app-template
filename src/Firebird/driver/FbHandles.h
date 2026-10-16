#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FBHANDLES_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FBHANDLES_CLASS_H

#include <ibase.h>

namespace firebirdi::driver
{

/**
 * @brief Holds the native Firebird handles of the FbClient class, so that the
 * ibase.h header does not leak into the FbClient.h one.
 */
class FbHandles
{
 public:
  /// @brief The attached database handle, zero when not attached.
  isc_db_handle db{0};

  /// @brief The status vector of the latest native call.
  ISC_STATUS_ARRAY status{};
};

}  // namespace firebirdi::driver

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FBHANDLES_CLASS_H
