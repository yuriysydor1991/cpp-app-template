## Вмикання інтеграції CFITSIO (FITS)

Для того щоб увімкнути бібліотеку [CFITSIO](https://heasarc.gsfc.nasa.gov/fitsio/) (астрономічний формат зображень FITS) для проекту, використовуючи встановлену в системі версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_CFITSIO` (для гілки `appCFITSIO` це значення за замовчуванням):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_CFITSIO=ON
cmake --build build --target all
```

Модуль [cmake/enablers/images/template-project-cfitsio-enabler.cmake](/cmake/enablers/images/template-project-cfitsio-enabler.cmake) шукає встановлену в системі версію через `pkg-config`, оскільки кожна установка CFITSIO містить файл `cfitsio.pc`, тоді як пакетний файл CMake постачається лише разом зі встановленням через CMake. Якщо в системі нічого не знайдено, то натомість завантажуються вихідні коди тегу `TEMPLATE_APP_CFITSIO_GIT_TAG` з репозиторію `TEMPLATE_APP_CFITSIO_GIT`, для збирання яких необхідні файли розробки zlib.

Обидва шляхи надають ту саму ціль `CFITSIO::cfitsio`, тому прилінковуй її до своїх цільових об'єктів:

```
target_link_libraries(${PROJECT_BINARY_NAME} CFITSIO::cfitsio)
```

### Контекст

Обидва власні компоненти працюють через клас `cfitsioi::CFITSIOContext` з файлу [src/CFITSIO/CFITSIOContext.h](/src/CFITSIO/CFITSIOContext.h). Це звичайний тримач даних, оголошений так само, як і `app::ApplicationContext`: приватні поля, доступні виключно через пару методів доступу з префіксами `get_` і `set_`.

| Поле | Що воно тримає |
| --- | --- |
| `path` | файл FITS, який контролер відкриває або створює |
| `image_size` | ширина і висота зображення, оновлюються при кожному читанні |
| `pixels` | пікселі зображення, у які читають і з яких записують |
| `header` | рядок ключових записів FITS для аналізатора WCS |

Метод доступу `get_pixels` повертає змінюване посилання, тому контролер читає ціле зображення напряму у контекст і не копіює його по дорозі.

Екземпляр контексту подорожує від компоненту CFITSIO до компоненту WCSLIB, несучи самі лише дані, тому жоден з двох компонентів не посилається на інший.

### Контролер

Клас `cfitsioi::CFITSIOController` з файлу [src/CFITSIO/CFITSIOController.h](/src/CFITSIO/CFITSIOController.h) загортає основні виклики CFITSIO для роботи із зображеннями, тримає один відкритий файл FITS на один екземпляр і не тримає власних даних: кожен виклик нижче або бере вхідні дані з наданого контексту, або записує свій результат у нього.

| Метод | Виклик CFITSIO за ним |
| --- | --- |
| `open` | `fits_open_file` |
| `create_image` | `fits_create_file` та `fits_create_img` |
| `close` | `fits_close_file` |
| `get_image_size` | `fits_get_img_param` |
| `get_hdu_count` | `fits_get_num_hdus` |
| `read` | `fits_read_img` |
| `write` | `fits_write_img` |
| `read_keyword` | `fits_read_key` |
| `write_keyword` | `fits_update_key`, з рядковим і числовим перевантаженням |
| `read_header` | `fits_hdr2str` |
| `last_error` | `fits_get_errstatus` |

Жоден з методів не кидає винятків: кожен повідомляє про результат через значення, що повертається, і залишає код стану CFITSIO виконаного виклику у методі доступу `last_status`.

```
auto ctx = cfitsioi::CFITSIOContext::create();
auto fits = cfitsioi::CFITSIOController::create();

ctx->set_path("/tmp/image.fits");
ctx->set_image_size({8, 4});
ctx->set_pixels(cfitsioi::CFITSIOContext::pixels_buffer(8 * 4, 42.0));

fits->create_image(ctx);
fits->write(ctx);
fits->write_keyword("OBJECT", "M31");
fits->close();

fits->open(ctx);
fits->read(ctx);
fits->read_header(ctx);

const auto& pixels = ctx->get_pixels();
const auto [width, height] = ctx->get_image_size();
```

Виклик `read_header` заповнює контекст цілим заголовком у вигляді рядка ключових записів, який приймають аналізатори FITS WCS, тому дивись [Вмикання інтеграції WCSLIB (FITS WCS)](/doc/sections/uk_UA/5-project-build/image-libraries/5-39-enabling-the-wcslib-library.md) щодо компоненту, який відображає ці пікселі на небесну сферу.

Метод `app::Application::run` з файлу [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) зчитує зображення FITS, на яке вказує параметр командного рядка `--image` (або `-i`), і звітує про нього через журнал проекту, тому заміни його тіло власним кодом обробки FITS.
