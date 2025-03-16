#include "src/gtkmm/GtkmmWindow.h"

#include "project-global-decls.h"
#include "random-logo.h"

namespace templateGtkmm
{

GtkmmWindow::GtkmmWindow()
    : box{},
      headerText{"Main GTKmm application"},
      explanationText{
          "Replace the default window implementation in GtkmmWindow class"}
{
  set_title(get_default_title());

  set_size_request(400, 300);
  set_default_size(500, 400);

  prepare_header_label();
  prepare_random_logo();

  box.set_homogeneous(false);

  box.pack_start(headerText, false, false);
  box.pack_start(explanationText, false, false);
  box.pack_start(image, true, true);

  add(box);

  show_all_children();
}

void GtkmmWindow::prepare_header_label()
{
  // Set font size using Pango attributes
  auto attr_list = Pango::AttrList();
  auto fontScale =
      Pango::Attribute::create_attr_size(20 * PANGO_SCALE);  // 20px font size
  attr_list.insert(fontScale);

  headerText.set_attributes(attr_list);
}

void GtkmmWindow::prepare_random_logo()
{
  // Create Pixbuf from memory
  Glib::RefPtr<Gdk::PixbufLoader> loader = Gdk::PixbufLoader::create();

  loader->write(resoruces::images::random_logo_data,
                resoruces::images::random_logo_data_size);
  loader->close();

  image.set(loader->get_pixbuf());
}

const std::string& GtkmmWindow::get_default_title()
{
  static const std::string default_title =
      std::string{project_decls::PROJECT_NAME} + " " +
      project_decls::PROJECT_BUILD_VERSION;

  return default_title;
}

}  // namespace templateGtkmm
