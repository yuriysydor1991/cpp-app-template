#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ADWAITAWINDOW_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ADWAITAWINDOW_CLASS_H

#include <memory>
#include <string>

#include "src/gtkmm4/adwaita_includes.h"
#include "src/gtkmm4/gtkmm4_includes.h"

namespace Gtkmm4i::main_window
{

/**
 * @brief The whole application window built out of the libadwaita widgets.
 *
 * The window itself is an AdwApplicationWindow, not a plain Gtk::Window, so the
 * header bar lives inside the window content and the adaptive libadwaita
 * behaviour (the AdwBreakpoint support, the rounded window corners and the
 * AdwStyleManager driven light and dark palettes) applies to the whole surface.
 *
 * libadwaita ships no official C++ binding, so its widgets are created through
 * the C API and handed over to the gtkmm side with Glib::wrap where a C++
 * reference is convenient. Both bindings wrap the very same GObject instances,
 * so mixing them is safe as long as the ownership stays in one place - here the
 * GTK widget tree owns every child and this class owns nothing but the raw
 * window pointer, which the running Gtk::Application owns in turn.
 *
 * Replace the AdwStatusPage content with the real application widgets to start
 * the development.
 */
class AdwaitaWindow
{
 public:
  using AdwaitaWindowPtr = std::shared_ptr<AdwaitaWindow>;

  virtual ~AdwaitaWindow() = default;
  AdwaitaWindow() = default;

  /**
   * @brief Creates the AdwApplicationWindow, fills it with the libadwaita
   * widget tree and presents it.
   *
   * Requires an already initialized libadwaita - see the
   * Gtkmm4i::GtkmmIniter::run which calls the adw_init for the whole process.
   *
   * @param app The running application the window belongs to.
   *
   * @return Returns the created window wrapped into its gtkmm counterpart, or
   * nullptr in case of any error. The returned window is owned by the given
   * application.
   */
  virtual Gtk::Window* build(const Glib::RefPtr<Gtk::Application>& app);

  /**
   * @brief Composes the window title out of the project name and version.
   *
   * @return Returns a non empty window title.
   */
  static const std::string& get_default_title();

  /**
   * @brief The description shown by the placeholder AdwStatusPage.
   *
   * @return Returns a non empty status page description.
   */
  static const std::string& get_default_description();

  /// @brief The GResource path of the window logo.
  inline static constexpr const char* const logo_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/images/kytok.org.ua-logo.png";

  /// @brief The GResource path of the additional window stylesheet.
  inline static constexpr const char* const main_css_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/css/main-window.css";

  /// @brief The default window sizes, in the logical pixels.
  inline static constexpr const int default_width = 600;
  inline static constexpr const int default_height = 500;
  inline static constexpr const int min_width = 360;
  inline static constexpr const int min_height = 294;

 protected:
  /**
   * @brief Creates the AdwHeaderBar shown as the AdwToolbarView top bar.
   *
   * @return Returns the created header bar widget.
   */
  virtual GtkWidget* create_header_bar();

  /**
   * @brief Creates the AdwStatusPage which stands for the actual application
   * content until it is replaced with the real widgets.
   *
   * @return Returns the created status page widget.
   */
  virtual GtkWidget* create_status_page();

  /**
   * @brief Loads the additional window stylesheet from the GResource bundle
   * and applies it on top of the libadwaita one.
   */
  virtual void prepare_css();

 private:
  AdwApplicationWindow* window{nullptr};
};

using AdwaitaWindowPtr = AdwaitaWindow::AdwaitaWindowPtr;

}  // namespace Gtkmm4i::main_window

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ADWAITAWINDOW_CLASS_H
