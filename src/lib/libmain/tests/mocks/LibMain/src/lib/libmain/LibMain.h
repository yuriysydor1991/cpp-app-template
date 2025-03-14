#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H

#include <gmock/gmock.h>

#include <memory>

#include "src/lib/facade/ILib.h"
#include "src/lib/facade/LibraryContext.h"

namespace lib0impl
{

class LibMain : public templatelib0::ILib
{
 public:
  virtual ~LibMain() = default;
  LibMain() = default;

  MOCK_METHOD(bool, libcall, (std::shared_ptr<LibraryContext> ctx), (override));
};

}  // namespace lib0impl

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H
