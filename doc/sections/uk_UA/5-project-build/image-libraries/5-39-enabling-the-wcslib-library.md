## Вмикання інтеграції WCSLIB (FITS WCS)

Для того щоб увімкнути бібліотеку [WCSLIB](https://www.atnf.csiro.au/people/mcalabre/WCS/) (система світових координат FITS, яка відображає пікселі зображення на небесну сферу) для проекту, використовуючи встановлену в системі версію або збираючи її з вихідних кодів, завантажених з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_WCSLIB` (для гілки `appCFITSIO` це значення за замовчуванням):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_WCSLIB=ON
cmake --build build --target all
```

Модуль [cmake/enablers/images/template-project-wcslib-enabler.cmake](/cmake/enablers/images/template-project-wcslib-enabler.cmake) шукає встановлену в системі версію через `pkg-config`. Якщо в системі нічого не знайдено, то натомість завантажується архів вихідних кодів `TEMPLATE_APP_WCSLIB_URL`, який перевіряється за значенням `TEMPLATE_APP_WCSLIB_URL_HASH`. WCSLIB постачається лише зі збіркою autotools, тому функція `template_project_autotools_3rdparty_build` модуля [cmake/tools/template-project-autotools-build-function.cmake](/cmake/tools/template-project-autotools-build-function.cmake) збирає її власним скриптом `configure` та GNU `make` одразу під час конфігурування, один раз на директорію побудови, і встановлює в директорію `_deps/wcslib-install`, де її потім знаходить той самий пошук через `pkg-config`. Для цього шляху потрібні компілятор C, GNU `make` і шлях до директорії побудови без пробілів, оскільки make-файли WCSLIB не беруть свої директорії встановлення в лапки.

Обидва шляхи надають ту саму ціль `WCSLIB::wcslib`, тому прилінковуй її до своїх цільових об'єктів:

```
target_link_libraries(${PROJECT_BINARY_NAME} WCSLIB::wcslib)
```

Завантажена WCSLIB збирається лише як статична бібліотека, тому виконуваний файл містить її в собі й працює в системі без жодної встановленої WCSLIB.

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
