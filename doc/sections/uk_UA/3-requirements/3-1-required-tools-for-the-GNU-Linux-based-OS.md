## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appESpeakNG` додатково потребує файлів розробки бібліотеки синтезу мовлення [eSpeak NG](https://github.com/espeak-ng/espeak-ng), яку конфігурування знаходить інструментом `pkg-config`, і бібліотеки [SDL2](https://www.libsdl.org/), якою вона відтворює мовлення:

```
sudo apt install -y pkg-config libespeak-ng-dev libsdl2-dev
```

Скрипт `scripts/packages/install-ubuntu.sh` (або `scripts/packages/install-debian.sh`) встановлює їх разом з рештою необхідних пакетів. У дистрибутивах на базі RPM відповідні пакети називаються `espeak-ng-devel`, `SDL2-devel` і `pkgconf-pkg-config`, а у FreeBSD - `audio/espeak-ng`, `devel/sdl20` і `devel/pkgconf` з `pkg`. Про ліцензію бібліотеки GPL-3.0-or-later, яку успадковує поширюваний виконуваний файл, дивись розділ [Вмикання синтезу мовлення eSpeak NG](/doc/sections/uk_UA/5-project-build/tts/5-67-enabling-the-eSpeak-NG-speech-synthesis.md).

Каталог [scripts/packages](/scripts/packages) містить скрипти, які встановлюють усі необхідні проекту пакунки за один раз. Скрипти [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) та [install-debian.sh](/scripts/packages/install-debian.sh) запускають скрипт поточного випуску системи - [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) чи [install-debian-13.sh](/scripts/packages/install-debian-13.sh) - оскільки кожен випуск по-своєму називає та версіонує свої пакунки, а на будь-якому іншому випуску завершуються з помилкою та переліком підтримуваних випусків. Залежність, придатної версії якої випуск не пакує, його скрипт будує з вихідних кодів закріпленого тегу її випуску. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) охоплює Fedora, RHEL та його перезбірки, а скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) - FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
