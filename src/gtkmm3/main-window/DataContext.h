#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MAIN_WINDOW_COMPONENT_MAINWINDOWDATACONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MAIN_WINDOW_COMPONENT_MAINWINDOWDATACONTEXT_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/gtkmm3/gtkmm_includes.h"

namespace Gtkmm3i::main_window
{

#ifndef GTKMM_APP_RESOURCES_PREFIX
#define GTKMM_APP_RESOURCES_PREFIX "/ua/org/kytok/template/gtkmm3/glade"
#endif  // GTKMM_APP_RESOURCES_PREFIXs

/**
 * @brief The root GTKmm3 window data context class.
 */
class DataContext
{
 public:
  virtual ~DataContext() = default;
  DataContext() = default;

  inline static constexpr const char* const UI_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/GtkmmWindow.ui";
  inline static constexpr const char* const logo_res_path =
      GTKMM_APP_RESOURCES_PREFIX
      "/resources/images/"
      "kytok.org.ua-logo.png";
  inline static constexpr const char* const main_css_res_path =
      GTKMM_APP_RESOURCES_PREFIX
      "/resources/css/"
      "main-window.css";

  inline static constexpr const char* const main_window_id = "main_window";
  inline static constexpr const char* const central_image_id = "random_image";
};

}  // namespace Gtkmm3i::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MAIN_WINDOW_COMPONENT_MAINWINDOWDATACONTEXT_CLASS_H
