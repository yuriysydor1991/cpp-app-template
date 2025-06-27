#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMWINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMWINDOW_CLASS_H

#include <memory>

#include "src/gtkmm3/gtkmm_includes.h"

#ifndef GTKMM_APP_RESOURCES_PREFIX
#define GTKMM_APP_RESOURCES_PREFIX "/ua/org/kytok/template/gtkmm3"
#endif  // GTKMM_APP_RESOURCES_PREFIX

namespace Gtkmm3i
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

 protected:
  const std::string& get_default_title();

 private:
  void prepare_header_label();
  void prepare_random_logo();
  void prepare_global_resource();
  void prepare_widgets();
  void prepare_css();

  inline static constexpr const char* const logo_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/images/kytok.org.ua-logo.png";
  inline static constexpr const char* const main_css_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/css/main-window.css";

  Glib::RefPtr<Gio::Resource> resources{nullptr};

  Gtk::VBox box;

  Gtk::Label headerText;
  Gtk::Label explanationText;
  Gtk::Image image;
};

}  // namespace Gtkmm3i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMWINDOW_CLASS_H
