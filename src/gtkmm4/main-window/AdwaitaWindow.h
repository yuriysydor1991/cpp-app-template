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
 * The content is a plain vertical GtkBox: the heading and the description sit
 * at the very top of it, one after another, and the logo grows over the height
 * they leave free, keeping its own aspect ratio. That is what a GtkBox does
 * with the children which do not expand followed by the one which does, and it
 * is also the reason the content is not an AdwStatusPage anymore - a status
 * page centers its whole content vertically instead.
 *
 * libadwaita ships no official C++ binding, so its widgets are created through
 * the C API and handed over to the gtkmm side with Glib::wrap where a C++
 * reference is convenient. Both bindings wrap the very same GObject instances,
 * so mixing them is safe as long as the ownership stays in one place - here the
 * GTK widget tree owns every child and this class owns nothing but the raw
 * window pointer, which the running Gtk::Application owns in turn.
 *
 * Replace the content widgets with the real application ones to start the
 * development.
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
   * @brief The smaller text shown right under the window heading.
   *
   * @return Returns a non empty content description.
   */
  static const std::string& get_default_description();

  /// @brief The GResource path of the window logo.
  inline static constexpr const char* const logo_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/images/kytok.org.ua-logo.png";

  /// @brief The GResource path of the additional window stylesheet.
  inline static constexpr const char* const main_css_res_path =
      GTKMM_APP_RESOURCES_PREFIX "/resources/css/main-window.css";

  /**
   * @brief The libadwaita typography style class of the window heading.
   *
   * The title-1 is the largest of the libadwaita heading styles, the H1
   * counterpart, so no custom CSS rule is needed to enlarge the heading.
   */
  inline static constexpr const char* const title_style_class = "title-1";

  /// @brief The libadwaita typography style class of the description text.
  inline static constexpr const char* const description_style_class = "body";

  /// @brief The libadwaita style class which dims the description text.
  inline static constexpr const char* const dim_style_class = "dim-label";

  /**
   * @brief The way the logo fills the height left free by the texts.
   *
   * The GTK_CONTENT_FIT_CONTAIN scales the logo up until it hits the free
   * height and keeps its width proportional to it, so the logo never gets
   * deformed. Switch it to the GTK_CONTENT_FIT_FILL to stretch the logo over
   * the whole free area instead, or to the GTK_CONTENT_FIT_COVER to fill that
   * area keeping the ratio but cropping whatever does not fit.
   */
  inline static constexpr const GtkContentFit logo_content_fit =
      GTK_CONTENT_FIT_CONTAIN;

  /// @brief The gap between the content box children, in the logical pixels.
  inline static constexpr const int content_spacing = 6;

  /// @brief The margins around the content texts, in the logical pixels.
  inline static constexpr const int content_margin = 12;

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
   * @brief Creates the window content: the top placed texts and the logo
   * filling everything below them.
   *
   * @return Returns the created content widget.
   */
  virtual GtkWidget* create_content();

  /**
   * @brief Creates the enlarged heading label shown at the window top.
   *
   * @return Returns the created label widget.
   */
  virtual GtkWidget* create_title_label();

  /**
   * @brief Creates the smaller description label shown under the heading.
   *
   * @return Returns the created label widget.
   */
  virtual GtkWidget* create_description_label();

  /**
   * @brief Creates the logo widget which occupies all the free height with a
   * proportional width.
   *
   * @return Returns the created picture widget.
   */
  virtual GtkWidget* create_logo_picture();

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
