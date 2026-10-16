## Required packages for the MySQL

To make available the `mysqlcppconn` library available in the system execute next command (GNU/Linux based OS):

```
sudo apt install libmysqlcppconn-dev
```

In order to execute the application properly make sure that MySQL (or MariaDB) server is installed and running, for example:

```
sudo apt install mariadb-server
```

The application connects to the `127.0.0.1:3306` server as the `template_test_user` user with the `template_test_password` password and selects no database by default (see the `src/app/ApplicationContext.cpp` file). Remember to change these publicly visible credentials! Create the matching user (and, optionally, a database for it) on the server with commands like the next ones:

```
sudo mysql -e "CREATE USER 'template_test_user'@'127.0.0.1' IDENTIFIED BY 'template_test_password';"
sudo mysql -e "CREATE DATABASE template_test_db;"
sudo mysql -e "GRANT ALL PRIVILEGES ON template_test_db.* TO 'template_test_user'@'127.0.0.1';"
```

The next environment variables override the defaults at the application start:

- `MYSQL_HOST` the server host (or a Connector/C++ URL, e.g. `unix:///run/mysqld/mysqld.sock` with an empty `MYSQL_TCP_PORT`);
- `MYSQL_TCP_PORT` the server port;
- `MYSQL_USER` the user name;
- `MYSQL_PASSWORD` the user password;
- `MYSQL_DATABASE` the database to select.

```
MYSQL_USER=my_user MYSQL_PASSWORD=my_password MYSQL_DATABASE=template_test_db ./CppAppTemplate
```
