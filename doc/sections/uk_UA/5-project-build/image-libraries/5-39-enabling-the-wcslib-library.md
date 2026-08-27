## Вмикання інтеграції WCSLIB (FITS WCS)

Для того щоб увімкнути бібліотеку [WCSLIB](https://www.atnf.csiro.au/people/mcalabre/WCS/) (система світових координат FITS, яка відображає пікселі зображення на небесну сферу) для проекту, необхідно встановити значення `ON` для CMake змінної `ENABLE_WCSLIB` (для гілки `appCFITSIO` це значення за замовчуванням):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_WCSLIB=ON
cmake --build build --target all
```

Модуль [cmake/enablers/images/template-project-wcslib-enabler.cmake](/cmake/enablers/images/template-project-wcslib-enabler.cmake) шукає встановлену в системі версію через `pkg-config` і надає ціль `WCSLIB::wcslib`, тому прилінковуй її до своїх цільових об'єктів:

```
target_link_libraries(${PROJECT_BINARY_NAME} WCSLIB::wcslib)
```

На відміну від [модуля CFITSIO](/doc/sections/uk_UA/5-project-build/image-libraries/5-38-enabling-the-cfitsio-library.md), цей модуль не має шляху завантаження з мережі: WCSLIB постачається лише зі збіркою autotools, тому не існує проекту CMake, який `FetchContent` міг би зібрати. Натомість встанови в системі `wcslib-dev` (Debian/Ubuntu), `wcslib-devel` (Fedora/openSUSE) або `astro/wcslib` (FreeBSD).

### Контролер

Клас `wcslibi::WCSLIBController` з файлу [src/WCSLIB/WCSLIBController.h](/src/WCSLIB/WCSLIBController.h) загортає основні виклики WCSLIB і тримає координатні представлення одного заголовку FITS на один екземпляр:

| Метод | Виклик WCSLIB за ним |
| --- | --- |
| `parse` | `wcspih` |
| `select` | `wcsset` |
| `release` | `wcsvfree` |
| `to_world` | `wcsp2s` |
| `to_pixel` | `wcss2p` |
| `last_error` | `wcshdr_errmsg` та `wcs_errmsg` |

Методи доступу `get_representations_count`, `get_axes_count`, `get_axis_type` і `get_rejected_count` зчитують розібрані структури `wcsprm`, тому заголовкові файли WCSLIB залишаються всередині реалізації і код, який підключає контролер, не потребує жодного з них.

Жоден з методів не кидає винятків: кожен повідомляє про результат через значення, що повертається, і залишає код стану WCSLIB виконаного виклику у методі доступу `last_status`.

Контролер є окремим компонентом і не має жодного посилання на компонент CFITSIO: він бере заголовок з того самого екземпляру [cfitsioi::CFITSIOContext](/doc/sections/uk_UA/5-project-build/image-libraries/5-38-enabling-the-cfitsio-library.md), у який компонент CFITSIO цей заголовок зчитує, тому між двома компонентами подорожують самі лише дані.

```
auto ctx = cfitsioi::CFITSIOContext::create();
auto fits = cfitsioi::CFITSIOController::create();
auto wcs = wcslibi::WCSLIBController::create();

ctx->set_path("/tmp/image.fits");
ctx->set_read_header_only(true);

fits->read(ctx);

wcs->parse(ctx);

const auto world = wcs->to_world({4.5, 2.5});
const auto pixel = wcs->to_pixel(world);
```

Заповнений вручну контекст підходить так само, оскільки виклик `parse` читає з нього лише `set_header`.

Піксельна координата рахується від `1.0`, як того вимагає стандарт FITS, а світова містить градуси для небесних осей. Обидві містять одне значення на кожну вісь обраного представлення, а їх кількість повідомляє `get_axes_count`.

Метод `app::Application::run` з файлу [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) зчитує заголовок зображення FITS, на яке вказує параметр командного рядка `--image` (або `-i`), і звітує, куди вказує центр цього зображення, тому заміни його тіло власним кодом обробки координат. Про зображення, заголовок якого не містить ключових слів WCS, звітується без координат, а не з помилкою.
