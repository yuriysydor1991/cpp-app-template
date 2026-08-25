## The toolkit messages

The application logs through the `src/log/log.h` macroses, while Qt Core, Qt Gui, Qt Quick, the QML engine, the platform plugins and every other module of the toolkit report through the Qt logging, which writes into the standard error stream of the process by it's own default message handler. So without any further ado a toolkit complaint is seen by whoever watches the terminal and by nobody else - it never reaches the log file, it carries no timestamp of the application format, no thread id and it obeys no level setting of the application.

The `Qt6i::qtlog::QtLogBridge` class of the `src/qt6/log` directory takes that over. It's `install` method, called at the very start of the `Qt6i::Qt6Initer::run` before anything of the toolkit is touched, hands an own message handler over to the `qInstallMessageHandler` in the place of the default one, and that handler turns every message of the process into a call of the application logging macroses.

The Qt message types are mapped this way:

| Qt message type | Application level |
| --- | --- |
| `QtFatalMsg` | error |
| `QtCriticalMsg` | error |
| `QtWarningMsg` | warning |
| `QtInfoMsg` | info |
| `QtDebugMsg` | debug |

The Qt fatal and critical types both stand for a broken invariant, which is why both of them are errors here. The fatal one keeps it's own behaviour on top of that: Qt aborts the process right after the handler returns, and the logger has the message in the file already, because it flushes every error by itself.

Beside the text a message carries a logging category and, whenever the reporting module was built with the `QT_MESSAGELOGCONTEXT` definition, the source file, line and function it came from. The log line carries all of them, in that very order:

```
... DBG ... QtLogBridge.cpp:78 : qt.highdpi: Initializing high-DPI scaling
... DBG ... QtLogBridge.cpp:78 : qt.qml.import: addImportPath: "qrc:/qt/qml"
... WRN ... QtLogBridge.cpp:75 : qt.qpa.xcb: could not connect to display
... ERR ... QtLogBridge.cpp:72 : This application failed to start because no Qt platform plugin could be initialized.
```

The uncategorized messages of the `qDebug`, the `qInfo`, the `qWarning` and the `qCritical` carry the `default` category, which is left out of the log line - exactly the way the Qt own default message pattern leaves it out. The named categories of the toolkit modules stand at the front of the message, the way they do in the terminal. Of the source file only the file name is kept, the very way the logger shortens the application own `__FILE__` values, and a QML file which names itself with an URL is shortened the same way.

The bridge logs through the `LOG*` macroses and not through a logger class directly, so it keeps working on the branches which replace the whole logging implementation (`appLog4Cpp5`, `appBoostLog`). The price of it is the source coordinates of a log line: they name the `QtLogBridge.cpp` file itself, while the toolkit ones stand inside the message text.

The QML interface files take part in it as well, wherever the application shows one. The `console.log`, the `console.warn` and the rest of the QML console are a front of the very same Qt logging, and so are the complaints of the QML engine about a file it fails to load, so all of them reach the log file with the QML file name and line in the message text.

### What is reported at all

Two gates stand in front of the log file and the bridge keeps both of them.

The first one is the toolkit own: Qt asks the logging category of a message before it calls a message handler at all, so a message the toolkit does not report never arrives at the bridge and there is nothing to keep by hand here - unlike the GLib logging, where the default gate is a part of the default writer and goes away together with it.

The categories of the toolkit itself, the ones named `qt.*`, report their debug messages only while the logging rules switch them on, which the `QT_LOGGING_RULES` environment variable, the `qtlogging.ini` file of the platform and the `QLoggingCategory::setFilterRules` call all set:

```bash
QT_LOGGING_RULES="qt.qpa.*.debug=true" ./YourApplication
QT_LOGGING_RULES="*.debug=true" ./YourApplication
```

Without those rules the warnings, the criticals and the fatals still reach the log - only the chatter of the toolkit internals stays out of it. That is the behaviour every Qt application has, and replacing the message handler must not change it.

The second gate is the `MAX_LOG_LEVEL` of the build, the very one the application own messages obey. A build which names the info level as it's highest (the default `-DMAX_LOG_LEVEL=3`) drops the toolkit debug messages whatever the logging rules say, and it does not even assemble their text.

### The one handler per process rule

Qt keeps a single message handler for the whole process and replaces it as many times as it is asked to, unlike the GLib logging which kills the process on a second writer. The bridge still installs itself once and ignores every further call, so that it never takes that single slot away from a handler the application installs for itself later on. Keep the slot for the bridge: the handler is a process wide one, so it catches the Qt messages of every library of the binary anyway.

Two Qt facilities step aside once the bridge is in place. The `QT_MESSAGE_PATTERN` variable and the `qSetMessagePattern` call shape the text of the default handler, which no longer runs, so the log line layout is the application one alone. And a message the handler produces itself would never recurse into it - Qt guards it's handler against that and writes such a message into the standard error stream instead - but the logging subsystem of this project uses no Qt facility at all, so the case does not arise.
