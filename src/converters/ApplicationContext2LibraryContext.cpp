#include "src/converters/ApplicationContext2LibraryContext.h"

#include <memory>

#include "LibraryContext.h"
#include "src/app/ApplicationContext.h"

namespace converters
{

bool ApplicationContext2LibraryContext::convert(
    std::shared_ptr<ApplicationContext> appctx,
    std::shared_ptr<LibraryContext> libctx)
{
  /// @brief Place here ApplicationContext -> LibraryContext necessary data
  /// transfer in order to library work properly.
  return true;
}

}  // namespace converters
