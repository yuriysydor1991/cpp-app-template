### Запуск згенерованого виконуваного файлу

Якщо виконуваний бінарний файл скомпільований і наявний у директорії побудови проекту його можна запустити з терміналу використовуючи шлях знайдений з попередньої секції командою:

```
# наприклад, з директорії побудови

./src/CppAppTemplate
```

І ще раз, ім'я `CppAppTemplate` являється ім'ям головного виконуваного бінарного файлу за замовчуванням. Його необхідно замінити у разі заміни ім'я за умовчанням у кореневому файлі `CMakeLists.txt` (змінні `CMAKE_PROJECT_NAME` або `PROJECT_BINARY_NAME`).

Побудова WebAssembly гілки `appWebAssembly` натомість генерує сторінку `./src/CppAppTemplate.html`, яку команда `emrun ./src/CppAppTemplate.html` відкриває у браузері, як описує розділ [Побудова бінарного файлу WebAssembly для браузерів](/doc/sections/uk_UA/5-project-build/platforms/5-74-building-the-WebAssembly-binary-for-the-browsers.md).
