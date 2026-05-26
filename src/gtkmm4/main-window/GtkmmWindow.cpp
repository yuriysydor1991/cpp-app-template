#include "src/gtkmm4/main-window/GtkmmWindow.h"

#include "project-global-decls.h"
#include "src/log/log.h"

namespace Gtkmm4i::main_window
{

GtkmmWindow::GtkmmWindow()
{
  if (!init()) {
    LOGE("Fail to init");
  }
}

bool GtkmmWindow::init()
{
  prepare_window();

  set_child(map);

  return true;
}

void GtkmmWindow::prepare_window()
{
  set_title(get_default_title());

  set_size_request(400, 300);
  set_default_size(500, 400);
}

const std::string& GtkmmWindow::get_default_title()
{
  static const std::string default_title =
      std::string{project_decls::PROJECT_NAME} + " " +
      project_decls::PROJECT_BUILD_VERSION;

  return default_title;
}

GtkmmWindowPtr GtkmmWindow::create() { return std::make_shared<GtkmmWindow>(); }

}  // namespace Gtkmm4i::main_window
