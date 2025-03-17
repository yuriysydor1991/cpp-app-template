#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H

#include <memory>

#include "src/gtkmm3/gtkmm_includes.h"

namespace templateGtkmm3
{

/**
 * @brief The root GTKmm window class to show
 * templated GUI window.
 */
class GtkmmIniter
{
 public:
  virtual ~GtkmmIniter() = default;
  GtkmmIniter() = default;

  virtual int run(int& argc, char**& argv);

 protected:
  void prepare_widgets();

 private:
  inline static constexpr const char* const UI_res_path =
      "/ua/org/kytok/template/gtkmm3/GtkmmWindow.glade";
  inline static constexpr const char* const logo_res_path =
      "/ua/org/kytok/template/gtkmm3/resources/images/kytok.org.ua-logo.png";

  void prepare_random_logo();

  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::Window* window{nullptr};
  Gtk::Image* image{nullptr};
};

}  // namespace templateGtkmm3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
