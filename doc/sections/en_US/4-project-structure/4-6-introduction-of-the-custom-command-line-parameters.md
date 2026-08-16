## Introducing custom command line parameters

In order to introduce some additional command line parameters for the binary look for the `CommandLineParser` class implementation. It contains command line parsing routines that are passed by `ApplicationFactory` class after the `main` function was called.

Add some additional custom fields into the `ApplicationContext` class in order to pass some custom command line flags and/or data to the `IApplication` interface abstract class descendants that will be created by the `ApplicationFactory` during command line arguments parse.

All the `ApplicationContext` data members are private ones and are named with the `m` prefix, so declare an appropriate public access methods pair next to every new field, the same way the already available ones are declared: a `get_` prefixed getter and a `set_` prefixed setter (see the `mprint_help_and_exit` field with it's `ApplicationContext::get_print_help_and_exit` and `ApplicationContext::set_print_help_and_exit` methods). Prefer the `std::atomic` based field types whenever the value is shared between multiple threads, the way the `mstop` application stop flag is declared.

Some or all `ApplicationContext` fields may be transferred into the `LibraryContext` instance by the `ApplicationContext2LibraryContext` converter class instance during the `LibMain` default implementation call. Examine the `Application` default application implementation.