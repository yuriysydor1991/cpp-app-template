## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appSherpaONNX` додатково потребує файлів розробки бібліотеки [SDL2](https://www.libsdl.org/), якою вона відтворює мовлення, тоді як бібліотеку синтезу мовлення [sherpa-onnx](https://github.com/k2-fsa/sherpa-onnx) конфігурування завантажує і збирає саме (інструментом `git` через доступ до інтернету). sherpa-onnx виконує моделі бібліотекою [onnxruntime](https://github.com/microsoft/onnxruntime) дистрибутиву, якщо той її пакує, а інакше завантажує власну попередньо зібрану:

```
sudo apt install -y libonnxruntime-dev libsdl2-dev
```

Ubuntu 24.04 не пакує onnxruntime, тож там потрібен лише пакет `libsdl2-dev`. Скрипт `scripts/packages/install-ubuntu.sh` (або `scripts/packages/install-debian.sh`) встановлює їх разом з рештою необхідних пакетів. У Fedora відповідні пакети називаються `onnxruntime-devel` і `SDL2-devel` (RHEL onnxruntime не пакує), а у FreeBSD - `misc/onnxruntime` і `devel/sdl20` з `pkg`. Про модель Kokoro, яку завантажує конфігурування, та ліцензії бібліотеки й моделей дивись розділ [Вмикання синтезу мовлення sherpa-onnx](/doc/sections/uk_UA/5-project-build/tts/5-71-enabling-the-sherpa-onnx-speech-synthesis.md).

Каталог [scripts/packages](/scripts/packages) містить скрипти, які встановлюють усі необхідні проекту пакунки за один раз. Скрипти [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) та [install-debian.sh](/scripts/packages/install-debian.sh) запускають скрипт поточного випуску системи - [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) чи [install-debian-13.sh](/scripts/packages/install-debian-13.sh) - оскільки кожен випуск по-своєму називає та версіонує свої пакунки, а на будь-якому іншому випуску завершуються з помилкою та переліком підтримуваних випусків. Залежність, придатної версії якої випуск не пакує, його скрипт будує з вихідних кодів закріпленого тегу її випуску. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) охоплює Fedora, RHEL та його перезбірки, а скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) - FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
