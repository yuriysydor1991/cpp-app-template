## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Щоб зробити доступною бібліотеку [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) можна скористатися наступною командою:

```
sudo apt install -y libsdl2-dev libsdl2-doc \
  libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0 \
  libsdl2-mixer-dev libsdl2-net-2.0-0 libsdl2-net-dev \
  libsdl2-ttf-dev
```
