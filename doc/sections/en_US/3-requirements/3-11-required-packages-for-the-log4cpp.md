## Required packages for the log4cpp

In order to make [log4cpp](https://log4cpp.sourceforge.net/) development packages available for templated project compilation install it with next command (GNU/Linux based OS):

```
sudo apt install -y pkg-config liblog4cpp5-dev
```

The [log4cpp enabler](/doc/sections/en_US/5-project-build/5-37-enabling-the-log4cpp-library.md) fetches and builds the library sources itself when the system carries no such package, so the installation above is an optional one.
