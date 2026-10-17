## Implement code straight away!

To proceed the library implementation right away look for the `LibMain` class' `LibMain.cpp` file which is designed to accept initial code of the library. Specifically, new code may be placed into the `bool LibMain::libcall(std::shared_ptr<LibraryContext> ctx)` method.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `Application` class implementation, rather than put all the code inside the `Application` class itself.
