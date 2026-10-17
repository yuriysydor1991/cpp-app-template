## Required package for Firebird connection

To be able to compile the template project against the [Firebird](https://firebirdsql.org/) client library (fbclient) make its development files available by installing them with the next command (GNU/Linux based OS):

```
sudo apt install -y firebird-dev
```

When the system lacks these development files the `cmake/enablers/template-project-firebird-enabler.cmake` enabler fetches the [Firebird](https://firebirdsql.org/) sources (see the `TEMPLATE_APP_FIREBIRD_GIT` and the `TEMPLATE_APP_FIREBIRD_GIT_TAG` CMake cache variables) and builds the client library alone together with the project, which demands the next build tools and libraries (GNU/Linux based OS):

```
sudo apt install -y autoconf automake libtool-bin make unzip zlib1g-dev libicu-dev libncurses-dev
```

The `ENABLE_FIREBIRD` CMake option (`ON` by default) controls the client library. Configured with `-DENABLE_FIREBIRD=OFF` the project neither probes nor fetches the fbclient library and builds without it: the `DisabledFbClient` class takes the place of the driver, so the executable reports that the Firebird support is disabled and exits with a failure status.

In order to install the [Firebird](https://firebirdsql.org/) DBMS server by itself (it also pulls in the `libfbclient2` runtime library) the next command may be used (GNU/Linux based OS, the version suffix may differ between distributions):

```
sudo apt install -y firebird3.0-server
```

### Connection settings

By default the executable connects to the `employee` sample database alias of the local server as the `SYSDBA` user with the `masterkey` password. The defaults live in the `src/app/ApplicationContext.cpp` file - **remember to change the publicly known default credentials!** At the start the next environment variables override them:

| Variable | Setting | Default |
|---|---|---|
| `FIREBIRD_DATABASE` | database alias or file path | `employee` |
| `ISC_USER` | user name | `SYSDBA` |
| `ISC_PASSWORD` | password | `masterkey` |
| `FIREBIRD_HOST` | server host (an empty one keeps the local connection) | empty |
| `FIREBIRD_PORT` | server port, used together with the host | empty (3050) |

For example:

```
FIREBIRD_HOST=localhost FIREBIRD_DATABASE=employee ISC_USER=SYSDBA ISC_PASSWORD='my secret' ./CppAppTemplate
```

The Debian and Ubuntu server packages ask for the `SYSDBA` password during the installation and keep it in the `/etc/firebird/<version>/SYSDBA.password` file as the same `ISC_USER` and `ISC_PASSWORD` shell variables (`sudo dpkg-reconfigure firebird<version>-server` changes it). The packages ship no `employee` database file: the `/usr/share/doc/firebird4.0-examples/examples/README.Debian` file of the `firebird4.0-examples` package (Firebird 4.0) shows how to create it from the bundled SQL script. To connect as a separate user, create it with the `SYSDBA` account in the `isql-fb` tool and pass it through the `ISC_USER` and `ISC_PASSWORD` variables:

```
CREATE USER template_test_user PASSWORD 'template_test_password';
```
