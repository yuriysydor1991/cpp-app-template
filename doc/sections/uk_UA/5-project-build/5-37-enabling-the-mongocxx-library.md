## Вмикання інтеграції драйвера MongoDB для C++

Драйвер [MongoDB для C++](https://www.mongodb.com/docs/languages/cpp/) виконує увесь доступ до бази даних гілки `appMongoDBCpp4`, тому CMake змінна `ENABLE_MONGOCXX` за замовчуванням має значення `ON` і побудова не потребує жодного додаткового параметру для неї:

```
# в середині кореневої директорії проекту

cmake -S . -B build
cmake --build build --target all
```

Модуль [cmake/enablers/template-project-mongocxx-enabler.cmake](/cmake/enablers/template-project-mongocxx-enabler.cmake) шукає встановлений у системі драйвер єдиним викликом `find_package(mongocxx)`, оскільки файл конфігурації пакету драйвера власними викликами find_dependency підтягує пакети bsoncxx та драйвера MongoDB для C. Якщо встановленого у системі драйвера не знайдено, то натомість завантажуються вихідні коди теґу `TEMPLATE_APP_MONGOCXX_GIT_TAG` із репозиторію `TEMPLATE_APP_MONGOCXX_GIT`, які додатково завантажують та збирають драйвер MongoDB для C, якщо у системі також немає пакетів `bson` та `mongoc`, тому машина без встановлених [пакетів розробки MongoDB](/doc/sections/uk_UA/3-requirements/3-11-required-packages-for-the-MongoDB-connection.md) все одно конфігурує та збирає проект. Такі перші конфігурування та побудова потребують часу на увесь набір драйверів, тому тримайте пакети драйвера для C встановленими, щоб його скоротити.

Обидва шляхи надають одні й ті самі цілі `mongo::mongocxx_shared` та `mongo::bsoncxx_shared`, тому компонуйте їх до своїх цілей:

```
target_link_libraries(${PROJECT_BINARY_NAME} mongo::mongocxx_shared mongo::bsoncxx_shared)
```

Модуль [src/mongodbcxx/CMakeLists.txt](/src/mongodbcxx/CMakeLists.txt) компонує їх до виконуваного файлу проекту та до об'єктної бібліотеки `TemplateMongoDBCppConnObj`, так само як це роблять модулі [helpers](/src/mongodbcxx/helpers/CMakeLists.txt) та [converters](/src/mongodbcxx/converters/CMakeLists.txt) для власних об'єктних бібліотек, тому вихідні коди кожного компоненту бачать заголовки драйвера обох шляхів.

Значення `OFF` залишає гілку взагалі без драйвера для компонування, тому встановлюйте його лише разом із заміною компоненту MongoDB на власний.
