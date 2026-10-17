#include "src/winui3/app/WinUI3App.h"

#include <MddBootstrap.h>
#include <WindowsAppSDK-VersionInfo.h>

#include "project-global-decls.h"
#include "src/app/applications/IApplication.h"
#include "src/log/log.h"
#include "src/winui3/WinUI3Launcher.h"
#include "src/winui3/helpers/WindowConfig.h"
#include "src/winui3/main-window/WinUI3MainWindow.h"

namespace mux = winrt::Microsoft::UI::Xaml;

namespace winui3
{

int run_winui_application(int& /*argc*/, char**& /*argv*/)
{
  // The unpackaged executable has no package identity: the bootstrapper adds
  // the Windows App SDK framework package (the WinUI 3 runtime) to the process
  // before any Windows App SDK API is used.
  const PACKAGE_VERSION minVersion{WINDOWSAPPSDK_RUNTIME_VERSION_UINT64};

  const HRESULT bootstrapped = MddBootstrapInitialize2(
      WINDOWSAPPSDK_RELEASE_MAJORMINOR, WINDOWSAPPSDK_RELEASE_VERSION_TAG_W,
      minVersion, MddBootstrapInitializeOptions_OnNoMatch_ShowUI);

  if (FAILED(bootstrapped)) {
    LOGE("Failed to initialize the Windows App SDK runtime, HRESULT 0x"
         << std::hex << static_cast<unsigned long>(bootstrapped));
    return app::IApplication::INVALID;
  }

  // Hand control to the WinUI 3 XAML application loop. Application::Start owns
  // the message loop until the application exits.
  winrt::init_apartment(winrt::apartment_type::single_threaded);

  mux::Application::Start(
      [](auto&&) { winrt::make<winui3::application::WinUI3App>(); });

  MddBootstrapShutdown();

  return 0;
}

}  // namespace winui3

namespace winui3::application
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

mux::Markup::IXamlType WinUI3App::GetXamlType(
    winrt::Windows::UI::Xaml::Interop::TypeName const& type)
{
  return provider.GetXamlType(type);
}

mux::Markup::IXamlType WinUI3App::GetXamlType(winrt::hstring const& fullName)
{
  return provider.GetXamlType(fullName);
}

winrt::com_array<mux::Markup::XmlnsDefinition> WinUI3App::GetXmlnsDefinitions()
{
  return provider.GetXmlnsDefinitions();
}

}  // namespace winui3::application
