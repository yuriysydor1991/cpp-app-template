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
  adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbarView), create_content());

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

GtkWidget* AdwaitaWindow::create_content()
{
  GtkWidget* content = gtk_box_new(GTK_ORIENTATION_VERTICAL, content_spacing);

  // Neither label expands, so the box hands them their natural height at the
  // very top and leaves everything below to the logo, which does expand.
  gtk_box_append(GTK_BOX(content), create_title_label());
  gtk_box_append(GTK_BOX(content), create_description_label());
  gtk_box_append(GTK_BOX(content), create_logo_picture());

  return content;
}

GtkWidget* AdwaitaWindow::create_title_label()
{
  GtkWidget* title = gtk_label_new(get_default_title().c_str());

  gtk_widget_add_css_class(title, title_style_class);

  gtk_label_set_wrap(GTK_LABEL(title), TRUE);
  gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);

  gtk_widget_set_valign(title, GTK_ALIGN_START);
  gtk_widget_set_margin_top(title, content_margin);
  gtk_widget_set_margin_start(title, content_margin);
  gtk_widget_set_margin_end(title, content_margin);

  return title;
}

GtkWidget* AdwaitaWindow::create_description_label()
{
  GtkWidget* description = gtk_label_new(get_default_description().c_str());

  gtk_widget_add_css_class(description, description_style_class);
  gtk_widget_add_css_class(description, dim_style_class);

  gtk_label_set_wrap(GTK_LABEL(description), TRUE);
  gtk_label_set_justify(GTK_LABEL(description), GTK_JUSTIFY_CENTER);

  gtk_widget_set_valign(description, GTK_ALIGN_START);
  gtk_widget_set_margin_start(description, content_margin);
  gtk_widget_set_margin_end(description, content_margin);
  gtk_widget_set_margin_bottom(description, content_margin);

  return description;
}

GtkWidget* AdwaitaWindow::create_logo_picture()
{
  // A GtkPicture and not a GtkImage: an image draws its texture at a fixed
  // pixel size, while a picture scales the very same texture into whatever
  // allocation it gets. That is what grows the logo over all the height the
  // labels leave free, with the content fit deciding that its width stays
  // proportional to that height instead of being stretched over the whole
  // width.
  GtkWidget* logo = gtk_picture_new_for_resource(logo_res_path);

  gtk_picture_set_content_fit(GTK_PICTURE(logo), logo_content_fit);

  // Without the shrinking the logo would push the window minimal size up to
  // its own pixel one and break the adaptive layout.
  gtk_picture_set_can_shrink(GTK_PICTURE(logo), TRUE);

  gtk_widget_set_vexpand(logo, TRUE);
  gtk_widget_set_hexpand(logo, TRUE);

  return logo;
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
      "Replace the content widgets of the AdwaitaWindow class with the real "
      "application ones";

  return default_description;
}

}  // namespace Gtkmm4i::main_window
