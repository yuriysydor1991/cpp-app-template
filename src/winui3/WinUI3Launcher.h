#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3LAUNCHER_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3LAUNCHER_H

namespace winui3
{

/**
 * @brief Runs the native WinUI 3 application.
 *
 * This is the single link-time seam that pulls in the WinUI 3 + C++/WinRT
 * (Windows App SDK) stack: the declaration is WinUI free and the definition
 * lives in the Windows-only app/WinUI3App.cpp translation unit (and in the
 * cross-platform app/WinUI3AppStub.cpp on non-Windows hosts). The component
 * tests provide their own definition of this function, so the WinUI3Initer
 * orchestration may be built and run without the Windows App SDK and without
 * launching a GUI.
 *
 * @param argc The command line arguments count.
 * @param argv The command line arguments array.
 *
 * @return Returns the application exit status (0 on success).
 */
int run_winui_application(int& argc, char**& argv);

}  // namespace winui3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3LAUNCHER_H
