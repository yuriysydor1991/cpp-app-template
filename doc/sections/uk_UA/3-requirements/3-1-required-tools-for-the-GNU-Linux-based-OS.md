## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appWhisperCPP` додатково потребує файлів розробки бібліотеки розпізнавання мовлення [whisper.cpp](https://github.com/ggml-org/whisper.cpp) і бібліотеки [SDL2](https://www.libsdl.org/), якою вона захоплює мікрофон:

```
sudo apt install -y libwhisper-dev libsdl2-dev curl
```

Скрипт `scripts/packages/install-ubuntu.sh` (або `scripts/packages/install-debian.sh`) встановлює їх разом з рештою необхідних пакетів. Пакет whisper.cpp зʼявився у випусках Ubuntu 26.04 і Debian forky, тож у старіших випусках Ubuntu 24.04 і Debian 13 скрипти install-ubuntu-24-04.sh і install-debian-13.sh збирають і встановлюють випуск whisper.cpp v1.9.4 з вихідних кодів, а конфігурація проекту завантажує і збирає їх через мережу Інтернет, якщо встановленої бібліотеки не знайдено. У дистрибутивах на базі RPM відповідні пакети називаються `whisper-cpp-devel` і `SDL2-devel`, а у FreeBSD - `audio/whisper.cpp` і `devel/sdl20` з `pkg`. Конфігурування завантажує модель розпізнавання мовлення інструментом `curl` (або `wget`), дивись розділ [Вмикання розпізнавання мовлення whisper.cpp](/doc/sections/uk_UA/5-project-build/ai/5-58-enabling-the-whisper-cpp-speech-recognition.md).

Каталог [scripts/packages](/scripts/packages) містить скрипти, які встановлюють усі необхідні проекту пакунки за один раз. Скрипти [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) та [install-debian.sh](/scripts/packages/install-debian.sh) запускають скрипт поточного випуску системи - [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) чи [install-debian-13.sh](/scripts/packages/install-debian-13.sh) - оскільки кожен випуск по-своєму називає та версіонує свої пакунки, а на будь-якому іншому випуску завершуються з помилкою та переліком підтримуваних випусків. Залежність, придатної версії якої випуск не пакує, його скрипт будує з вихідних кодів закріпленого тегу її випуску. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) охоплює Fedora, RHEL та його перезбірки, а скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) - FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
