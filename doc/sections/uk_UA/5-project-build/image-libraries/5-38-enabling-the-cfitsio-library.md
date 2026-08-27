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
| `path` | файл FITS для читання або запису |
| `image_size` | ширина і висота зображення, оновлюються при кожному читанні |
| `pixels` | пікселі зображення, у які читають і з яких записують |
| `header` | рядок ключових записів FITS для аналізатора WCS |
| `keywords` | текстові ключові слова заголовку за їх іменами |
| `numeric_keywords` | ключові слова, які запис вносить без лапок |
| `hdu_count` | кількість блоків, з яких складається прочитаний файл |
| `read_header_only` | підніми, щоб прочитати заголовок і пропустити зображення |
| `write_header_only` | підніми, щоб оновити заголовок вже наявного файлу |

Методи доступу `get_pixels` і `get_keywords` повертають змінюване посилання, тому контролер читає напряму у контекст і не копіює цілого зображення по дорозі.

Читання заповнює лише `keywords`, оскільки ключове слово надходить з файлу як текст; `numeric_keywords` є записувальною половиною пари і тримають значення, які мають потрапити до заголовку без лапок, як того потребують аналізатори WCS.

Екземпляр контексту подорожує від компоненту CFITSIO до компоненту WCSLIB, несучи самі лише дані, тому жоден з двох компонентів не посилається на інший.

### Контролер

Уся поверхня класу `cfitsioi::CFITSIOController` з файлу [src/CFITSIO/CFITSIOController.h](/src/CFITSIO/CFITSIOController.h) - це виклики `read` і `write`, кожен з яких приймає єдиний контекст і нічого більше: кожен параметр операції і кожен її результат живуть у цьому контексті.

| Виклик | Що він робить | Виклики CFITSIO за ним |
| --- | --- | --- |
| `read` | заповнює контекст з файлу, на який той вказує | `fits_open_file`, `fits_get_num_hdus`, `fits_hdr2str`, `fits_get_hdrspace`, `fits_read_keyn`, `fits_read_key`, `fits_get_img_param`, `fits_read_img`, `fits_close_file` |
| `write` | записує контекст у файл, на який той вказує | `fits_create_file`, `fits_create_img`, `fits_write_img`, `fits_update_key`, `fits_close_file` |
| `last_error` | описує стан, який залишив невдалий виклик | `fits_get_errstatus` |

Файл відкривається і закривається всередині виклику, тому між викликами екземпляр не тримає ані даних, ані файлу. Повний запис створює зображення наново і перезаписує вже наявний файл, тоді як запис лише заголовку відкриває цей файл і оновлює його ключові слова на місці.

Жоден з викликів не кидає винятків: обидва повідомляють про результат через значення, що повертається, і залишають код стану CFITSIO невдалого виклику у методі доступу `last_status`.

```
auto ctx = cfitsioi::CFITSIOContext::create();
auto fits = cfitsioi::CFITSIOController::create();

ctx->set_path("/tmp/image.fits");
ctx->set_image_size({8, 4});
ctx->set_pixels(cfitsioi::CFITSIOContext::pixels_buffer(8 * 4, 42.0));
ctx->set_keywords({{"OBJECT", "M31"}});
ctx->set_numeric_keywords({{"CRVAL1", 202.4695}});

fits->write(ctx);

auto reading = cfitsioi::CFITSIOContext::create();

reading->set_path("/tmp/image.fits");

fits->read(reading);

const auto& pixels = reading->get_pixels();
const auto [width, height] = reading->get_image_size();
const auto object = reading->get_keywords().at("OBJECT");
```

Читання заповнює контекст цілим заголовком у вигляді рядка ключових записів, який приймають аналізатори FITS WCS, тому дивись [Вмикання інтеграції WCSLIB (FITS WCS)](/doc/sections/uk_UA/5-project-build/image-libraries/5-39-enabling-the-wcslib-library.md) щодо компоненту, який відображає ці пікселі на небесну сферу.

Метод `app::Application::run` з файлу [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) зчитує зображення FITS, на яке вказує параметр командного рядка `--image` (або `-i`), і звітує про нього через журнал проекту, тому заміни його тіло власним кодом обробки FITS.
