## Інтеграція Cocoa (AppKit) + Objective-C++

Ця гілка дає швидкий старт для нативної настільної програми macOS, написаної з фреймворком [Cocoa](https://developer.apple.com/documentation/appkit) / AppKit мовою [Objective-C++](https://en.wikipedia.org/wiki/Objective-C%2B%2B) (файли `.mm`, що поєднують C++ та Objective-C). Cocoa - це UI-стек **лише для macOS**, тому компонент тримає все, що може бути платформонезалежним, платформонезалежним і ховає нативний UI за єдиним швом запуску.

### Вимоги

Хост macOS з інструментами командного рядка Xcode (`xcode-select --install`) надає clang з фронтендом Objective-C++ і фреймворк Cocoa. CMake (>= 3.18 на macOS, для мови `OBJCXX` і виклику `find_library(... REQUIRED)`; >= 3.13 для платформонезалежного збирання деінде) керує збиранням нативно: компілює `.mm` як Objective-C++ і лінкує `-framework Cocoa`.

### Структура

- `src/cocoa/CocoaController.{h,cpp}` - об'єкт оркестрації, вільний від Cocoa. Перевіряє контекст програми і запускає GUI через шов `run_cocoa_application()` (`src/cocoa/CocoaLauncher.h`). Збирається і тестується (модульно/компонентно) на будь-якій платформі.
- `src/cocoa/helpers/WindowConfig.{h,cpp}` - незалежний від Cocoa тримач заголовка / текстів / розмірів вікна, тестується ізольовано.
- `src/cocoa/app/CocoaApp.mm` - справжнє визначення `run_cocoa_application()`, яке запускає програму AppKit. **Лише macOS.**
- `src/cocoa/app/TemplateCocoaAppDelegate.{h,mm}` - нативний делегат програми AppKit, який показує головне вікно під час запуску. Його інтерфейс Objective-C захищений `__OBJC__`, тож ціль `cppcheck`, яка перевіряє лише C++, його пропускає. **Лише macOS.**
- `src/cocoa/app/CocoaAppStub.cpp` - визначення `run_cocoa_application()` для не-Apple, щоб виконуваний файл усе одно збирався, лінкувався і запускався (друкуючи повідомлення) поза macOS. Справжнє вікно Cocoa відкривається лише на macOS.
- `src/cocoa/main-window/CocoaMainWindow.{h,mm}` - вікно AppKit `NSWindow`, побудоване програмно (без файлу .xib/.nib) з `WindowConfig`. **Лише macOS.**

`Application::run()` (`src/app/applications/Application.cpp`) створює `CocoaController` і делегує йому, так само як інші GUI-гілки делегують своєму контролеру.

Обробники сигналів програми лише піднімають прапорець зупинки контексту (дивись секцію [Обробка сигналів операційної системи](/doc/sections/uk_UA/4-project-structure/4-8-handling-the-OS-signals.md)), тож `CocoaController` передає у `run_cocoa_application()` запит зупинки, який читає `ApplicationContext::get_stop()`. Делегат програми перевіряє його кожні 100 мс і виходить з циклу подій AppKit, щойно його піднято, тож Ctrl+C, `kill` та інші сигнали зупинки завершують програму звичайним чином.

### Збирання

Нативний UI налаштовує CMake-модуль `cmake/enablers/template-project-Cocoa-enabler.cmake`, що керується `ENABLE_COCOA` (типово `ON`). На macOS він вмикає мову `OBJCXX`, знаходить фреймворк Cocoa і надає ціль `cocoa::sdk` (лінкується з `-framework Cocoa`, компілюється з `-fobjc-arc` для автоматичного підрахунку посилань). На будь-якому іншому хості він нічого не робить, і замість нього збирається шов-заглушка, тож платформонезалежний код продовжує збиратися й тестуватися. На macOS виконуваний файл створюється як пакунок `.app` (`MACOSX_BUNDLE`), ідентифікатором якого є змінна CMake `TEMPLATE_PROJECT_MACOS_BUNDLE_IDENTIFIER` (типово `ua.org.kytok.template.cppapptemplate`; її використовує й інсталятор `.pkg`), тож задай у ній власну назву у зворотному DNS-форматі.

### Пакування

`cmake/enablers/packagers/template-project-macos-package-enabler.cmake` (конфігуруй з `-DENABLE_MACOS_PACKAGE=ON`) під'єднує два генератори CPack: `DragNDrop` (образ диску `.dmg` з `.app` і посиланням для перетягування в Applications) і `productbuild` (інсталятор `.pkg`). Запусти `cpack` у директорії збирання, щоб отримати обидва. Пакунок `.app` встановлюється у корінь префікса встановлення (`BUNDLE DESTINATION .`), тож `.dmg` показує його поруч із посиланням на Applications, а `.pkg` встановлює його як `/Applications/CppAppTemplate.app`. Їхні назви завершуються процесорами, для яких зібрано пакунок `.app`, наприклад `CppAppTemplate-<версія>-arm64.dmg`: `CMAKE_OSX_ARCHITECTURES`, поєднані через `-` (`arm64-x86_64` для універсального пакунку), типово - процесор хоста. Встанови `TEMPLATE_PROJECT_PRODUCTBUILD_IDENTITY` у ідентичність *Developer ID Installer*, щоб підписати `.pkg`.

### Тести

`UTEST_WindowConfig`, `UTEST_CocoaController` (модульні) і `CTEST_Cocoa` (компонентний) перевіряють вільні від Cocoa частини через шов запуску, тож виконуються на будь-якій платформі. Вони зареєстровані у конвеєрі macOS `misc/Jenkinsfile` поруч із тестами програми.
