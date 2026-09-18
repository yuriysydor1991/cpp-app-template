## Implement code straight away!

To proceed the application implementation right away look for the `src/qtdbus/query-handlers` directory: every D-Bus query of the application is a class implementing the `IDBusQueryHandler` interface, like the `Hostname1QueryHandler` one which reads the systemd-hostnamed properties, and the `DBusQueryHandlerFactory` class creates the handler the `QtDBusController` class runs over its system bus connection.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to add a new `IDBusQueryHandler` descendant for a new query and to create other directories which would contain implemented components of the application, rather than put all the code inside a single handler class.

Some Qt6 related code may be introduced into the `Qt6Initer` class, which creates the `QCoreApplication` instance the QtDBus module needs.
