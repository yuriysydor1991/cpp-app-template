## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appOpenCV` додатково використовує системні файли розробки [OpenCV](https://opencv.org/) і пакет даних з попередньо встановленими каскадами Хаара, тому їх також необхідно встановити:

```
sudo apt install -y libopencv-dev opencv-data
```

На дистрибутивах на базі RPM відповідні пакети називаються `opencv-devel` і `opencv-data`; на FreeBSD це `graphics/opencv` і `graphics/opencv-data` з `pkg`.
