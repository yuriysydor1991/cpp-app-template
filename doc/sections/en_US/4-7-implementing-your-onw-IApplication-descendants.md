## Implement your own IApplication descendants

The `IApplication` interface and all of it's descendants are decomposed into the `src/app/applications` subcomponent directory of the `src/app` component:

```
src/app/applications
├── Application.cpp
├── Application.h
├── ApplicationHelpPrinter.cpp
├── ApplicationHelpPrinter.h
├── ApplicationVersionPrinter.cpp
├── ApplicationVersionPrinter.h
├── meson.build
├── IApplication.h
└── tests
    ├── meson.build
    ├── mocks
    │   ├── Application
    │   ├── ApplicationHelpPrinter
    │   └── ApplicationVersionPrinter
    └── unit
        ├── Application
        ├── ApplicationHelpPrinter
        ├── ApplicationVersionPrinter
        └── meson.build
```

You may implement another custom `IApplication` descendant classes in order to support high level variety of the application behavior to not to mess original `Application` class with irrelevant `if`-s statements and mixing up code (remember about the SOLID's single responsibility principle).

You may accomplish `IApplication` subclassing by directly creating an `IApplication` subclass in a new file or extend existing `IApplication` descendant like `Application`, `ApplicationHelpPrinter` or a `ApplicationVersionPrinter`.

Register newly created custom `IApplication` descendant in the `ApplicationFactory`'s `create_application` method which is responsible to create appropriate application instance with accordance of a provided data through the command line parameters.

That may be accomplished by implementing a custom `ApplicationFactory` descendant and overriding it's create methods like `create_application` and/or others (call appropriate static member in the `main` function of the `main.cpp` file).

### Where to place the new descendant files

1. Put the new class' header and source files into the `src/app/applications` directory and list the new `.cpp` file in the `applications_sources` of the `src/app/applications/meson.build` build file.
1. Put the new class' unit test into the `src/app/applications/tests/unit/<YourApplication>` directory and register that directory with a `subdir` call in the `src/app/applications/tests/unit/meson.build` build file. Take the neighbour unit tests as an example.
1. If the new class has to be substituted with a GMock object in some other class' test (like it is done for the `ApplicationFactory` unit test), put that mock into the `src/app/applications/tests/mocks/<YourApplication>/src/app/applications/<YourApplication>.h` file and declare it as a `MOCK_<YourApplication>` in the `src/app/applications/tests/mocks/meson.build` build file, next to the mocks of the neighbour applications. The `src/app` component own mocks stay in the `src/app/tests/mocks` directory.
