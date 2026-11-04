## Вибір типу бібліотеки

Опція `LIB_TYPE` будує бібліотеку проекту або як спільну, або як статичну:

| Опція | За умовчанням | Дія |
|---|---|---|
| `-DLIB_TYPE=SHARED` | `SHARED` | Будує спільну бібліотеку `lib<NAME>.so` |
| `-DLIB_TYPE=STATIC` | | Будує статичну бібліотеку `lib<NAME>.a` |

Якщо `LIB_TYPE` не задано, статичну бібліотеку обирає також `-DBUILD_SHARED_LIBS=OFF` (його передають менеджери пакетів vcpkg і Conan).

Побудова і встановлення статичної бібліотеки:

```
# у кореневій директорії проекту

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DLIB_TYPE=STATIC
cmake --build build
cmake --install build --prefix /usr/local
```

Проекти-споживачі на CMake використовують обидва типи однаково, дивись [Встановлення файлів розробки бібліотеки](/doc/sections/uk_UA/5-project-build/5-37-installing-the-library-development-files.md). Чим відрізняється статична бібліотека:

- Виконуваний файл проекту сам містить код статичної бібліотеки: йому не потрібен RUNPATH, він поділяє з бібліотекою одну копію підсистеми журналювання, а його встановлення з `-DLIB_INSTALL_DEV_FILES=OFF` складається лише з виконуваного файлу.
- Файл `<libdir>/lib<NAME>.a` цілком є файлом розробки, тому встановлення лише файлів часу виконання з `-DLIB_INSTALL_DEV_FILES=OFF` не встановлює бібліотеки взагалі.
- Бібліотека передає своїм користувачам визначення `TEMPLATE_LIB_STATIC` через CMake-пакет, і воно прибирає пару `__declspec` ОС MS Windows з макроса `TEMPLATE_LIB_API` у [LibraryAPI.h](/src/lib/facade/public/LibraryAPI.h). Визначай його вручну, якщо лінкуєш бібліотеку в ОС MS Windows без CMake-пакету.
- Сторонні бібліотеки, які enabler-модулі лінкують у бібліотеку (libcurl, libxml2, nlohmann json, OpenCV і OpenSSL), стають залежностями лінкування кожного користувача бібліотеки. Знаходь їх у [TemplateLibraryConfig.cmake.in](/src/lib/cmake/TemplateLibraryConfig.cmake.in) перед його рядком `include()`, наприклад `include(CMakeFindDependencyMacro)` і за ним `find_dependency(CURL)` для libcurl.
- Обʼєктні файли статичної бібліотеки стають частиною бінарника, який її лінкує, тому прихована видимість символів більше не розділяє копії підсистеми журналювання двох похідних бібліотек - вони непомітно поділяють один журналювальник. Перейменуй також простір імен `default_logger`, дивись [Перейменування просторів імен бібліотеки](/doc/sections/uk_UA/4-project-structure/4-9-the-librarys-installable-include-header-files.md#перейменування-просторів-імен-бібліотеки).

Опція оголошена у [cmake/template-project-misc-variables-declare.cmake](/cmake/template-project-misc-variables-declare.cmake) і використовується у [src/lib/CMakeLists.txt](/src/lib/CMakeLists.txt).
