## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appWhisperCPP` додатково потребує файлів розробки бібліотеки розпізнавання мовлення [whisper.cpp](https://github.com/ggml-org/whisper.cpp) і бібліотеки [SDL2](https://www.libsdl.org/), якою вона захоплює мікрофон:

```
sudo apt install -y libwhisper-dev libsdl2-dev curl
```

Скрипт `scripts/packages/install-ubuntu.sh` (або `scripts/packages/install-debian.sh`) встановлює їх разом з рештою необхідних пакетів. Пакет whisper.cpp зʼявився у випусках Ubuntu 26.04 і Debian forky, тож у старіших випусках вихідні коди whisper.cpp натомість завантажуються і збираються через мережу Інтернет. У дистрибутивах на базі RPM відповідні пакети називаються `whisper-cpp-devel` і `SDL2-devel`, а у FreeBSD - `audio/whisper.cpp` і `devel/sdl20` з `pkg`. Конфігурування завантажує модель розпізнавання мовлення інструментом `curl` (або `wget`), дивись розділ [Вмикання розпізнавання мовлення whisper.cpp](/doc/sections/uk_UA/5-project-build/ai/5-58-enabling-the-whisper-cpp-speech-recognition.md).
