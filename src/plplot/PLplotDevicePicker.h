#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PLPLOTDEVICEPICKER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PLPLOTDEVICEPICKER_CLASS_H

#include <string>
#include <vector>

namespace plploti
{

/**
 * @brief Picks the interactive PLplot device the example plot is shown by.
 * The PLplot asks for a device on the standard input and quits the whole
 * process when the requested one isn't installed, so the device is picked
 * among the installed drivers ones beforehand.
 */
class PLplotDevicePicker
{
 public:
  virtual ~PLplotDevicePicker() = default;
  PLplotDevicePicker() = default;

  /// @brief The interactive devices in the order of preference: the Qt one
  /// (the plplot-driver-qt package), the Cairo X one (plplot-driver-cairo)
  /// and the plain X one (plplot-driver-xwin).
  inline static const std::vector<std::string> preferred{"qtwidget", "xcairo",
                                                         "xwin"};

  /**
   * @brief Picks the first preferred device among the given installed ones.
   *
   * @param installed The keywords of the installed PLplot devices.
   *
   * @return Returns the device keyword or an empty string when no preferred
   * device is installed.
   */
  virtual std::string pick(const std::vector<std::string>& installed) const;
};

}  // namespace plploti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PLPLOTDEVICEPICKER_CLASS_H
