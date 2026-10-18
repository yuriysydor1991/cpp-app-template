## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appPiperTTS` додатково потребує git і доступу до інтернету, оскільки конфігурування збирає бібліотеку синтезу мовлення [Piper](https://github.com/OHF-Voice/piper1-gpl) з її вихідних кодів, файлів розробки бібліотеки [onnxruntime](https://onnxruntime.ai/), якою вона виконує голоси, якщо система її пакує, і бібліотеки [SDL2](https://www.libsdl.org/), якою вона відтворює мовлення:

```
sudo apt install -y git libonnxruntime-dev libsdl2-dev
```

Скрипт `scripts/packages/install-ubuntu.sh` (або `scripts/packages/install-debian.sh`) встановлює їх разом з рештою необхідних пакетів. Ubuntu 24.04 не має пакету `libonnxruntime-dev`, тож там збірка завантажує готову onnxruntime. У дистрибутивах на базі RPM відповідні пакети називаються `onnxruntime-devel` і `SDL2-devel`, а у FreeBSD - `misc/onnxruntime` і `devel/sdl20` з `pkg`. Про ліцензію бібліотеки GPL-3.0-or-later, яку успадковує поширюваний виконуваний файл, і про ліцензії голосів дивись розділ [Вмикання синтезу мовлення Piper](/doc/sections/uk_UA/5-project-build/tts/5-70-enabling-the-Piper-speech-synthesis.md).

Каталог [scripts/packages](/scripts/packages) містить скрипти, які встановлюють усі необхідні проекту пакунки за один раз. Скрипти [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) та [install-debian.sh](/scripts/packages/install-debian.sh) запускають скрипт поточного випуску системи - [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) чи [install-debian-13.sh](/scripts/packages/install-debian-13.sh) - оскільки кожен випуск по-своєму називає та версіонує свої пакунки, а на будь-якому іншому випуску завершуються з помилкою та переліком підтримуваних випусків. Залежність, придатної версії якої випуск не пакує, його скрипт будує з вихідних кодів закріпленого тегу її випуску. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) охоплює Fedora, RHEL та його перезбірки, а скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) - FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
