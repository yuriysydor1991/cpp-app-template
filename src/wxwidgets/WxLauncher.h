#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WXLAUNCHER_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WXLAUNCHER_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace wxwi
{

/**
 * @brief Runs the native wxWidgets application event loop.
 *
 * This is the single link-time seam that pulls in the wxWidgets library: the
 * declaration is wxWidgets free and the definition lives in the wxWidgets
 * dependent app/WxApp.cpp translation unit. The component tests provide their
 * own definition of this function, so the WxWidgetsController orchestration may
 * be built and run without the wxWidgets library and without launching a GUI.
 *
 * @param ctx The application context, which stop flag ends the event loop.
 * @param argc The command line arguments count (forwarded to wxEntry).
 * @param argv The command line arguments array (forwarded to wxEntry).
 *
 * @return Returns the wxWidgets application exit status (0 on success).
 */
int run_wx_application(std::shared_ptr<::app::ApplicationContext> ctx,
                       int& argc, char**& argv);

}  // namespace wxwi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WXLAUNCHER_H
