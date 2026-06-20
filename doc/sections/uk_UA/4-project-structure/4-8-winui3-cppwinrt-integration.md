## Інтеграція WinUI 3 + C++/WinRT

Ця гілка дає швидкий старт для настільної програми [Microsoft WinUI 3](https://learn.microsoft.com/windows/apps/winui/winui3/), написаної з [C++/WinRT](https://learn.microsoft.com/windows/uwp/cpp-and-winrt-apis/) поверх [Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/). WinUI 3 - це UI-стек **лише для Windows**, тому компонент тримає все, що може бути платформонезалежним, платформонезалежним і ховає нативний UI за єдиним швом запуску.

### Структура

- `src/winui3/WinUI3Initer.{h,cpp}` - об'єкт оркестрації, вільний від WinUI. Перевіряє контекст програми і запускає GUI через шов `run_winui_application()` (`src/winui3/WinUI3Launcher.h`). Збирається і тестується (модульно/компонентно) на будь-якій платформі.
- `src/winui3/helpers/WindowConfig.{h,cpp}` - незалежний від WinUI тримач заголовка / текстів / розмірів вікна, тестується ізольовано.
- `src/winui3/app/WinUI3App.{h,cpp}` - нативний об'єкт програми C++/WinRT і справжнє визначення `run_winui_application()`. **Лише Windows.**
- `src/winui3/app/WinUI3AppStub.cpp` - визначення `run_winui_application()` для не-Windows, щоб виконуваний файл усе одно збирався, лінкувався і запускався (друкуючи повідомлення) поза Windows. Справжнє вікно WinUI 3 відкривається лише на Windows.
- `src/winui3/main-window/WinUI3MainWindow.{h,cpp}` - вікно WinUI 3, побудоване програмно (без XAML-файлу) з `WindowConfig`. **Лише Windows.**

`Application::run()` (`src/app/Application.cpp`) створює `WinUI3Initer` і делегує йому, так само як інші GUI-гілки делегують своєму initer.

### Збирання

Нативний UI налаштовує CMake-модуль `cmake/enablers/template-project-WinUI3-enabler.cmake`, що керується:

- `ENABLE_WINUI3` (типово `ON`) - встанови `OFF`, щоб прибрати інтеграцію з WinUI 3.
- `TEMPLATE_APP_WINAPPSDK_VERSION` / `TEMPLATE_APP_CPPWINRT_VERSION` - версії NuGet-пакетів Windows App SDK і C++/WinRT, що відновлюються на Windows.

На Windows модуль відновлює NuGet-пакети Windows App SDK + C++/WinRT (потрібен NuGet CLI) і надає ціль `winui3::sdk`, з якою лінкується нативний UI; проєкція C++/WinRT (`cppwinrt.exe`) і Windows SDK мають бути присутні (Visual Studio 2022 з робочим навантаженням *Desktop development with C++* і Windows App SDK). На будь-якому іншому хості модуль нічого не робить, і замість нього збирається шов-заглушка, тож платформонезалежний код продовжує збиратися й тестуватися.

> WinUI 3 з CMake - це не типовий шлях від Microsoft (Visual Studio керує WinUI 3 через MSBuild/.vcxproj). Налаштування CMake тут - це відправна точка: оркестрація, шов запуску, тести і пакування WIX уже з'єднані; доведи з'єднання Windows App SDK / проєкції `cppwinrt` на хості Windows, щоб отримати нативне вікно.

### Тести

`UTEST_WindowConfig`, `UTEST_WinUI3Initer` (модульні) і `CTEST_WinUI3` (компонентний) перевіряють вільні від WinUI частини через шов запуску, тож виконуються на будь-якій платформі. Вони зареєстровані у конвеєрі Windows `misc/Jenkinsfile` поруч із тестами програми.
