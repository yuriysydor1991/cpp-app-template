#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMWINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMWINDOW_CLASS_H

#include <memory>

#include "src/gtkmm/gtkmm_includes.h"

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
  virtual const std::string& get_default_title();

 private:
  void prepare_random_logo();

  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::Box* box{nullptr};
  Gtk::Image* image{nullptr};
};

}  // namespace templateGtkmm

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMWINDOW_CLASS_H
