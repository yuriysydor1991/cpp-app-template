#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "project-global-decls.h"
#include "src/log/log.h"

namespace app
{

int Application::run(ApplicationContextPtr ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  LOGI("Your " << project_decls::PROJECT_NAME
               << " application implementation goes here!");

  return 0;
}

}  // namespace app
