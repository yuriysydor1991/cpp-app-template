## Required package for PostgreSQL connection

To be able to compile the template project with the PostgreSQL C++ bind library make it available by installing it with next command (GNU/Linux based OS):

```
sudo apt install -y libpqxx-dev
```

In order to install the [PostgreSQL](https://en.wikipedia.org/wiki/PostgreSQL) DBMS by itself the next command may be used (GNU/Linux based OS):

```
sudo apt install -y postgresql
```

### Connection credentials

The executable connects to the `postgres` database at the `localhost` server (TCP, default port 5432) as the `template_test_user` user with the `template_test_password` password. The defaults live in the `src/app/ApplicationContext.cpp` file, so change them for your application. At the start the libpq environment variables `PGHOST`, `PGPORT`, `PGDATABASE`, `PGUSER` and `PGPASSWORD` override them, for example:

```
PGHOST=db.example.org PGUSER=my_user PGPASSWORD='my secret' ./CppAppTemplate
```

Every value is quoted in the connection string, so passwords with spaces or quotes work as they are.

A freshly installed server knows no such user yet, so create it with the PostgreSQL superuser (GNU/Linux based OS):

```
sudo -u postgres psql -c "CREATE ROLE template_test_user LOGIN PASSWORD 'template_test_password';"
```

The `postgres` database accepts every user by default, which is enough for the demonstration `SELECT CURRENT_DATE;` query. For a database of your own run `sudo -u postgres createdb -O template_test_user <name>` and pass the `<name>` through the `PGDATABASE` variable.
