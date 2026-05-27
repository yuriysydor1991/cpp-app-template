#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QTDBUSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QTDBUSCONTROLLER_CLASS_H

#include <memory>
#include <optional>

#include <QDBusConnection>

namespace qtdbusi
{

class SystemInformation;

/**
 * @brief Owns the system bus connection and drives the system information
 * query through a query handler.
 *
 * The native Qt D-Bus (Qt6::DBus) counterpart of the sdbus-c++ based
 * appSDBusCxxClient branch SDBusCxxController. Created through the static
 * create() factory method which opens the system bus connection up front, so a
 * non-null instance is always usable.
 */
class QtDBusController
{
 public:
  using QtDBusControllerPtr = std::shared_ptr<QtDBusController>;

  virtual ~QtDBusController() = default;
  QtDBusController() = default;

  /**
   * @brief Reads the general system information into the given holder.
   *
   * @param info The system information holder to populate.
   *
   * @return Returns true on success and false if the controller is not
   * initialized or the query handler reports a failure.
   */
  virtual bool run(SystemInformation& info);

  /**
   * @brief Creates a controller with an established system bus connection.
   *
   * @return Returns the created controller, or an empty pointer when the system
   * bus is not reachable in the current environment.
   */
  static QtDBusControllerPtr create();

 protected:
  virtual bool init();
  virtual bool inited() const;

  /**
   * @brief The connection handed down to the query handlers.
   *
   * Exposed as an overridable seam so the orchestration in run() may be unit
   * tested without a live bus.
   *
   * @return A pointer to the held connection, or nullptr when none is held.
   */
  virtual QDBusConnection* connection_ptr();

  std::optional<QDBusConnection> connection;

 private:
  bool make_system_info_call(SystemInformation& info);
};

using QtDBusControllerPtr = QtDBusController::QtDBusControllerPtr;

}  // namespace qtdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QTDBUSCONTROLLER_CLASS_H
