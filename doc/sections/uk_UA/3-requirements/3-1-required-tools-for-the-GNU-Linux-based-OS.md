## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appRHVoice` додатково потребує файлів розробки бібліотеки синтезу мовлення [RHVoice](https://github.com/RHVoice/RHVoice) разом з її англійськими й українськими голосами і бібліотеки [SDL2](https://www.libsdl.org/), якою вона відтворює мовлення:

```
sudo apt install -y librhvoice-dev rhvoice-english rhvoice-ukrainian libsdl2-dev
```

Скрипт `scripts/packages/install-ubuntu.sh` (або `scripts/packages/install-debian.sh`) встановлює їх разом з рештою необхідних пакетів. Ubuntu бере їх зі свого компонента `multiverse`, а Debian має їх лише в компоненті `non-free`, який спершу треба увімкнути. Дистрибутиви на базі RPM не пакують RHVoice, тож скрипт `scripts/packages/install-redhat.sh` збирає її з вихідних кодів поруч з пакетом `SDL2-devel`, а у FreeBSD пакети називаються `audio/rhvoice` і `devel/sdl20` з `pkg`. Подробиці, ліцензію бібліотеки LGPL-2.1-or-later і власні ліцензії голосів дивись у розділі [Вмикання синтезу мовлення RHVoice](/doc/sections/uk_UA/5-project-build/tts/5-69-enabling-the-RHVoice-speech-synthesis.md).

Каталог [scripts/packages](/scripts/packages) містить скрипти, які встановлюють усі необхідні проекту пакунки за один раз. Скрипти [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) та [install-debian.sh](/scripts/packages/install-debian.sh) запускають скрипт поточного випуску системи - [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) чи [install-debian-13.sh](/scripts/packages/install-debian-13.sh) - оскільки кожен випуск по-своєму називає та версіонує свої пакунки, а на будь-якому іншому випуску завершуються з помилкою та переліком підтримуваних випусків. Залежність, придатної версії якої випуск не пакує, його скрипт будує з вихідних кодів закріпленого тегу її випуску. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) охоплює Fedora, RHEL та його перезбірки, а скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) - FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
