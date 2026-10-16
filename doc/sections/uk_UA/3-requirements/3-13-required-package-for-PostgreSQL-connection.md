## Обов'язкові пакунки для підключення до PostgreSQL

Для того щоб мати можливість скомпілювати проект і підключатись до СКБД [PostgreSQL](https://en.wikipedia.org/wiki/PostgreSQL) необхідно встановити відповідний пакунок наступною командою (ОС на базі GNU/Linux):

```
sudo apt install -y libpqxx-dev
```

Для встановлення самої СКБД [PostgreSQL](https://en.wikipedia.org/wiki/PostgreSQL) можна використати наступну команду (ОС на базі GNU/Linux):

```
sudo apt install -y postgresql
```

### Облікові дані для підключення

Виконуваний файл підключається до бази даних `postgres` на сервері `localhost` (TCP, типовий порт 5432) від імені користувача `template_test_user` з паролем `template_test_password`. Типові значення визначені у файлі `src/app/ApplicationContext.cpp`, тож зміни їх для свого застосунку. Під час запуску їх перевизначають змінні середовища libpq `PGHOST`, `PGPORT`, `PGDATABASE`, `PGUSER` та `PGPASSWORD`, наприклад:

```
PGHOST=db.example.org PGUSER=my_user PGPASSWORD='my secret' ./CppAppTemplate
```

Кожне значення береться в лапки у рядку підключення, тож паролі з пробілами чи лапками працюють без змін.

Щойно встановлений сервер ще не має такого користувача, тож створи його від імені суперкористувача PostgreSQL (ОС на базі GNU/Linux):

```
sudo -u postgres psql -c "CREATE ROLE template_test_user LOGIN PASSWORD 'template_test_password';"
```

База даних `postgres` типово приймає будь-якого користувача, чого достатньо для демонстраційного запиту `SELECT CURRENT_DATE;`. Для власної бази даних виконай `sudo -u postgres createdb -O template_test_user <назва>` і передай `<назва>` через змінну `PGDATABASE`.
