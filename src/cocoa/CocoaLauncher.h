#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COCOALAUNCHER_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COCOALAUNCHER_H

namespace cocoa
{

/**
 * @brief Runs the native macOS Cocoa / AppKit application.
 *
 * This is the single link-time seam that pulls in the Cocoa framework: the
 * declaration is Cocoa free and the definition lives in the macOS-only
 * Objective-C++ app/CocoaApp.mm translation unit (and in the cross-platform
 * app/CocoaAppStub.cpp on non-Apple hosts). The component tests provide their
 * own definition of this function, so the CocoaIniter orchestration may be
 * built and run without AppKit and without launching a GUI.
 *
 * @param argc The command line arguments count.
 * @param argv The command line arguments array.
 *
 * @return Returns the application exit status (0 on success).
 */
int run_cocoa_application(int& argc, char**& argv);

}  // namespace cocoa

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_COCOALAUNCHER_H
