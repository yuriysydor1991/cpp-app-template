## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appCFITSIO` додатково шукає системні файли розробки [CFITSIO](https://heasarc.gsfc.nasa.gov/fitsio/) та [WCSLIB](https://www.atnf.csiro.au/people/mcalabre/WCS/) за допомогою `pkg-config`, тому їх варто також встановити:

```
sudo apt install -y pkg-config libcfitsio-dev wcslib-dev
```

На дистрибутивах на базі RPM відповідні пакети називаються `pkgconf-pkg-config`, `cfitsio-devel` і `wcslib-devel`; на FreeBSD це `devel/pkgconf`, `astro/cfitsio` і `astro/wcslib` з `pkg`. Без пакету CFITSIO його вихідні коди натомість завантажуються і збираються з мережі, для чого додатково потрібні файли розробки zlib (`zlib1g-dev`). Без пакету WCSLIB натомість завантажується і збирається власним скриптом `configure` архів її вихідних кодів, для чого потрібні компілятор C, GNU `make` (обидва входять до `build-essential`) і шлях до директорії побудови без пробілів.

Каталог [scripts/packages](/scripts/packages) містить скрипти, які встановлюють усі необхідні проекту пакунки за один раз. Скрипти [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) та [install-debian.sh](/scripts/packages/install-debian.sh) запускають скрипт поточного випуску системи - [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) чи [install-debian-13.sh](/scripts/packages/install-debian-13.sh) - оскільки кожен випуск по-своєму називає та версіонує свої пакунки, а на будь-якому іншому випуску завершуються з помилкою та переліком підтримуваних випусків. Залежність, придатної версії якої випуск не пакує, його скрипт будує з вихідних кодів закріпленого тегу її випуску. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) охоплює Fedora, RHEL та його перезбірки, а скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) - FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
