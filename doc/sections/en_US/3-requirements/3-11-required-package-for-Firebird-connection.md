## Required package for Firebird connection

To be able to compile the template project against the [Firebird](https://firebirdsql.org/) client library (fbclient) make its development files available by installing them with the next command (GNU/Linux based OS):

```
sudo apt install -y firebird-dev
```

When the system lacks these development files the `cmake/enablers/template-project-firebird-enabler.cmake` enabler fetches the [Firebird](https://firebirdsql.org/) sources (see the `TEMPLATE_APP_FIREBIRD_GIT` and the `TEMPLATE_APP_FIREBIRD_GIT_TAG` CMake cache variables) and builds the client library alone together with the project, which demands the next build tools and libraries (GNU/Linux based OS):

```
sudo apt install -y autoconf automake libtool-bin make unzip zlib1g-dev libicu-dev libncurses-dev
```

In order to install the [Firebird](https://firebirdsql.org/) DBMS server by itself (it also pulls in the `libfbclient2` runtime library) the next command may be used (GNU/Linux based OS, the version suffix may differ between distributions):

```
sudo apt install -y firebird3.0-server
```

The default connection credentials used by the template (`SYSDBA` / `masterkey`) and the default `employee` sample database may be changed in the `ApplicationContext` class or overridden for your own deployment - **remember to change the publicly known default credentials!**
