## Вибір типу бібліотеки

Вбудована опція Meson `default_library` будує бібліотеку проекту як спільну, як статичну або як обидві:

| Опція | За умовчанням | Дія |
|---|---|---|
| `-Ddefault_library=shared` | `shared` | Будує спільну бібліотеку `lib<NAME>.so` |
| `-Ddefault_library=static` | | Будує статичну бібліотеку `lib<NAME>.a` |
| `-Ddefault_library=both` | | Будує обидві, користувачі бібліотеки отримують спільну |

Побудова і встановлення статичної бібліотеки:

```
# у кореневій директорії проекту

meson setup build --prefix /usr/local -Ddefault_library=static
ninja -C build
meson install -C build
```

Файл pkg-config і CMake-пакет обслуговують обидва типи однаково, дивись [Встановлення файлів розробки бібліотеки](/doc/sections/uk_UA/5-30-installing-the-library-development-files.md). Чим відрізняється статична бібліотека:

- Файл `<libdir>/lib<NAME>.a` цілком є файлом розробки, тому встановлення лише файлів часу виконання з `-DLIB_INSTALL_DEV_FILES=false` не встановлює бібліотеки взагалі. Тип `both` встановлює його в обох режимах, так само як і символьне посилання `.so`.
- Бібліотека передає своїм користувачам визначення `TEMPLATE_LIB_STATIC` через файл pkg-config і CMake-пакет, і воно прибирає пару `__declspec` ОС MS Windows з макроса `TEMPLATE_LIB_API` у [LibraryAPI.h](/src/lib/facade/public/LibraryAPI.h). Тип `both` будує свою статичну бібліотеку з обʼєктних файлів спільної, тому для ОС MS Windows будуй тип `static`.
- Сторонні бібліотеки, які enabler-модулі додають до бібліотеки (libcurl, libxml2, nlohmann json і OpenCV), стають залежностями лінкування кожного користувача бібліотеки. Файл pkg-config їх перелічує, а CMake-пакет ні - лінкуй їх там вручну.
- Обʼєктні файли статичної бібліотеки стають частиною бінарника, який її лінкує, тому прихована видимість символів більше не розділяє копії підсистеми журналювання двох похідних бібліотек - вони непомітно поділяють один журналювальник. Перейменуй також простір імен `default_logger`, дивись [Перейменування просторів імен бібліотеки](/doc/sections/uk_UA/4-8-the-librarys-installable-include-header-files.md#перейменування-просторів-імен-бібліотеки).

Опцію використовують [meson/template-project-misc-variables-declare/meson.build](/meson/template-project-misc-variables-declare/meson.build) і [src/lib/meson.build](/src/lib/meson.build).
