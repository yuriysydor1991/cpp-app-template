#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

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

  const auto& data = curl->download(project_decls::PROJECT_HOME_URL);

  if (!curl->last_response_successful()) {
    ctx->push_error("Fail to download the " + project_decls::PROJECT_HOME_URL +
                    " URL data.");
    LOGE("Fail to download the "
         << project_decls::PROJECT_HOME_URL
         << " URL data, HTTP status code: " << curl->last_response_code());
    return INVALID;
  }

  LOGI("Downloaded " << data.size() << " bytes of the "
                     << project_decls::PROJECT_HOME_URL << " URL data");

  std::cout.write(data.data(), static_cast<std::streamsize>(data.size()));
  std::cout << std::endl;

  return 0;
}

}  // namespace app
