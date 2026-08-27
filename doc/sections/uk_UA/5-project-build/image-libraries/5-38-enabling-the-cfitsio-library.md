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

### Контролер

Клас `cfitsioi::CFITSIOController` з файлу [src/CFITSIO/CFITSIOController.h](/src/CFITSIO/CFITSIOController.h) загортає основні виклики CFITSIO для роботи із зображеннями і тримає один відкритий файл FITS на один екземпляр:

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
| `write_keyword` | `fits_update_key` |
| `last_error` | `fits_get_errstatus` |

Жоден з методів не кидає винятків: кожен повідомляє про результат через значення, що повертається, і залишає код стану CFITSIO виконаного виклику у методі доступу `last_status`.

```
auto fits = cfitsioi::CFITSIOController::create();

fits->create_image("/tmp/image.fits", {8, 4});
fits->write(cfitsioi::CFITSIOController::pixels_buffer(8 * 4, 42.0));
fits->write_keyword("OBJECT", "M31");
fits->close();

fits->open("/tmp/image.fits");

const auto pixels = fits->read();
const auto [width, height] = fits->get_image_size();
```

Метод `app::Application::run` з файлу [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) виконує саме такий цикл запису і читання, тому заміни його тіло власним кодом обробки FITS.
