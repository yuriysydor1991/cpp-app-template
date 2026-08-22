#include "src/gtkmm4/main-window/AdwaitaWindow.h"

#include <cassert>
#include <string>

#include "project-global-decls.h"
#include "src/log/log.h"

namespace Gtkmm4i::main_window
{

Gtk::Window* AdwaitaWindow::build(const Glib::RefPtr<Gtk::Application>& app)
{
  assert(app);

  if (!app) {
    LOGE("No valid application instance provided");
    return nullptr;
  }

  window = ADW_APPLICATION_WINDOW(
      adw_application_window_new(GTK_APPLICATION(app->gobj())));

  assert(window != nullptr);

  if (window == nullptr) {
    LOGE("Fail to create the AdwApplicationWindow instance");
    return nullptr;
  }

  GtkWindow* gtkWindow = GTK_WINDOW(window);

  gtk_window_set_title(gtkWindow, get_default_title().c_str());
  gtk_window_set_default_size(gtkWindow, default_width, default_height);
  gtk_widget_set_size_request(GTK_WIDGET(window), min_width, min_height);

  // The AdwToolbarView is what makes the header bar a part of the window
  // content instead of a separate title bar. It is the recommended libadwaita
  // window layout and the reason to use an AdwApplicationWindow at all.
  GtkWidget* toolbarView = adw_toolbar_view_new();

  adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbarView),
                               create_header_bar());
  adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbarView),
                               create_status_page());

  adw_application_window_set_content(window, toolbarView);

  prepare_css();

  gtk_window_present(gtkWindow);

  LOGD("The libadwaita application window is presented");

  return Glib::wrap(gtkWindow);
}

GtkWidget* AdwaitaWindow::create_header_bar()
{
  GtkWidget* headerBar = adw_header_bar_new();

  // The window title widget follows the AdwToolbarView, so it fades together
  // with the header bar and keeps the adaptive libadwaita behaviour.
  GtkWidget* windowTitle = adw_window_title_new(
      get_default_title().c_str(), project_decls::PROJECT_BUILD_COMMIT.c_str());

  adw_header_bar_set_title_widget(ADW_HEADER_BAR(headerBar), windowTitle);

  return headerBar;
}

GtkWidget* AdwaitaWindow::create_status_page()
{
  GtkWidget* statusPage = adw_status_page_new();

  adw_status_page_set_title(ADW_STATUS_PAGE(statusPage),
                            get_default_title().c_str());
  adw_status_page_set_description(ADW_STATUS_PAGE(statusPage),
                                  get_default_description().c_str());

  // The logo comes from the very same GResource bundle the plain gtkmm4 branch
  // uses, so the resource wiring stays untouched by the libadwaita switch.
  GtkWidget* logo = gtk_image_new_from_resource(logo_res_path);

  gtk_image_set_pixel_size(GTK_IMAGE(logo), 128);

  adw_status_page_set_child(ADW_STATUS_PAGE(statusPage), logo);

  return statusPage;
}

void AdwaitaWindow::prepare_css()
{
  auto css_provider = Gtk::CssProvider::create();

  try {
    css_provider->load_from_resource(main_css_res_path);
  }
  catch (const Glib::Error& ex) {
    LOGE("Failed to load CSS: " << ex.what());
    return;
  }

  auto display = Gdk::Display::get_default();

  if (!display) {
    LOGE("No default display to apply the stylesheet on");
    return;
  }

  Gtk::StyleContext::add_provider_for_display(
      display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

const std::string& AdwaitaWindow::get_default_title()
{
  static const std::string default_title =
      std::string{project_decls::PROJECT_NAME} + " " +
      project_decls::PROJECT_BUILD_VERSION;

  return default_title;
}

const std::string& AdwaitaWindow::get_default_description()
{
  static const std::string default_description =
      "Replace the AdwStatusPage of the AdwaitaWindow class with the real "
      "application widgets";

  return default_description;
}

}  // namespace Gtkmm4i::main_window
