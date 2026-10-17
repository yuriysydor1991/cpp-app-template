#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUS_CXX_MOCK_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUS_CXX_MOCK_H

// Header-only mock of the subset of the sdbus-c++ API used by the project's
// D-Bus server sources. It lets the sdbus-cpp unit tests compile and
// run without linking the real sdbus-c++ or touching a live bus: the
// bus-touching members are no-ops that return defaults. The real bus
// interactions stay covered by the component tests, which link the real
// sdbus-c++.

#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace sdbus
{

namespace mock_detail
{

/**
 * @brief Minimal stand-in for the sdbus-c++ strong string types (ServiceName,
 * ObjectPath, ...). Each alias gets a distinct tag so the types stay distinct.
 */
template <typename Tag>
class StringLike
{
 public:
  StringLike() = default;
  StringLike(std::string value) : value_{std::move(value)} {}
  StringLike(const char* value) : value_{value} {}

  explicit operator std::string() const { return value_; }
  const std::string& str() const { return value_; }

  bool operator==(const StringLike& other) const
  {
    return value_ == other.value_;
  }
  bool operator!=(const StringLike& other) const
  {
    return value_ != other.value_;
  }

 private:
  std::string value_;
};

template <typename Tag>
std::ostream& operator<<(std::ostream& os, const StringLike<Tag>& value)
{
  return os << value.str();
}

}  // namespace mock_detail

using ServiceName = mock_detail::StringLike<struct ServiceNameTag>;
using ObjectPath = mock_detail::StringLike<struct ObjectPathTag>;
using InterfaceName = mock_detail::StringLike<struct InterfaceNameTag>;
using PropertyName = mock_detail::StringLike<struct PropertyNameTag>;
using MemberName = mock_detail::StringLike<struct MemberNameTag>;

/**
 * @brief Mock of sdbus::Error. Derives from std::exception (through
 * std::runtime_error) so the production catch clauses keep working.
 */
class Error : public std::runtime_error
{
 public:
  using Name = mock_detail::StringLike<struct ErrorNameTag>;

  Error(Name name, std::string message)
      : std::runtime_error{message},
        name_{std::move(name)},
        message_{std::move(message)}
  {
  }

  const Name& getName() const { return name_; }
  const std::string& getMessage() const { return message_; }

 private:
  Name name_;
  std::string message_;
};

namespace mock
{

/**
 * @brief Test hook: while true, the next bus connection creation reports a
 * failure by throwing (exactly as the real factory does when no bus is
 * reachable), so the controller's init/create error paths can be exercised.
 */
inline bool& fail_bus_connection()
{
  static bool flag = false;
  return flag;
}

/**
 * @brief Test hook: the connection calls made so far, in their order.
 */
inline std::vector<std::string>& calls()
{
  static std::vector<std::string> made;
  return made;
}

}  // namespace mock

// ---- property read (client proxy side) ------------------------------------
class PendingPropertyGet
{
 public:
  PendingPropertyGet& onInterface(const InterfaceName&) { return *this; }

  template <typename T>
  T get()
  {
    return T{};
  }
};

class IProxy
{
 public:
  virtual ~IProxy() = default;

  PendingPropertyGet getProperty(const PropertyName&) { return {}; }
};

// ---- vtable registration (server object side) -----------------------------
class PropertyVTableItem
{
 public:
  template <typename Getter>
  PropertyVTableItem& withGetter(Getter&&)
  {
    return *this;
  }
};

inline PropertyVTableItem registerProperty(const PropertyName&) { return {}; }

class VTableAdder
{
 public:
  void forInterface(const InterfaceName&) {}
};

class IObject
{
 public:
  virtual ~IObject() = default;

  template <typename... VTableItems>
  VTableAdder addVTable(VTableItems&&...)
  {
    return {};
  }
};

// ---- connection -----------------------------------------------------------
class IConnection
{
 public:
  virtual ~IConnection() = default;

  void requestName(const ServiceName&)
  {
    mock::calls().emplace_back("requestName");
  }
  void releaseName(const ServiceName&)
  {
    mock::calls().emplace_back("releaseName");
  }
  void enterEventLoopAsync()
  {
    mock::calls().emplace_back("enterEventLoopAsync");
  }
  void leaveEventLoop() { mock::calls().emplace_back("leaveEventLoop"); }
};

inline std::unique_ptr<IConnection> createSessionBusConnection()
{
  if (mock::fail_bus_connection()) {
    throw Error(Error::Name{"org.freedesktop.DBus.Error.Failed"},
                "mock: session bus is not reachable");
  }

  return std::make_unique<IConnection>();
}

inline std::unique_ptr<IProxy> createProxy(IConnection&, ServiceName,
                                           ObjectPath)
{
  return std::make_unique<IProxy>();
}

inline std::unique_ptr<IObject> createObject(IConnection&, ObjectPath)
{
  return std::make_unique<IObject>();
}

}  // namespace sdbus

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUS_CXX_MOCK_H
