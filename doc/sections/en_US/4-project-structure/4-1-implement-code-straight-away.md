## Implement code straight away!

To proceed the application implementation right away look for the `Gtkmm3Controller` class' `Gtkmm3Controller.cpp` and/or `Gtkmm3Controller.h` files which is designed to accept initial code of the application's window. The UI may be designed in the `src/gtkmm3/ui/GtkmmWindow.ui`.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `Gtkmm3Controller` class implementation, rather than put all the code inside the `Gtkmm3Controller` class itself.

Additional code may be introduced into the `Application` class implementation or by creation `IApplication` class descendant in order to provide binary level variety.

The `StopFlagWatcher` class quits the GTK application main loop as soon as the OS signals (Ctrl+C, `kill` and so on) raise the application context stop flag, so the window code needs no signal handling of its own.
