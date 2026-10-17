### Вмикання компонентних тестів

Для того щоб увімкнути побудову компонентних тестів проекту (виконувані файли `CTEST_DefaultLogger` та `CTEST_LibraryRealLogger` у директоріях `src/log/default-logger/tests/component/` та `src/lib/tests/component/`) необхідно сконфігурувати проект з опцією `ENABLE_COMPONENT_TESTS` встановленою у значення `true` (для GNU/Linux ОС і подібних):

```
# з кореневої директорії проекту

meson setup build -DENABLE_COMPONENT_TESTS=true && meson compile -C build
```

Компонентні тести реєструються через функцію `test()` системи Meson і підхоплюються командою `meson test -C build` разом з юніт-тестами.
