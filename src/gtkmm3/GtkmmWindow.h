#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMWINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMWINDOW_CLASS_H

#include <memory>

#include "src/gtkmm3/gtkmm_includes.h"

namespace templateGtkmm
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

  inline static constexpr const char* const logo_res_path =
      "/ua/org/kytok/template/gtkmm3/resources/images/kytok.org.ua-logo.png";

  Glib::RefPtr<Gio::Resource> resources{nullptr};

  Gtk::VBox box;

  Gtk::Label headerText;
  Gtk::Label explanationText;
  Gtk::Image image;
};

}  // namespace templateGtkmm

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMWINDOW_CLASS_H
