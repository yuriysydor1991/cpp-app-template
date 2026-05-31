#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GDBUSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GDBUSCONTROLLER_CLASS_H

#include <memory>

#include <giomm/dbusconnection.h>
#include <glibmm/refptr.h>

namespace gdbusi
{

/**
 * @brief Owns the system bus connection and drives the system information
 * query through a query handler.
 *
 * The native GLib GDBus (gtkmm4/giomm Gio::DBus) counterpart of the sdbus-c++
 * based appSDBusCxxClient branch SDBusCxxController and of the QtDBus based
 * appQt6QtDBusClient branch QtDBusController. Created through the static
 * create() factory method which opens the system bus connection up front, so a
 * non-null instance is always usable.
 */
class GDBusController
{
 public:
  using GDBusControllerPtr = std::shared_ptr<GDBusController>;

  virtual ~GDBusController() = default;
  GDBusController() = default;

  /**
   * @brief Reads the general system information and logs it.
   *
   * @return Returns true on success and false if the controller is not
   * initialized or the query handler reports a failure.
   */
  virtual bool run();

  /**
   * @brief Creates a controller with an established system bus connection.
   *
   * @return Returns the created controller, or an empty pointer when the system
   * bus is not reachable in the current environment.
   */
  static GDBusControllerPtr create();

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
  virtual Gio::DBus::Connection* connection_ptr();

  Glib::RefPtr<Gio::DBus::Connection> connection;

 private:
  bool make_system_info_call();
};

using GDBusControllerPtr = GDBusController::GDBusControllerPtr;

}  // namespace gdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GDBUSCONTROLLER_CLASS_H
