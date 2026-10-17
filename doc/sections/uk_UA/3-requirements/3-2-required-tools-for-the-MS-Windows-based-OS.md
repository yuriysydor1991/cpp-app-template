## Обов'язкові інструменти для ОС на базі MS Windows

Для того щоб мати можливість розробляти і будувати проект необхідно завантажити MSVC інсталятор з сторінки [https://visualstudio.microsoft.com/downloads/](https://visualstudio.microsoft.com/downloads/) і увімкнути встановлення інструментів для нативної розробки на C++ (робоче навантаження **Desktop development with C++**). Для графічного інтерфейсу WinUI 3 цієї гілки також встанови компонент **Windows App SDK C++ templates** (для WinUI 3 / C++/WinRT потрібна Visual Studio 2022).

Окремо інсталятор на кожен необхідний проект можна завантажити з окремих джерел (**можлива необхідність пошуку і встановлення інших пакунків**):
- Система вірсіювання Git за адресою [https://git-scm.com/downloads/win](https://git-scm.com/downloads/win)
- Система побудови CMake за адресою [https://cmake.org/download/](https://cmake.org/download/)
- Пакунки Windows 10 SDK за адресою [https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/)
- Windows App SDK (WinUI 3) - відновлюється під час конфігурування CMake як NuGet-пакет `Microsoft.WindowsAppSDK` (разом із пакетами C++/WinRT і WebView2); див. розділ [Інтеграція WinUI 3 + C++/WinRT](/doc/sections/uk_UA/4-project-structure/4-8-winui3-cppwinrt-integration.md)
- NuGet CLI за адресою [https://www.nuget.org/downloads](https://www.nuget.org/downloads) - використовується для відновлення пакетів Windows App SDK, C++/WinRT і WebView2
