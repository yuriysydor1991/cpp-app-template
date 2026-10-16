### Пакети необхідні для побудови Wt

Для побудови Wt необхідні пакунки розробника Boost і zlib (Ubuntu 24.04/26.04, Debian 13):

```
sudo apt install -y libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev zlib1g-dev
```

або відповідні пакунки Fedora і RHEL:

```
sudo dnf install -y boost-devel
```

[Wt C++ фреймворк](https://www.webtoolkit.eu/wt) підтримує набір можливостей котрі можуть вимагати встановлення додаткових залежностей на цільову ОС для того щоб побудувати кінцевий бінарний файл і бібліотеки разом з виконуваним файлом проекту.

Наприклад, якщо планується використання СУБД [PostgreSQL](https://en.wikipedia.org/wiki/PostgreSQL) через DBO модуль [Wt C++ фреймворку](https://www.webtoolkit.eu/wt), очевидно, що вимагається встановлення самого [PostgreSQL's](https://en.wikipedia.org/wiki/PostgreSQL) серверу, бібліотек і пакунків розробника.
