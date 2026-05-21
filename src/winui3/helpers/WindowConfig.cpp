#include "src/winui3/helpers/WindowConfig.h"

#include <string>

namespace winui3::helpers
{

WindowConfig::WindowConfig(const std::string& app_name,
                           const std::string& app_version)
    : window_title{app_name + " " + app_version},
      header{"Main WinUI 3 application"},
      explanation{
          "Replace the default window implementation in the WinUI3MainWindow class"}
{
}

const std::string& WindowConfig::title() const { return window_title; }

const std::string& WindowConfig::header_text() const { return header; }

const std::string& WindowConfig::explanation_text() const
{
  return explanation;
}

int WindowConfig::width() const { return window_width; }

int WindowConfig::height() const { return window_height; }

int WindowConfig::min_width() const { return window_min_width; }

int WindowConfig::min_height() const { return window_min_height; }

}  // namespace winui3::helpers
