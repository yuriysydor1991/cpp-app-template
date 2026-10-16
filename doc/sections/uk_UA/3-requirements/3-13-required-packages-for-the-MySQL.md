## Обов'язкові пакети для підключення до MySQL

Для того щоб зробити доступною бібліотеку `mysqlcppconn` у наявній системі необхідно виконати команду подібну до наступної (ОС на базі GNU/Linux):

```
sudo apt install libmysqlcppconn-dev
```

Щоб програма успішно підключалась до цільового СУБД MySQL (або MariaDB) серверу необхідно переконатись що він встановлений, працює і доступний для мережевого підключення, наприклад:

```
sudo apt install mariadb-server
```

Типово програма підключається до сервера `127.0.0.1:3306` від імені користувача `template_test_user` з паролем `template_test_password` і не обирає жодної бази даних (див. файл `src/app/ApplicationContext.cpp`). Не забудь змінити ці публічно відомі облікові дані! Створи відповідного користувача (і, за потреби, базу даних для нього) на сервері командами подібними до наступних:

```
sudo mysql -e "CREATE USER 'template_test_user'@'127.0.0.1' IDENTIFIED BY 'template_test_password';"
sudo mysql -e "CREATE DATABASE template_test_db;"
sudo mysql -e "GRANT ALL PRIVILEGES ON template_test_db.* TO 'template_test_user'@'127.0.0.1';"
```

Наступні змінні середовища замінюють типові значення під час запуску програми:

- `MYSQL_HOST` хост сервера (або URL для Connector/C++, наприклад `unix:///run/mysqld/mysqld.sock` разом з порожньою `MYSQL_TCP_PORT`);
- `MYSQL_TCP_PORT` порт сервера;
- `MYSQL_USER` ім'я користувача;
- `MYSQL_PASSWORD` пароль користувача;
- `MYSQL_DATABASE` база даних, яку слід обрати.

```
MYSQL_USER=my_user MYSQL_PASSWORD=my_password MYSQL_DATABASE=template_test_db ./CppAppTemplate
```

Ці ж змінні використовують компонентні тести `CTEST_MySQLController`, котрі пропускаються, якщо з ними не вдається підключитись до жодного сервера.
