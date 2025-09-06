#include "src/converters/ApplicationContext2LibraryContext.h"

#include <cassert>
#include <memory>

#include "LibraryContext.h"
#include "src/app/ApplicationContext.h"

namespace converters
{

bool ApplicationContext2LibraryContext::convert(
    std::shared_ptr<ApplicationContext> appctx, LibraryContextPtr libctx)
{
  assert(appctx != nullptr);
  assert(libctx != nullptr);

  if (appctx == nullptr) {
    return false;
  }

  if (libctx == nullptr) {
    return false;
  }

  /// @brief Place here ApplicationContext -> LibraryContext necessary data
  /// transfer in order to library work properly.
  return true;
}

}  // namespace converters
