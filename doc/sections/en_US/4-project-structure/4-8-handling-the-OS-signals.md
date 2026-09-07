## Handling the OS signals

The OS signals which are asking the process to stop are covered by the `src/app/signals-handlers` subcomponent of the `src/app` component:

```
src/app/signals-handlers
├── CMakeLists.txt
├── ISignalsHandler.h
├── SignalsHandler.cpp
├── SignalsHandler.h
└── tests
    ├── CMakeLists.txt
    ├── mocks
    │   └── SignalsHandler
    └── unit
        ├── CMakeLists.txt
        └── SignalsHandler
```

The `ApplicationFactory::run` method creates the default `ISignalsHandler` interface implementation - the `SignalsHandler` one - right before the created application start and hands the application context over to it's `ISignalsHandler::install` method. Every handled signal raises the context stop flag through the `ApplicationContext::set_stop` setter from that moment, and the handled signals are given back to the OS default disposition as soon as the `ApplicationFactory::run` returns.

The handled signals are the `SIGINT` one of the Ctrl+C keys combination, the `SIGTERM` one of the `kill` command and the POSIX only `SIGHUP` and `SIGQUIT` ones (the last two are silently skipped on the platforms which are not declaring them, like the MS Windows one).

So the application implementation is expected to poll the `ApplicationContext::get_stop` flag inside every long running routine of it's `IApplication::run` implementation and to return as soon as the flag is raised. The flag is an atomic one, so it is safe to poll it from any thread of the application, as well as from a timer callback of a toolkit main loop.

### Extending the signals handling

1. Add or remove the handled OS signals numbers in the `SignalsHandler::get_handled_signals` method.
1. Implement an own `ISignalsHandler` descendant whenever a completely different reaction is needed, put it into the `src/app/signals-handlers` directory, list it's new `.cpp` file in the `target_sources` call of the `src/app/signals-handlers/CMakeLists.txt` build file and return it from an overridden `ApplicationFactory::create_default_signals_handler` method.
1. Put the new class' unit test into the `src/app/signals-handlers/tests/unit/<YourSignalsHandler>` directory and register that directory with an `add_subdirectory` call in the `src/app/signals-handlers/tests/unit/CMakeLists.txt` build file. The subcomponent mocks directory is exposed to the whole `src/app` component as the `${SIGNALS_HANDLERS_MOCKS_ROOT}` CMake variable, the same way the `${APPLICATIONS_MOCKS_ROOT}` one is exposed by the `src/app/applications` subcomponent.

**Keep in mind that the routine which the OS calls on a signal arrival is allowed to use the async signal safe calls only**, so the `SignalsHandler::stop_context` one touches the lock free atomics and does no logging, no memory allocation and no locking at all.
