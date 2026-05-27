#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SYSTEMINFORMATION_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SYSTEMINFORMATION_CLASS_H

#include <QObject>
#include <QString>

/**
 * @brief The namespace to contain all the entities related to the Qt D-Bus
 * (QtDBus, Qt6::DBus) based system bus client component.
 */
namespace qtdbusi
{

/**
 * @brief The general system information data holder exposed to the QML layer.
 *
 * A single instance is created by the Qt6Initer, populated by the
 * QtDBusController through a query handler and then published into the QML
 * engine root context (as the @c systemInfo context property) so the main
 * window may simply bind to its properties. The fields mirror a few read only
 * properties of the systemd-hostnamed service (org.freedesktop.hostname1).
 *
 * The properties are exposed with the @c MEMBER convenience and a single shared
 * @c changed() notifier - one notification after a whole query is the only
 * update granularity this one shot client needs.
 */
class SystemInformation : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString hostname MEMBER hostname NOTIFY changed)
  Q_PROPERTY(QString prettyHostname MEMBER prettyHostname NOTIFY changed)
  Q_PROPERTY(QString operatingSystemPrettyName MEMBER operatingSystemPrettyName
                 NOTIFY changed)
  Q_PROPERTY(QString kernelName MEMBER kernelName NOTIFY changed)
  Q_PROPERTY(QString kernelRelease MEMBER kernelRelease NOTIFY changed)
  Q_PROPERTY(QString chassis MEMBER chassis NOTIFY changed)
  Q_PROPERTY(QString error MEMBER error NOTIFY changed)

 public:
  virtual ~SystemInformation();
  explicit SystemInformation(QObject* parent = nullptr);

  /// @brief The static hostname (org.freedesktop.hostname1 Hostname).
  QString hostname;
  /// @brief The pretty, user friendly hostname (PrettyHostname).
  QString prettyHostname;
  /// @brief The operating system pretty name (OperatingSystemPrettyName).
  QString operatingSystemPrettyName;
  /// @brief The OS kernel name, e.g. "Linux" (KernelName).
  QString kernelName;
  /// @brief The OS kernel release, e.g. "6.8.0-1-generic" (KernelRelease).
  QString kernelRelease;
  /// @brief The chassis type, e.g. "vm"/"laptop"/"desktop" (Chassis).
  QString chassis;
  /// @brief A human readable error description set when the query fails. Empty
  /// on success so the QML side may show it conditionally.
  QString error;

  /**
   * @brief Emits the changed() notifier so every bound QML property refreshes.
   *
   * Called by the query handlers once a full property read round completed (or
   * failed), keeping the notification logic out of the bus touching code.
   */
  void notifyChanged();

 signals:
  /// @brief Emitted whenever any of the held properties changed.
  void changed();
};

}  // namespace qtdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SYSTEMINFORMATION_CLASS_H
