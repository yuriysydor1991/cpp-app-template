#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H

#include <gmock/gmock.h>

#include <memory>

#include "ILib.h"
#include "LibraryContext.h"
#include "project-lib-decls.h"

namespace TEMPLATE_LIB_IMPL_NAMESPACE
{

class LibMain : public TEMPLATE_LIB_NAMESPACE::ILib
{
 public:
  using LibMainPtr = std::shared_ptr<LibMain>;
  using LibraryContextPtr = TEMPLATE_LIB_NAMESPACE::LibraryContextPtr;

  ~LibMain() override = default;
  LibMain() = default;

  MOCK_METHOD(bool, libcall, (LibraryContextPtr ctx), (override));

  inline static LibMainPtr create() { return std::make_shared<LibMain>(); }
};

using LibMainPtr = LibMain::LibMainPtr;

}  // namespace TEMPLATE_LIB_IMPL_NAMESPACE

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LIBRARYMAIN_CLASS_H
