## Інтеграція WinUI 3 + C++/WinRT

Ця гілка дає швидкий старт для настільної програми [Microsoft WinUI 3](https://learn.microsoft.com/windows/apps/winui/winui3/), написаної з [C++/WinRT](https://learn.microsoft.com/windows/uwp/cpp-and-winrt-apis/) поверх [Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/). WinUI 3 - це UI-стек **лише для Windows**, тому компонент тримає все, що може бути платформонезалежним, платформонезалежним і ховає нативний UI за єдиним швом запуску.

### Структура

- `src/winui3/WinUI3Controller.{h,cpp}` - об'єкт оркестрації, вільний від WinUI. Перевіряє контекст програми і запускає GUI через шов `run_winui_application()` (`src/winui3/WinUI3Launcher.h`). Збирається і тестується (модульно/компонентно) на будь-якій платформі.
- `src/winui3/helpers/WindowConfig.{h,cpp}` - незалежний від WinUI тримач заголовка / текстів / розмірів вікна, тестується ізольовано.
- `src/winui3/app/WinUI3App.{h,cpp}` - нативний об'єкт програми C++/WinRT і справжнє визначення `run_winui_application()`. **Лише Windows.**
- `src/winui3/app/WinUI3AppStub.cpp` - визначення `run_winui_application()` для не-Windows, щоб виконуваний файл усе одно збирався, лінкувався і запускався (друкуючи повідомлення) поза Windows. Справжнє вікно WinUI 3 відкривається лише на Windows.
- `src/winui3/main-window/WinUI3MainWindow.{h,cpp}` - вікно WinUI 3, побудоване програмно (без XAML-файлу) з `WindowConfig`. **Лише Windows.**

`Application::run()` (`src/app/applications/Application.cpp`) створює `WinUI3Controller` і делегує йому, так само як інші GUI-гілки делегують своєму контролеру.

### Збирання

Нативний UI налаштовує CMake-модуль `cmake/enablers/template-project-WinUI3-enabler.cmake`, що керується:

- `ENABLE_WINUI3` (типово `ON`) - встанови `OFF`, щоб прибрати інтеграцію з WinUI 3.
- `TEMPLATE_APP_WINAPPSDK_VERSION` / `TEMPLATE_APP_CPPWINRT_VERSION` / `TEMPLATE_APP_WEBVIEW2_VERSION` - версії NuGet-пакетів Windows App SDK, C++/WinRT і WebView2 (залежності Windows App SDK), що відновлюються на Windows.
- `WINUI3_CPPWINRT_GEN` (типово `<директорія збирання>/winui3-cppwinrt`) - директорія згенерованих заголовків проєкції C++/WinRT.

На Windows модуль відновлює NuGet-пакети Windows App SDK, C++/WinRT і WebView2 (потрібен NuGet CLI), генерує відновленим `cppwinrt.exe` заголовки проєкції C++/WinRT (`winrt/*.h`) з метаданих Windows SDK, Windows App SDK і WebView2 (повторно лише після зміни версій пакетів) і надає ціль `winui3::sdk` (C++20, `/bigobj`), з якою лінкується нативний UI; Windows SDK має бути присутній (Visual Studio 2022 з робочим навантаженням *Desktop development with C++*). На будь-якому іншому хості модуль нічого не робить, і замість нього збирається шов-заглушка, тож платформонезалежний код продовжує збиратися й тестуватися.

> WinUI 3 з CMake - це не типовий шлях від Microsoft (Visual Studio керує WinUI 3 через MSBuild/.vcxproj). Виконуваний файл тут - це непакована (unpackaged) програма WinUI 3 лише з коду (без компілятора розмітки XAML): `run_winui_application()` ініціалізує середовище виконання Windows App SDK викликом `MddBootstrapInitialize2()` (на машині має бути встановлене середовище виконання Windows App SDK тієї ж версії major.minor, інакше завантажувач запропонує його завантажити), а збирання копіює `Microsoft.WindowsAppRuntime.Bootstrap.dll` поруч із виконуваним файлом і встановлює його разом із ним.

### Тести

`UTEST_WindowConfig`, `UTEST_WinUI3Controller` (модульні) і `CTEST_WinUI3` (компонентний) перевіряють вільні від WinUI частини через шов запуску, тож виконуються на будь-якій платформі. Вони зареєстровані у конвеєрі Windows `misc/Jenkinsfile` поруч із тестами програми.
