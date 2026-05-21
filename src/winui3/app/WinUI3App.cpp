#include "src/winui3/app/WinUI3App.h"

#include "project-global-decls.h"
#include "src/winui3/WinUI3Launcher.h"
#include "src/winui3/helpers/WindowConfig.h"
#include "src/winui3/main-window/WinUI3MainWindow.h"

namespace mux = winrt::Microsoft::UI::Xaml;

namespace winui3
{

int run_winui_application(int& /*argc*/, char**& /*argv*/)
{
  // Bootstrap the Windows App SDK runtime for an unpackaged executable and hand
  // control to the WinUI 3 XAML application loop. Application::Start owns the
  // message loop until the last window is closed.
  winrt::init_apartment(winrt::apartment_type::single_threaded);

  mux::Application::Start(
      [](auto&&) { winrt::make<winui3::app::WinUI3App>(); });

  return 0;
}

}  // namespace winui3

namespace winui3::app
{

void WinUI3App::OnLaunched(mux::LaunchActivatedEventArgs const& /*args*/)
{
  // Merge the default WinUI 3 control styles - the code-only equivalent of the
  // generated App.xaml <XamlControlsResources/> resource merge.
  Resources().MergedDictionaries().Append(
      winrt::Microsoft::UI::Xaml::Controls::XamlControlsResources{});

  const helpers::WindowConfig config{project_decls::PROJECT_NAME,
                                     project_decls::PROJECT_BUILD_VERSION};

  main_window::WinUI3MainWindow mainWindow{config};
  window = mainWindow.window();
  window.Activate();
}

}  // namespace winui3::app
