## Implement code straight away!

To proceed the application implementation right away look for the `GtkmmIniter` class' `GtkmmIniter.cpp` and/or `GtkmmIniter.h` files which is designed to accept initial code of the application's window. The UI may be designed in the `src/gtkmm3/ui/GtkmmWindow.ui`.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `GtkmmIniter` class implementation, rather than put all the code inside the `GtkmmIniter` class itself.

Additional code may be introduced into the `Application` class implementation or by creation `IApplication` class descendant in order to provide binary level variety.
