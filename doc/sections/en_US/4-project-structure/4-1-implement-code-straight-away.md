## Implement code straight away!

To proceed the application implementation right away look for the `main.qml` file which is designed to accept initial QML code of the application.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented QML-components of the application and include them into the `main.qml` file implementation, rather than put all the code inside the `main.qml` class itself (for the trivial applications in may be ok).

Some Qt6 related code may be introduced into the `Qt6Initer` class for supporting the better Qt6 experience.
