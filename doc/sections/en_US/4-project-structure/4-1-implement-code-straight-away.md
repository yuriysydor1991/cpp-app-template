## Implement code straight away!

To proceed the 3D application implementation right away look for the `Painter` class' `src/SDL2/Painter/Painter.cpp` file which is designed to accept initial code of the scene drawing. Specifically, new OpenGL draw code may be placed into the `bool Painter::paint(std::shared_ptr<SDL2Context> ctx)` method, which the `SDL2Controller` event loop calls once per frame. The SDL2 events are handled by the `IEventHandler` descendants in the `src/SDL2/Eventer/EventsHandlers` directory, which the `EventsHandlersFactory` class picks per event type.

The window is created with an OpenGL 3.3 core profile context, whose functions past the OpenGL 1.1 have to be loaded at runtime: use `SDL_GL_GetProcAddress` or a loader library (e.g. [glad](https://github.com/Dav1dde/glad) or [GLEW](https://glew.sourceforge.net/)) before calling them.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application and include them into the `Painter` class implementation, rather than put all the code inside the `Painter` class itself.

Additional code may be introduced into the `Application` class implementation or by creation `IApplication` class descendant in order to provide binary level variety.
