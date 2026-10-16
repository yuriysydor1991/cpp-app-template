## Required packages for the SQLiteCpp

The template project works with the [SQLite](https://www.sqlite.org/) database engine through the [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp) C++ wrapper. Install its development package with the next command (GNU/Linux based OS):

```
sudo apt install -y libsqlitecpp-dev
```

If CMake finds no installed SQLiteCpp, the project configuration fetches its sources from the `TEMPLATE_APP_SQLITECPP_GIT` repository at the `TEMPLATE_APP_SQLITECPP_GIT_TAG` tag (`https://github.com/SRombauts/SQLiteCpp.git` and `3.3.3` by default) and builds them together with the project, so the Git tool and an Internet connection are required then. Both cache variables may be changed during the configuration, for example:

```
cmake -S . -B build -DTEMPLATE_APP_SQLITECPP_GIT_TAG=3.3.3
```

The flatpak package and the Jenkins pipeline Docker image build the SQLiteCpp from the same repository and tag.

### The database file location

The SQLite needs no database server: the executable opens (and creates, if absent) the `<project name><version>.db` database file (for example `CppAppTemplate0.11.0.db`) inside the `$XDG_DATA_HOME/<project name>` directory, or inside the `~/.local/share/<project name>` directory when the `XDG_DATA_HOME` environment variable is not set. The missing directories get created too.

Set the `SQLITE_DB_PATH` environment variable to use another database file:

```
SQLITE_DB_PATH=/path/to/the/database.db ./CppAppTemplate
```
