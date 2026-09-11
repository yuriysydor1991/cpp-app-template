## Handling the OS signals

The OS signals which are asking the process to stop or to pause are covered by the `src/app/signals-handlers` subcomponent of the `src/app` component:

```
src/app/signals-handlers
├── meson.build
├── ISignalsHandler.h
├── SignalsHandler.cpp
├── SignalsHandler.h
├── handlers
│   ├── ASignalsHandler.cpp
│   ├── ASignalsHandler.h
│   ├── meson.build
│   ├── posix
│   │   ├── meson.build
│   │   ├── ContinueSignalsHandler.cpp
│   │   ├── ContinueSignalsHandler.h
│   │   ├── IgnoredSignalsHandler.cpp
│   │   ├── IgnoredSignalsHandler.h
│   │   ├── PauseSignalsHandler.cpp
│   │   ├── PauseSignalsHandler.h
│   │   ├── PosixSignalsHandler.cpp
│   │   ├── PosixSignalsHandler.h
│   │   ├── ReloadSignalsHandler.cpp
│   │   ├── ReloadSignalsHandler.h
│   │   ├── StopSignalsHandler.cpp
│   │   ├── StopSignalsHandler.h
│   │   ├── UserSignalsHandler.cpp
│   │   ├── UserSignalsHandler.h
│   │   └── tests
│   │       ├── mocks
│   │       └── unit
│   └── tests
│       └── unit
└── tests
    ├── mocks
    │   └── SignalsHandler
    └── unit
        └── SignalsHandler
```

Every class of the subcomponent implements the very same `ISignalsHandler` interface, so the rest of the application depends on the interface only and knows neither how many signals categories exist nor which platform declares them:

```
ISignalsHandler                          the only type the application depends on
├── SignalsHandler                       the facade over every category
└── ASignalsHandler                      the std::signal install and uninstall mechanics
    └── PosixSignalsHandler              the POSIX platforms family
        ├── StopSignalsHandler           SIGINT, SIGTERM, SIGQUIT
        ├── PauseSignalsHandler          SIGTSTP, SIGTTIN, SIGTTOU
        ├── ContinueSignalsHandler       SIGCONT
        ├── ReloadSignalsHandler         SIGHUP
        ├── UserSignalsHandler           SIGUSR1, SIGUSR2
        └── IgnoredSignalsHandler        SIGPIPE
```

1. The `SignalsHandler` class is the **facade** of the whole subcomponent. It creates a subhandler of every covered signals category in it's `SignalsHandler::create_handlers` method and forwards the `ISignalsHandler::install` and the `ISignalsHandler::uninstall` calls to each of them.
1. The `ASignalsHandler` class is the **common std::signal based skeleton** of a single category handler. It knows how to subscribe the process to a set of the OS signals and how to give them back to the OS default disposition, while a descendant only tells which signals it's category consists of, which routine reacts on them and where the handled context pointer is kept.
1. The `PosixSignalsHandler` class is the **platform family base**, which makes the platform of a handler a part of it's type and not a directory name only. It adds no behaviour of it's own on purpose - it classifies the descendants instead, holds the lock free atomic assertion the whole family shares and keeps a place for the helpers it may share one day, so a handler of another family, a MS Windows console control one for example, becomes an obviously different type rather than a look alike neighbour.
1. The `handlers/posix` directory holds the **category handlers** themselves - one per reaction the application may have. They rest on the standard `std::signal` call, so they stay compilable everywhere, while the signals which are declared by the POSIX platforms only are guarded with the `ifdef` and are simply not covered elsewhere.

The `ApplicationFactory::run` method creates the default `ISignalsHandler` interface implementation - the `SignalsHandler` facade - right before the created application start and hands the application context over to it's `ISignalsHandler::install` method. Every handled signal raises the context stop flag through the `ApplicationContext::set_stop` setter or toggles the context pause one through the `ApplicationContext::set_pause` setter from that moment, and the handled signals are given back to the OS default disposition as soon as the `ApplicationFactory::run` returns.

### The application stop signals

The `StopSignalsHandler` class covers the `SIGINT` one of the Ctrl+C keys combination, the `SIGTERM` one of the `kill` command and the POSIX only `SIGQUIT` one (silently skipped on the platforms which are not declaring it, like the MS Windows one). The `SIGHUP` signal is **not** a stop one here, see the configuration reload requests below.

So the application implementation is expected to poll the `ApplicationContext::get_stop` flag inside every long running routine of it's `IApplication::run` implementation and to return as soon as the flag is raised. The flag is an atomic one, so it is safe to poll it from any thread of the application, as well as from a timer callback of a toolkit main loop.

### The application pause signals

The `PauseSignalsHandler` class covers the POSIX signals which are asking the process to suspend itself - the `SIGTSTP` one of the Ctrl+Z keys combination, the `SIGTTIN` one of a background process reading from the terminal and the `SIGTTOU` one of a background process writing to it. All the three raise the context pause flag through the `ApplicationContext::set_pause` setter. The `ContinueSignalsHandler` class covers the `SIGCONT` signal of the `fg` and `bg` shell job control commands and lowers the very same flag back.

So the application implementation is expected to poll the `ApplicationContext::get_pause` flag the same way the stop one is polled and to hold it's work - to stop rendering the frames, to stop feeding the worker threads, to release the exclusive devices and so on - while the flag is raised, instead of leaving the `IApplication::run` method. The flag is an atomic one too.

**Keep in mind that handling the pause signals replaces the OS default disposition of them, so the process is not suspended by the Ctrl+Z keys combination any more** - it is up to the application to react on the raised pause flag. Drop the `PauseSignalsHandler` class from the `SignalsHandler::create_handlers` set whenever the usual shell job control behaviour is preferred, or make the application call `std::raise(SIGSTOP)` on it's own once it is ready to be suspended.

The `SIGSTOP` signal is deliberately absent in the covered sets, since **no process is allowed to handle, to block or to ignore it at all** - the OS suspends the process on it's arrival without any notification, so such a pause stays unnoticed by the application.

The pause and the continue categories are the empty ones on the platforms which are not declaring those POSIX signals, like the MS Windows one, so their `ISignalsHandler::install` calls report a failure there, which the facade tolerates as long as any other category is covered.

### The configuration reload signals

The `ReloadSignalsHandler` class covers the `SIGHUP` signal, which the OS sends on a closed terminal and which the daemon control tools send on purpose. It raises the context reload flag through the `ApplicationContext::set_reload` setter, so the application is expected to poll the `ApplicationContext::get_reload` one, to reread it's configuration and to lower the flag back on it's own.

The signal is the conventional configuration reload request of the long living processes, which is why it belongs here and not to the stop category. **The OS default reaction on it terminates the process, so handling it means a closed terminal does not end the application any more.** Drop the class from the `SignalsHandler::create_handlers` set, or move the `SIGHUP` number back into the `StopSignalsHandler::get_handled_signals` one, whenever the termination is the expected reaction.

### The user defined signals

The `UserSignalsHandler` class covers the `SIGUSR1` and the `SIGUSR2` signals, which the OS reserves for the application own needs and gives no meaning of it's own to. The first one raises the context flag of the `ApplicationContext::set_first_user_request` setter and the second one raises the flag of the `ApplicationContext::set_second_user_request` one, so it is the only handler of the component which tells it's signals apart by the number the OS gives to the routine.

**The meaning of both requests is the application own one** - reopening the log files after a rotation and dumping the current state are the classic ones. The application is expected to poll the flags, to serve the pending request and to lower the flag back on it's own. The flags coalesce, so a burst of the very same signal is a single pending request - count the arrivals inside the routine instead whenever every single one of them has to be served.

The OS default reaction on both signals terminates the process, so handling them keeps the application alive on a `kill -USR1 <pid>` command.

### The ignored signals

The `IgnoredSignalsHandler` class covers the `SIGPIPE` signal, which arrives on a write into a pipe or a socket nobody reads any more. It is the only handler of the component which installs the `SIG_IGN` disposition instead of a routine, so it touches no application context at all and it's `ASignalsHandler::store_context` override is an empty one.

**The OS default reaction on the signal terminates the process silently**, which turns a disconnected peer into an unexplained application death. Ignoring the signal makes the failing write return an `EPIPE` error instead, so the calling code gets the chance to notice the broken connection and to report it, which is why virtually every networking application ignores it.

### Extending the signals handling

1. Add or remove the covered OS signals numbers in the `ASignalsHandler::get_handled_signals` override of the appropriate category handler.
1. Add a brand new signals category by putting an own `PosixSignalsHandler` descendant into the `src/app/signals-handlers/handlers/posix` directory, listing it's new `.cpp` file in the `signals_handlers_posix_sources` of that directory `meson.build` build file and creating it in the `SignalsHandler::create_handlers` method. The descendant is expected to override the `ASignalsHandler::get_handled_signals`, the `ASignalsHandler::get_signal_disposition` and the `ASignalsHandler::store_context` methods, to keep it's own `std::atomic<ApplicationContext*>` field and **to call the `ISignalsHandler::uninstall` method from it's own destructor**, since neither the `ASignalsHandler` nor the `PosixSignalsHandler` one is able to reach the pure virtual `ASignalsHandler::store_context` method.
1. Cover a platform family the POSIX signals do not fit by putting an own `ASignalsHandler` descendant - a family base of the `PosixSignalsHandler` kind - into a new `src/app/signals-handlers/handlers/<platform>` directory, registering that directory with a `subdir` call in the `src/app/signals-handlers/handlers/meson.build` build file, entering its tests with a `subdir` call in the `src/app/meson.build` one and deriving the categories of that family from it. The facade tolerates a category which covers nothing on the current platform, so the families of every supported platform may be created side by side in the `SignalsHandler::create_handlers` method.
1. Implement an own `ISignalsHandler` descendant whenever a completely different reaction is needed, put it into the `src/app/signals-handlers` directory, list it's new `.cpp` file in the `signals_handlers_sources` of the `src/app/signals-handlers/meson.build` build file and return it from an overridden `ApplicationFactory::create_default_signals_handler` method.
1. Put the new class' unit test into the `src/app/signals-handlers/tests/unit/<YourSignalsHandler>` directory, or into the `src/app/signals-handlers/handlers/<platform>/tests/unit/<YourSignalsHandler>` one for a category handler, and register that directory with a `subdir` call in the appropriate `tests/unit/meson.build` build file. The subcomponent mocks are declared as the `MOCK_<YourSignalsHandler>` entries in the `src/app/signals-handlers/tests/mocks/meson.build` and the `src/app/signals-handlers/handlers/posix/tests/mocks/meson.build` build files, the same way the `src/app/applications` subcomponent declares its own.

**Keep in mind that the routine which the OS calls on a signal arrival is allowed to use the async signal safe calls only**, so every one of them - the `StopSignalsHandler::stop_context`, the `PauseSignalsHandler::pause_context`, the `ContinueSignalsHandler::continue_context`, the `ReloadSignalsHandler::reload_context` and the `UserSignalsHandler::request_context` ones - touches the lock free atomics and does no logging, no memory allocation and no locking at all. The `IgnoredSignalsHandler` class installs no routine at all, since the `SIG_IGN` value is a valid `ASignalsHandler::get_signal_disposition` answer of its own.
