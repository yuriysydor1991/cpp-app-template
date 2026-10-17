## Implement code straight away!

To proceed the application implementation right away look for the `gdbusi::GDBusController` class' `src/gdbus/GDBusController.cpp` and/or `src/gdbus/GDBusController.h` files, which open the system bus connection and run the query handler, and for the `gdbusi::Hostname1QueryHandler` class of the `src/gdbus/query-handlers` directory, which reads and logs the hostname1 properties. Introduce every new D-Bus query as a new `IDBusQueryHandler` descendant created by the `DBusQueryHandlerFactory` class.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and use them from the query handlers, rather than put all the code inside a single handler class itself.

Additional code may be introduced into the `Application` class implementation or by creation `IApplication` class descendant in order to provide binary level variety.
