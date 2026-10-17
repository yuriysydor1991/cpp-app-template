## The Boost.Log logger

The log macros of the `src/log/log.h` file log through the `boost_log::BoostLogController` class of the `src/log/boost-log` directory, which sets the [Boost.Log](https://www.boost.org/doc/libs/release/libs/log/) console and file sinks up:

| Macro | Logs into |
| --- | --- |
| `LOG_INIT_DEFAULTS()` | the console and the `CppAppTemplate-<version>.log` file of the current directory; a file that can't be opened (a read-only current directory, for instance) costs a single standard error warning and the logs go into the console only |
| `LOG_INIT_PATH(path)` | the console and the given file, which the `-l` (or `--log-file`) command line parameter names; it yields `false` when the file can't be opened |
| `LOG_INIT(path, level, printMessages)` | the given file with the given level, the console as well when the `printMessages` is `true`; it yields `false` when the file can't be opened |

Every init replaces the sinks of the previous one, so a repeated init writes no record twice. A sink failing later on (a full disk, a removed log directory) drops its records instead of terminating the process. The records are logged through a single multithreaded (`severity_logger_mt`) logger, so every thread may log at once.

The `LOGE`, `LOGW`, `LOGI`, `LOGD` and `LOGT` macros log with the Boost.Log `error`, `warning`, `info`, `debug` and `trace` severities, and the `MAX_LOG_LEVEL` CMake variable leaves the messages above it out of the build:

```
cmake -S . -B build -DMAX_LOG_LEVEL=5
```
