## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appDarknetXX` додатково потребує файлів розробки бібліотек [OpenCV](https://opencv.org/), [zlib](https://zlib.net/) і [nlohmann JSON](https://github.com/nlohmann/json), з якими збирається мережеве ядро [darknetxx](https://github.com/yuriysydor1991/darknetxx):

```
sudo apt install -y libopencv-dev zlib1g-dev nlohmann-json3-dev
```

Скрипт `scripts/packages/install-ubuntu.sh` (або `scripts/packages/install-debian.sh`) встановлює їх разом з рештою необхідних пакетів. У дистрибутивах на базі RPM відповідні пакети називаються `opencv-devel`, `zlib-devel` і `json-devel`, а у FreeBSD - `graphics/opencv` і `devel/nlohmann-json` з `pkg` (zlib входить до базової системи). Конфігурування завантажує вихідні коди darknetxx інструментом `git` і завантажує ваги мережі, дивись розділ [Вмикання виявлення об'єктів darknetxx](/doc/sections/uk_UA/5-project-build/ai/5-61-enabling-the-darknetxx-object-detection.md).

Каталог [scripts/packages](/scripts/packages) містить скрипти, які встановлюють усі необхідні проекту пакунки за один раз. Скрипти [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) та [install-debian.sh](/scripts/packages/install-debian.sh) запускають скрипт поточного випуску системи - [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) чи [install-debian-13.sh](/scripts/packages/install-debian-13.sh) - оскільки кожен випуск по-своєму називає та версіонує свої пакунки, а на будь-якому іншому випуску завершуються з помилкою та переліком підтримуваних випусків. Залежність, придатної версії якої випуск не пакує, його скрипт будує з вихідних кодів закріпленого тегу її випуску. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) охоплює Fedora, RHEL та його перезбірки, а скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) - FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
