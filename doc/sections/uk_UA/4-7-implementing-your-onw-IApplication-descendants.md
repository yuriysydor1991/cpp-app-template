## Реалізація власних нащадків IApplication

Абстрактний клас `IApplication` і усі його нащадки винесені у окрему директорію-підкомпонент `src/app/applications` компонента `src/app`:

```
src/app/applications
├── Application.cpp
├── Application.h
├── ApplicationHelpPrinter.cpp
├── ApplicationHelpPrinter.h
├── ApplicationVersionPrinter.cpp
├── ApplicationVersionPrinter.h
├── meson.build
├── IApplication.h
└── tests
    ├── meson.build
    ├── mocks
    │   ├── Application
    │   ├── ApplicationHelpPrinter
    │   └── ApplicationVersionPrinter
    └── unit
        ├── Application
        ├── ApplicationHelpPrinter
        ├── ApplicationVersionPrinter
        └── meson.build
```

Звісно що можна реалізувати окремий новий потомок абстракного класу `IApplication` щоб реалізувати високорівненву варіативність поведінки виконуваного файлу без засмічування незв'язаними `if`-виразами і іншим кодом оригінального класу `Application` (у якому буде міститись реалізація за умовчанням) (пам'ятаймо про принцип Єдиної відповідальності від SOLID).

Створення потомка абстрактного класу `IApplication` може бути виконаним за допомогою прямого безпосереднього створення нового потомка-класу або перевизначенням наявних класів-потомків `IApplication` на подобі `Application`, `ApplicationHelpPrinter` або `ApplicationVersionPrinter`.

Зареєструй новостворений клас-потомок абстрактного класу `IApplication` у методі `create_application` від `ApplicationFactory`, який відповідальний за створення необхідної релазації програми у відповідності до вводу користувача у вигляді параметрів командного рядка.

Це може бути виконаним реалізацією нового потомка класу `ApplicationFactory` і віртальним перевизначенням його створюючих методів на подобі `create_application` і/або інших (потрібно також викликати відповідний статичний метод у головній функції виконуваного бінарного файлу `main` що розміщена у файлі `main.cpp`).

### Де розміщувати файли нового нащадка

1. Файли заголовку і реалізації нового класу необхідно розмістити у директорії `src/app/applications` і додати новий файл `.cpp` до `applications_sources` у файлі побудови `src/app/applications/meson.build`.
1. Модульний тест нового класу необхідно розмістити у директорії `src/app/applications/tests/unit/<ВашаПрограма>` і зареєструвати дану директорію за допомогою виклику `subdir` у файлі побудови `src/app/applications/tests/unit/meson.build`. За приклад можна взяти сусідні модульні тести.
1. Якщо новий клас необхідно підміняти GMock-об'єктом у тестах іншого класу (як це зроблено для модульного тесту класу `ApplicationFactory`), то такий макет необхідно розмістити у файлі `src/app/applications/tests/mocks/<ВашаПрограма>/src/app/applications/<ВашаПрограма>.h` і оголосити його як `MOCK_<ВашаПрограма>` у файлі побудови `src/app/applications/tests/mocks/meson.build`, поруч з макетами сусідніх програм. Власні макети компонента `src/app` залишаються у директорії `src/app/tests/mocks`.
