### Фреймворк тестів Google Test

На даний момент приклади тестів опираються на фреймворк GTest.

Звісно, скрипти `meson.build` шукають системний фреймворк тестування GTest (pkg-config залежності `gtest`, `gmock` і `gtest_main`) тільки якщо самі тести проекту-шаблону увімкнені Meson-опціями `ENABLE_UNIT_TESTS` або `ENABLE_COMPONENT_TESTS`. Пакети для встановлення наведено у секції [Необов'язкові пакети для тестів](/doc/sections/uk_UA/3-3-optional-for-the-tests.md).
