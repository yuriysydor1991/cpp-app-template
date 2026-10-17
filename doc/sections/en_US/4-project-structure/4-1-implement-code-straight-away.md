## Implement code straight away!

To proceed the application implementation right away look for the classes of the `src/gtkmm3/main-window` directory: the `Loader` class builds the window out of the UI file and prepares its widgets, the `DataContext` class names the UI resources and the widget ids, and the `EventsHandler` class is designed to accept the window events connections. The UI may be designed in the `src/gtkmm3/ui/GtkmmWindow.ui`.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and use them from the `main-window` classes, rather than put all the code inside the `Loader` and the `EventsHandler` classes themselves.

Additional code may be introduced into the `Application` class implementation or by creation `IApplication` class descendant in order to provide binary level variety.

The `StopFlagWatcher` class quits the GTK application main loop as soon as the OS signals (Ctrl+C, `kill` and so on) raise the application context stop flag, so the window code needs no signal handling of its own.
