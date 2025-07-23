#include "src/app/Application.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>

#include "project-global-decls.h"
#include "src/CURL/CURLController.h"
#include "src/log/log.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  auto curl = curli::CURLController::create();

  assert(curl != nullptr);

  auto data = curl->download(project_decls::PROJECT_HOME_URL);

  LOGI("Downloaded " << project_decls::PROJECT_HOME_URL
                     << " URL data: " << std::string(data.begin(), data.end()));

  return 0;
}

}  // namespace app
