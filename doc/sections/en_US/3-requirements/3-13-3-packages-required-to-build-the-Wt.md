### Packages required to build the Wt

The Wt build needs the Boost and the zlib development packages (Ubuntu 24.04/26.04, Debian 13):

```
sudo apt install -y libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev zlib1g-dev
```

or the Fedora and RHEL ones:

```
sudo dnf install -y boost-devel
```

The [Wt C++ framework](https://www.webtoolkit.eu/wt) supports the set of features that may require additional packages to install into the target OS installation in order to build final binary libraries and project' application executable.

For example, if the [PostgreSQL](https://en.wikipedia.org/wiki/PostgreSQL) is planned to be used through the [Wt's](https://www.webtoolkit.eu/wt) DBO it is required to install required [PostgreSQL's](https://en.wikipedia.org/wiki/PostgreSQL) server and dev libraries.
