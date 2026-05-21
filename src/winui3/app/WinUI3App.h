#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3APP_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3APP_CLASS_H

#include "src/winui3/winui3_includes.h"

namespace winui3::app
{

/**
 * @brief The default WinUI 3 application object.
 *
 * Derives from the C++/WinRT ApplicationT<> CRTP base (the code-only equivalent
 * of the generated App.xaml) and creates/activates the main window on launch.
 */
class WinUI3App
    : public winrt::Microsoft::UI::Xaml::ApplicationT<WinUI3App>
{
 public:
  void OnLaunched(
      winrt::Microsoft::UI::Xaml::LaunchActivatedEventArgs const& args);

 private:
  winrt::Microsoft::UI::Xaml::Window window{nullptr};
};

}  // namespace winui3::app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3APP_CLASS_H
