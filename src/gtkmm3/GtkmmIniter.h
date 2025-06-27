#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/gtkmm3/gtkmm_includes.h"

namespace Gtkmm3i
{

#ifndef GTKMM_APP_RESOURCES_PREFIX
#define GTKMM_APP_RESOURCES_PREFIX "/ua/org/kytok/template/gtkmm3/glade"
#endif  // GTKMM_APP_RESOURCES_PREFIXs

/**
 * @brief The root GTKmm window class to show
 * templated GUI window.
 */
class GtkmmIniter
{
 public:
  virtual ~GtkmmIniter() = default;
  GtkmmIniter() = default;

  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);

 protected:
  void prepare_widgets();
  static void load_css();

 private:
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

  void prepare_random_logo();

  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::Window* window{nullptr};
  Gtk::Image* image{nullptr};

  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace Gtkmm3i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
