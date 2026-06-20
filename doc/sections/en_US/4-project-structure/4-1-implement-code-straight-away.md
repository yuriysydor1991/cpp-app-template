## Implement code straight away!

To proceed the application implementation right away look for the `Application` class' `Application.cpp` file which is designed to accept initial code of the application. Specifically, new code may be placed into the `int Application::run(std::shared_ptr<ApplicationContext> ctx)` method.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `Application` class implementation, rather than put all the code inside the `Application` class itself.
