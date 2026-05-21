#include "src/winui3/main-window/WinUI3MainWindow.h"

namespace mux = winrt::Microsoft::UI::Xaml;
namespace muxc = winrt::Microsoft::UI::Xaml::Controls;

namespace winui3::main_window
{

WinUI3MainWindow::WinUI3MainWindow(const helpers::WindowConfig& config)
    : win{mux::Window{}}
{
  win.Title(winrt::to_hstring(config.title()));

  build_content(config);
}

mux::Window WinUI3MainWindow::window() const { return win; }

void WinUI3MainWindow::build_content(const helpers::WindowConfig& config)
{
  muxc::StackPanel panel{};
  panel.HorizontalAlignment(mux::HorizontalAlignment::Center);
  panel.VerticalAlignment(mux::VerticalAlignment::Center);
  panel.Spacing(12);

  muxc::TextBlock header{};
  header.Text(winrt::to_hstring(config.header_text()));
  header.FontSize(28);
  header.HorizontalAlignment(mux::HorizontalAlignment::Center);

  muxc::TextBlock explanation{};
  explanation.Text(winrt::to_hstring(config.explanation_text()));
  explanation.HorizontalAlignment(mux::HorizontalAlignment::Center);

  panel.Children().Append(header);
  panel.Children().Append(explanation);

  win.Content(panel);
}

}  // namespace winui3::main_window
