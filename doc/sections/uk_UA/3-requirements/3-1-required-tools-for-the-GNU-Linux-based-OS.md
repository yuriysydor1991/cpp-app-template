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
