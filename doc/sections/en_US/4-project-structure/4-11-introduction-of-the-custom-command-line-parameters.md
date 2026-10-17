## Introducing custom command line parameters

In order to introduce some additional command line parameters for the binary look for the `CommandLineParser` class implementation. It contains command line parsing routines that are passed by `ApplicationFactory` class after the `main` function was called.

Add some additional custom fields into the `ApplicationContext` class in order to pass some custom command line flags and/or data to the `IApplication` interface abstract class descendants that will be created by the `ApplicationFactory` during command line arguments parse.

All the `ApplicationContext` data members are private ones and are named with the `m` prefix, so declare an appropriate public access methods pair next to every new field, the same way the already available ones are declared: a `get_` prefixed getter and a `set_` prefixed setter (see the `mprint_help_and_exit` field with it's `ApplicationContext::get_print_help_and_exit` and `ApplicationContext::set_print_help_and_exit` methods). Prefer the `std::atomic` based field types whenever the value is shared between multiple threads, the way the `mstop` application stop flag is declared.

The template binary already accepts the next options:

| Option | Effect |
| --- | --- |
| `-h`, `--help` | prints the help message and exits with the zero status |
| `-v`, `--version` | prints the version, the build git commit and the configure date and exits with the zero status |
| `-l <path>`, `--log-file <path>` | appends the log messages to the given file instead of the default one |

The `ApplicationFactory::run` method parses the command line before it initializes the logging, so the help and the version printers open no log file at all. A log file given with the `-l`/`--log-file` option which can not be opened is an error: the binary prints it into the stderr stream and exits with a non-zero status before the application runs. The default log file which can not be opened - the one of a read only current working directory, for example - only gives a warning and the logging goes into the console.

Report a parse error of a new parameter the way the `CommandLineParser` class reports an unknown parameter or a missing parameter value: push its description with the `ApplicationContext::push_error` method, raise the help printing flag with the `ApplicationContext::set_print_help_and_exit` setter and return a `false` value. The `ApplicationHelpPrinter` prints the pushed errors into the stderr stream in front of the help message and returns a non-zero status then, so a bad usage never reports a success. Register every new parameter in the `ApplicationHelpPrinter` help message too.
