#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H

#include <memory>

#include "ILib.h"
#include "LibraryContext.h"

namespace lib0impl
{

class LibMain : public templatelib0::ILib
{
 public:
  using LibMainPtr = std::shared_ptr<LibMain>;
  using LibraryContextPtr = templatelib0::LibraryContextPtr;

  virtual ~LibMain() = default;
  LibMain() = default;

  MOCK_METHOD(bool, libcall, (LibraryContextPtr ctx), (override));

  static LibMainPtr create();
};

using LibMainPtr = LibMain::LibMainPtr;

}  // namespace lib0impl

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H
