## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Саму бібліотеку wxWidgets завантажує і будує з вихідних кодів механізм CMake FetchContent (див. секцію [wxWidgets через FetchContent](/doc/sections/uk_UA/4-6-wxwidgets-fetchcontent-integration.md)), тому встановлювати окремий пакунок wxWidgets не потрібно. На GNU/Linux wxWidgets будує свій бекенд GTK, отож необхідно встановити пакунки розробника GTK:

```
sudo apt install -y pkg-config libgtk-3-dev
```
