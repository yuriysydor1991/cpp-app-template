## Вмикання інтеграції liblzma

Для того щоб увімкнути бібліотеку стиснення [liblzma](https://tukaani.org/xz/) (XZ Utils) (`.xz` / LZMA2, застарілий `.lzma`) для проекту, використовуючи встановлену версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_LIBLZMA`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_LIBLZMA=ON
```

Дивись модуль `cmake/enablers/compression/template-project-liblzma-enabler.cmake` щодо цілей (`LibLZMA::LibLZMA` для системної версії, `liblzma` для побудови через FetchContent), які слід прилінкувати до твоїх цільових об'єктів.

### Стиснення потрібних даних (приклади для копіювання)

Після `ENABLE_LIBLZMA=ON` та прилінкування цілі liblzma (наприклад `target_link_libraries(${PROJECT_BINARY_NAME} LibLZMA::LibLZMA)`) підключи `<lzma.h>` і скопіюй будь-який зі сніпетів нижче.

Найшвидший спосіб стиснути потрібний буфер — за один виклик, у пам'яті, у контейнер `.xz` (LZMA2):

```cpp
#include <lzma.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

// preset: 0..9, за бажанням з LZMA_PRESET_EXTREME. LZMA_CHECK_CRC64 — типова
// перевірка цілісності формату .xz.
std::vector<uint8_t> xz_compress(const std::vector<uint8_t>& input,
                                 uint32_t preset = LZMA_PRESET_DEFAULT)
{
  std::vector<uint8_t> out(lzma_stream_buffer_bound(input.size()));
  std::size_t out_pos = 0;
  lzma_ret rc = lzma_easy_buffer_encode(preset, LZMA_CHECK_CRC64, nullptr,
                                        input.data(), input.size(), out.data(),
                                        &out_pos, out.size());
  if (rc != LZMA_OK) {
    throw std::runtime_error("lzma_easy_buffer_encode failed");
  }
  out.resize(out_pos);
  return out;
}

// Розмір розпакованих даних не зберігається у потоці .xz, тож збільшуй вихідний
// буфер і повторюй, доки декодер повідомляє про брак місця.
std::vector<uint8_t> xz_uncompress(const std::vector<uint8_t>& input)
{
  std::vector<uint8_t> out(input.size() * 4 + 1024);
  for (;;) {
    std::size_t in_pos = 0;
    std::size_t out_pos = 0;
    uint64_t memlimit = UINT64_MAX;
    lzma_ret rc = lzma_stream_buffer_decode(&memlimit, 0, nullptr, input.data(),
                                            &in_pos, input.size(), out.data(),
                                            &out_pos, out.size());
    if (rc == LZMA_OK) {
      out.resize(out_pos);
      return out;
    }
    if (rc == LZMA_BUF_ERROR) {  // вихідний буфер замалий, збільшуємо і повторюємо
      out.resize(out.size() * 2);
      continue;
    }
    throw std::runtime_error("lzma_stream_buffer_decode failed");
  }
}
```

### Потокове стиснення

Для даних, які не варто тримати у пам'яті цілком, керуй кодувальником
`lzma_stream` у циклі по частинах (та сама форма працює і для розпакування через
`lzma_stream_decoder()`):

```cpp
#include <lzma.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

std::vector<uint8_t> xz_compress_stream(const std::vector<uint8_t>& input,
                                        uint32_t preset = LZMA_PRESET_DEFAULT)
{
  lzma_stream strm = LZMA_STREAM_INIT;
  if (lzma_easy_encoder(&strm, preset, LZMA_CHECK_CRC64) != LZMA_OK) {
    throw std::runtime_error("lzma_easy_encoder failed");
  }

  strm.next_in = input.data();  // next_in має тип const uint8_t*, приведення не треба
  strm.avail_in = input.size();

  std::vector<uint8_t> out;
  uint8_t buf[BUFSIZ];
  lzma_ret rc = LZMA_OK;
  do {
    strm.next_out = buf;
    strm.avail_out = sizeof(buf);
    rc = lzma_code(&strm, LZMA_FINISH);
    out.insert(out.end(), buf, buf + (sizeof(buf) - strm.avail_out));
  } while (rc == LZMA_OK);
  lzma_end(&strm);

  if (rc != LZMA_STREAM_END) {
    throw std::runtime_error("lzma_code failed");
  }
  return out;
}
```

**`.xz` проти застарілого `.lzma`.** Сніпети вище створюють сучасний контейнер
`.xz` (рекомендований). Для застарілого формату `.lzma` (лише LZMA1) використовуй
`lzma_alone_encoder()` / `lzma_alone_decoder()` із `lzma_options_lzma`, заповненою
через `lzma_lzma_preset()`. Формат `.xz` додає перевірки цілісності й підтримку
кількох фільтрів, тож для нових даних варто надавати перевагу саме йому.
