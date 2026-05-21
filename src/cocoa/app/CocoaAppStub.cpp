#include <iostream>

#include "project-global-decls.h"
#include "src/cocoa/CocoaLauncher.h"
#include "src/cocoa/helpers/WindowConfig.h"
#include "src/log/log.h"

namespace cocoa
{

// Non-macOS definition of the Cocoa launch seam. Cocoa / AppKit is a macOS-only
// framework, so off macOS the executable still builds and runs but reports the
// GUI is unavailable (printing the portable WindowConfig content) instead of
// opening a window. This keeps the portable parts cross-platform buildable and
// testable.
int run_cocoa_application(int& /*argc*/, char**& /*argv*/)
{
  const helpers::WindowConfig config{project_decls::PROJECT_NAME,
                                     project_decls::PROJECT_BUILD_VERSION};

  LOGI("Cocoa / AppKit GUI is only available on Apple macOS");

  std::cout << config.title() << "\n"
            << config.header_text() << "\n"
            << config.explanation_text() << std::endl;

  return 0;
}

}  // namespace cocoa
