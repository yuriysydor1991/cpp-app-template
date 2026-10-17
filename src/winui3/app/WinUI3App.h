#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3APP_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3APP_CLASS_H

#include "src/winui3/winui3_includes.h"

namespace winui3::application
{

/**
 * @brief The default WinUI 3 application object.
 *
 * Derives from the C++/WinRT ApplicationT<> CRTP base (the code-only equivalent
 * of the generated App.xaml) and creates/activates the main window on launch.
 * Without the XAML compiler the application itself provides the XAML type
 * metadata of the WinUI 3 controls (IXamlMetadataProvider), which the merged
 * XamlControlsResources styles need.
 */
class WinUI3App
    : public winrt::Microsoft::UI::Xaml::ApplicationT<
          WinUI3App, winrt::Microsoft::UI::Xaml::Markup::IXamlMetadataProvider>
{
 public:
  void OnLaunched(
      winrt::Microsoft::UI::Xaml::LaunchActivatedEventArgs const& args);

  winrt::Microsoft::UI::Xaml::Markup::IXamlType GetXamlType(
      winrt::Windows::UI::Xaml::Interop::TypeName const& type);
  winrt::Microsoft::UI::Xaml::Markup::IXamlType GetXamlType(
      winrt::hstring const& fullName);
  winrt::com_array<winrt::Microsoft::UI::Xaml::Markup::XmlnsDefinition>
  GetXmlnsDefinitions();

 private:
  winrt::Microsoft::UI::Xaml::Window window{nullptr};
  winrt::Microsoft::UI::Xaml::XamlTypeInfo::XamlControlsXamlMetaDataProvider
      provider;
};

}  // namespace winui3::application

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3APP_CLASS_H
