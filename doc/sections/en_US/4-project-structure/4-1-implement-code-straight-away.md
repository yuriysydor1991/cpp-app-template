## Implement code straight away!

To proceed the library implementation right away look for the `LibMain` class' `LibMain.cpp` file which is designed to accept initial code of the library. Specifically, new code may be placed into the `bool LibMain::libcall(std::shared_ptr<LibraryContext> ctx)` method.

The `LibMain` class will be compiled into destination target library in order to make it's implementation available for other external applications to reuse it.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the library and include them into the `LibMain` class implementation, rather than put all the code inside the `LibMain` class itself (thats may be ok for a trivial library).
