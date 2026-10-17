## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake pkg-config libsystemd-dev
```

Інструмент `pkg-config` і файли `libsystemd-dev` потрібні для збирання та лінкування бібліотеки [sdbus-c++](/doc/sections/uk_UA/3-requirements/3-13-required-packages-for-the-sdbus-cpp.md) цієї гілки.
