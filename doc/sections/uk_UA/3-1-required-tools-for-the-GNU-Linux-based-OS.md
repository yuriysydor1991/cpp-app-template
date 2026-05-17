## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови Meson, Ninja і системою версіювання Git:

```
sudo apt install -y git g++ meson ninja-build pkg-config
```

Гілка містить опціональні Meson-модулі для декількох сторонніх бібліотек (за замовчуванням усі вимкнені). Встановлюй лише ті пакети, які плануєш увімкнути відповідним прапорцем `-DENABLE_*=true`. Повна таблиця у розділі [Додаткові можливості Meson](/doc/sections/uk_UA/5-19-meson-extra-features.md).

```
# інтеграція libcurl (-DENABLE_LIBCURL=true)
sudo apt install -y libcurl4-openssl-dev

# інтеграція libxml2 (-DENABLE_LIBXML2=true)
sudo apt install -y libxml2-dev

# інтеграція nlohmann_json (-DENABLE_NLOHMANN_JSON=true)
sudo apt install -y nlohmann-json3-dev

# інтеграція OpenCV (-DENABLE_OPENCV=true) - разом з попередньо встановленими каскадами Хаара
sudo apt install -y libopencv-dev opencv-data
```
