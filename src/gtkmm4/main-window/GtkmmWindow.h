#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H

#include <string>

#include "src/gtkmm4/gtkmm4_includes.h"

namespace Gtkmm4i::main_window
{

/**
 * @brief The root GTKmm window class to show
 * templated GUI window.
 */
class GtkmmWindow : public Gtk::Window
{
 public:
  virtual ~GtkmmWindow() = default;
  GtkmmWindow();

  bool init();

 protected:
  const std::string& get_default_title();

 private:
  void prepare_header_label();
  void prepare_random_logo();
  void prepare_widgets();
  void prepare_css();
  void pack_widgets();

  inline static constexpr const char* const logo_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/images/kytok.org.ua-logo.png";
  inline static constexpr const char* const main_css_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/css/main-window.css";
  inline static constexpr const char* const header_label_class = "header-label";

  Gtk::Box box;

  Gtk::Label headerText;
  Gtk::Label explanationText;
  Gtk::Image image;
};

}  // namespace Gtkmm4i::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM4WINDOW_CLASS_H
