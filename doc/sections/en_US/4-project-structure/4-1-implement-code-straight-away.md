## Implement code straight away!

To proceed the application implementation right away look for the `Wt4Server` class' `src/wt4/Wt4Server.cpp` file which is designed to accept initial code of the application. Specifically, new code may be placed into the `Wt4Server::Wt4Server(const Wt::WEnvironment& env, std::shared_ptr<Wt4Context> nwt4ctx)` constructor, which runs for every new session and fills its root with the widgets of the `widgets::WidgetsFactory` class, e.g. the `widgets::guest::Root` one of the `src/wt4/widgets/guest/Root.cpp` file.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `Wt4Server` class implementation, rather than put all the code inside the `Wt4Server` class itself.
