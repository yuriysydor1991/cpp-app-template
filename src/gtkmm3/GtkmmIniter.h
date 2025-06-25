#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/gtkmm3/gtkmm_includes.h"

namespace Gtkmm3i
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

  virtual int run(std::shared_ptr<app::ApplicationContext> nactx);

 protected:
  void prepare_widgets();

 private:
  inline static constexpr const char* const UI_res_path =
      "/ua/org/kytok/template/gtkmm3/glade/GtkmmWindow.ui";
  inline static constexpr const char* const logo_res_path =
      "/ua/org/kytok/template/gtkmm3/glade/resources/images/"
      "kytok.org.ua-logo.png";

  void prepare_random_logo();

  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::Window* window{nullptr};
  Gtk::Image* image{nullptr};

  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace Gtkmm3i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
