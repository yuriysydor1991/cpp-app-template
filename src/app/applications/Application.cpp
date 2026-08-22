#include "src/app/applications/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "fontawesome-decls.h"
#include "src/fontawesome/icons/FontAwesomeIcons.h"
#include "src/fontawesome/resources/FontAwesomeGResourcePath.h"
#include "src/fontawesome/resources/FontAwesomeQtResourcePath.h"
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

  const auto icons = fontawesome::FontAwesomeIcons::create();

  assert(icons != nullptr);

  LOGI("Font Awesome Free " << fontawesome_decls::FONTAWESOME_VERSION
                            << " carries " << icons->count() << " icons at "
                            << fontawesome_decls::FONTAWESOME_SVGS_DIR);

  const auto icon = icons->find(DEMO_ICON_STYLE, DEMO_ICON_NAME);

  if (icon == nullptr) {
    LOGW("No " << DEMO_ICON_STYLE << "/" << DEMO_ICON_NAME
               << " icon in the Font Awesome checkout in use");
    return 0;
  }

  LOGI("The " << icon->alias() << " icon file: " << icon->filePath());
  LOGI("... embedded into the Qt resources: "
       << fontawesome::FontAwesomeQtResourcePath::create()->of(icon));
  LOGI("... embedded into the GResource ones: "
       << fontawesome::FontAwesomeGResourcePath::create()->of(icon));

  return 0;
}

}  // namespace app
