#include <iostream>

#include "project-global-decls.h"
#include "src/log/log.h"
#include "src/winui3/WinUI3Launcher.h"
#include "src/winui3/helpers/WindowConfig.h"

namespace winui3
{

// Non-Windows definition of the WinUI 3 launch seam. WinUI 3 + C++/WinRT is a
// Windows-only stack, so off Windows the executable still builds and runs but
// reports the GUI is unavailable (printing the portable WindowConfig content)
// instead of opening a window. This keeps the portable parts of the project
// cross-platform buildable and testable.
int run_winui_application(int& /*argc*/, char**& /*argv*/)
{
  const helpers::WindowConfig config{project_decls::PROJECT_NAME,
                                     project_decls::PROJECT_BUILD_VERSION};

  LOGI("WinUI 3 GUI is only available on Microsoft Windows");

  std::cout << config.title() << "\n"
            << config.header_text() << "\n"
            << config.explanation_text() << std::endl;

  return 0;
}

}  // namespace winui3
