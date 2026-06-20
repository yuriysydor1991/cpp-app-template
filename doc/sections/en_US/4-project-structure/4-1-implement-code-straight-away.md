## Implement code straight away!

To proceed the application implementation right away look for the `LibMain` class' `LibMain.cpp` file which is designed to accept initial code of the application. Specifically, new code may be placed into the `bool LibMain::libcall(std::shared_ptr<LibraryContext> ctx)` method. 

Although `Application` class instance which calls for the `libcall` method of the `LibMain` class is fully implemented and doesn't require any changes, it may also receive some changes in order for application to work properly if necessary. See the `Application` class default implementation method `int Application::run(std::shared_ptr<ApplicationContext> ctx)` in order to review it's code and introduce some changes.

The `LibMain` class will be compiled into destination target library in order to make it's implementation available for other external applications to reuse it.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `LibMain` class implementation, rather than put all the code inside the `LibMain` class itself (thats may be ok for a trivial application).
