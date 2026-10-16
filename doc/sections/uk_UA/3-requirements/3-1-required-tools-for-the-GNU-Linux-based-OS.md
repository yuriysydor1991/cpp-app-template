## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Усі необхідні пакунки розробника для GTKmm-3.0:

```
sudo apt install -y pkg-config libgtkmm-3.0-dev
```

Для того щоб мати змогу розробляти візуальний інтерфейс необіхдно встановити спеціалізований інструмент розробки [Glade](https://en.wikipedia.org/wiki/Glade_Interface_Designer) за допомогою команди (для побудови він не потрібен, а Ubuntu 26.04 не містить пакунку glade, тому сценарій `scripts/packages/install-debian.sh` встановлює його лише там, де він доступний):

```
sudo apt install -y glade
```

Каталог [scripts/packages](/scripts/packages) містить скрипти, які встановлюють усі необхідні проекту пакунки за один раз. Скрипти [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) та [install-debian.sh](/scripts/packages/install-debian.sh) запускають скрипт поточного випуску системи - [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) чи [install-debian-13.sh](/scripts/packages/install-debian-13.sh) - оскільки кожен випуск по-своєму називає та версіонує свої пакунки, а на будь-якому іншому випуску завершуються з помилкою та переліком підтримуваних випусків. Залежність, придатної версії якої випуск не пакує, його скрипт будує з вихідних кодів закріпленого тегу її випуску. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) охоплює Fedora, RHEL та його перезбірки, а скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) - FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
