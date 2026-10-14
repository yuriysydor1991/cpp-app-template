## Implement code straight away!

To proceed the application implementation right away look for the `FreeGlutController` class' `FreeGlutController.cpp` file which is designed to accept initial code of the 3D application. Specifically, new code may be placed into the `void FreeGlutController::display()` method.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `FreeGlutController` class implementation, rather than put all the code inside the `FreeGlutController` class itself.

Additional code may be introduced into the `Application` class implementation or by creation `IApplication` class descendant in order to provide binary level variety.
