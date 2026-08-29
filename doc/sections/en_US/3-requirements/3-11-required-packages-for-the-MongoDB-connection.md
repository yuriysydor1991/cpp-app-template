## Required packages for the MongoDB connection

In order to make the MongoDB C driver, which the C++ one of the template project builds upon, available install it with a next command (GNU/Linux based OS):

```
sudo apt install -y libmongoc-dev libbson-dev
```

The archives of the most of the distributions carry no MongoDB C++ driver package at all, so the [mongocxx enabler](/doc/sections/en_US/5-project-build/5-37-enabling-the-mongocxx-library.md) fetches and builds that driver itself when the system carries none. The C driver packages above are the optional ones which spare the fetched sources that part of the build.
