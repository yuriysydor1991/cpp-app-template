## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Щоб встановити усі необхідні пакунки розробника GTKmm-4.0 необхідно виконати команду:

```
sudo apt install -y pkg-config libgtkmm-4.0-dev libglib2.0-dev-bin
```

Завантажувач та заголовкові файли Vulkan, що використовуються як для переліку фізичних пристроїв, так і для відмальовування вмісту вікна засобами Vulkan поза екраном з подальшим експортом у вигляді Linux dma-buf для показу у вікні GTK (а також драйвер часу виконання Vulkan з підтримкою експорту dma-buf, наприклад драйвери Mesa для відеокарт):

```
sudo apt install -y libvulkan-dev mesa-vulkan-drivers
```

Гілка потребує GTK / gtkmm версії 4.14 або новішої (для `Gdk::DmabufTexture`): зі старішою gtkmm конфігурування зупиняється. Без придатного середовища виконання Vulkan взагалі (немає завантажувача чи драйвера) або за наявності лише програмного драйвера Vulkan (наприклад lavapipe) експорт dma-buf недоступний, і вікно повертається до простого чорного тла.

Каталог [scripts/packages](/scripts/packages) містить скрипти, які встановлюють усі необхідні проекту пакунки за один раз. Скрипти [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) та [install-debian.sh](/scripts/packages/install-debian.sh) запускають скрипт поточного випуску системи - [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) чи [install-debian-13.sh](/scripts/packages/install-debian-13.sh) - оскільки кожен випуск по-своєму називає та версіонує свої пакунки, а на будь-якому іншому випуску завершуються з помилкою та переліком підтримуваних випусків. Залежність, придатної версії якої випуск не пакує, його скрипт будує з вихідних кодів закріпленого тегу її випуску. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) охоплює Fedora, RHEL та його перезбірки, а скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) - FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
