## Публічні заголовкові файли бібліотеки для встановлення

Директорія [src/lib/facade/public](/src/lib/facade/public) містить публічні заголовкові файли, що підлягають встановленню. Публічні заголовки описують головний фасад реалізованої бібліотеки для зовнішнього коду. Додавай нові класи та/або методи сюди щоб поширювати функціонал на будь-який проект-споживач. Вміст [src/lib/facade/public](/src/lib/facade/public) встановлюється, наприклад, у субдиректорію за замовчуванням `include/CppAppTemplate-0` (ім'я формується з імені проекту і його мажорної версії) відносно сконфігурованого Meson `--prefix`.

Поруч з успішним встановленням бінарної бібліотеки і заголовкових файлів Meson встановлює:

- файл **pkg-config** за шляхом `<prefix>/<libdir>/pkgconfig/CppAppTemplate-0.pc`, щоб проекти-споживачі на Meson могли знаходити бібліотеку через `dependency('CppAppTemplate-0')` (під капотом це pkg-config), а Autotools чи інші системи побудови - через `pkg-config --cflags --libs CppAppTemplate-0`.
- набір **CMake package-config файлів** за шляхом `<prefix>/<libdir>/cmake/CppAppTemplate-0/`:
    - `CppAppTemplate-0Config.cmake`
    - `CppAppTemplate-0ConfigVersion.cmake` (політика сумісності SameMajorVersion)
    - `CppAppTemplate-0Targets.cmake` (з імпортованою ціллю `CppAppTemplate-0::CppAppTemplate-0`)

Проекти-споживачі на CMake можуть використати бібліотеку так:

```
find_package(CppAppTemplate-0 CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE CppAppTemplate-0::CppAppTemplate-0)
```

Обидва набори артефактів генеруються викликами Meson `configure_file` у [src/lib/meson.build](/src/lib/meson.build) із шаблонів, що лежать у [src/lib/cmake/](/src/lib/cmake/). Налаштовуй шаблони і виклик `pkgconfig.generate()` коли бібліотеці потрібні додаткові метадані (наприклад додаткові `Requires:` для pkg-config або `find_dependency()` для CMake).
