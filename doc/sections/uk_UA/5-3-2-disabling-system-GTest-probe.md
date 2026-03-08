### Запобігання використання GTest з ОС

Для вимкнення використання ресурсів наявного фреймворку GTest необхідно встановити відповідне значення для Meson-змінної `GTEST_TRY_SYSTEM_PROBE` за допомогою команди конфігурування проекту (для GNU/Linux):

```
# з кореневої директорії проекту-шаблону
# поки-о не спрацює !!!

meson setup build -DENABLE_UNIT_TESTS=true -DGTEST_TRY_SYSTEM_PROBE=true && meson compile -C build
```
