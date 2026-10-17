## Implement code straight away!

To proceed the 2D application implementation right away look for the `Painter` class' `src/SFML/Painter/Painter.cpp` file which is designed to accept initial code of the scene drawing. Specifically, new SFML draw code may be placed into the `bool Painter::paint(std::shared_ptr<SFMLContext> ctx)` method, which the `SFMLController` event loop calls once per frame. The SFML events are handled by the `IEventHandler` descendants in the `src/SFML/Eventer/EventsHandlers` directory, which the `EventsHandlersFactory` class picks per event type.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `Painter` class implementation, rather than put all the code inside the `Painter` class itself.

Additional code may be introduced into the `Application` class implementation or by creation `IApplication` class descendant in order to provide binary level variety.
