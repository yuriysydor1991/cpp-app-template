## Вмикання перевірок під час виконання програми (sanitizers)

Для того щоб увімкнути додаткові перевірки бібліотеки та її тестів під час виконання необхідно сконфігурувати проект з увімкненою змінною `ENABLE_SANITIZERS`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_SANITIZERS=ON -DENABLE_UNIT_TESTS=ON -DENABLE_COMPONENT_TESTS=ON
```

Для вмикання загальних перевірок. Деталі і список прапорців перевірок у файлі `cmake/compile-options/sanitizers/template-project-sanitizers.cmake`. Конвеєри CI будують тести саме так.

Також присутня можливість вмикання перевірок виконання потоків на предмет перегонів даних (data races) наступною командою:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_SANITIZERS_THREADS=ON -DENABLE_UNIT_TESTS=ON -DENABLE_COMPONENT_TESTS=ON
```

Не слід поєднувати `ENABLE_SANITIZERS` і `ENABLE_SANITIZERS_THREADS`.

Будь-які знахідки увімкнених перевірок друкуються у стандартні потоки виводу (stdout/stderr) тесту (або будь-якої іншої програми, зібраної з інструментованою бібліотекою) під час його виконання, наприклад командою `ctest`.
