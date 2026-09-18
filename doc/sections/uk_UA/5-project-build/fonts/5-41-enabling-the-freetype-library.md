## Вмикання інтеграції FreeType

Для того щоб увімкнути бібліотеку растеризації шрифтів [FreeType](https://freetype.org/) (перетворення шрифтів TrueType, OpenType, WOFF та інших форматів на растри гліфів) для проекту, використовуючи встановлену версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_FREETYPE`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_FREETYPE=ON
```

Дивись модуль `cmake/enablers/fonts/template-project-freetype-enabler.cmake` щодо цілі (`Freetype::Freetype` як для системної версії, так і для побудови через FetchContent), яку слід прилінкувати до твоїх цільових об'єктів.

Версія, що завантажується, визначається CMake змінною `TEMPLATE_APP_FREETYPE_GIT_TAG` (типово `VER-2-14-3`). Побудова через FetchContent називає свою ціль бібліотеки `freetype`, тож модуль створює для неї псевдонім `Freetype::Freetype` - ім'я, яке CMake модуль `FindFreetype` дає системній версії - та позначає її як `SYSTEM`, що вберігає заголовки FreeType від попереджень проекту так само, як і заголовки системної версії. Модуль msdfgen знаходить свою залежність FreeType через ту ж ціль, а побудова HarfBuzz через FetchContent сама прилінковує завантажену FreeType.

### Відмальовування потрібних гліфів (приклади для копіювання)

Після `ENABLE_FREETYPE=ON` та прилінкування цілі FreeType (наприклад `target_link_libraries(${PROJECT_BINARY_NAME} Freetype::Freetype)`) підключи `<ft2build.h>`, а за ним `FT_FREETYPE_H`, і скопіюй будь-який зі сніпетів нижче.

Увесь життєвий цикл FreeType в одній функції - бібліотека, face з файлу шрифтів, його розмір та гліф, відмальований у растр:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdio>

void freetype_render_glyph(const char *fontPath)
{
  // Бібліотека утримує модулі FreeType, а face - це один шрифт файлу шрифтів.
  FT_Library library{nullptr};
  if (FT_Init_FreeType(&library) != 0) {
    return;
  }

  FT_Face face{nullptr};
  if (FT_New_Face(library, fontPath, 0, &face) == 0) {
    // 48 пікселів на EM; нульова ширина означає "така ж, як висота".
    FT_Set_Pixel_Sizes(face, 0, 48);

    // FT_LOAD_RENDER перетворює контур гліфа на 8 бітний растр покриття.
    if (FT_Load_Char(face, 'A', FT_LOAD_RENDER) == 0) {
      const FT_GlyphSlot glyph = face->glyph;

      // bitmap_left / bitmap_top розміщують растр відносно пера на базовій
      // лінії, а крок (advance, в 1/64 пікселя) пересуває перо далі.
      std::printf("%ux%u bitmap, bearing %d,%d, advance %ld px\n",
                  glyph->bitmap.width, glyph->bitmap.rows, glyph->bitmap_left,
                  glyph->bitmap_top, glyph->advance.x >> 6);
    }

    FT_Done_Face(face);
  }

  FT_Done_FreeType(library);
}
```

### Відмальовування рядка тексту в текстуру

OpenGL та Vulkan малюють текст з текстур, тож простий початок - це увесь рядок, відмальований в один растр і показаний одним текстурованим чотирикутником:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

// Ширина, висота та 8 бітні пікселі покриття, починаючи з верхнього рядка.
using TextBitmap = std::tuple<unsigned, unsigned, std::vector<unsigned char>>;

// Відмальовує рядок тексту шрифтом із розміром, заданим FT_Set_Pixel_Sizes(),
// в один растр, готовий для текстури GL_R8 чи зображення VK_FORMAT_R8_UNORM.
TextBitmap freetype_render_line(FT_Face face, const char *text)
{
  // Рамка рядка: завширшки із суму кроків гліфів, заввишки від верхнього
  // виносного елемента (ascender) до нижнього (descender), з базовою лінією
  // на рівні ascender.
  const FT_Pos ascender = face->size->metrics.ascender >> 6;
  const FT_Pos height = ascender - (face->size->metrics.descender >> 6);
  FT_Pos width = 0;

  for (const char *c = text; *c != '\0'; ++c) {
    if (FT_Load_Char(face, static_cast<unsigned char>(*c), FT_LOAD_DEFAULT) == 0) {
      width += face->glyph->advance.x >> 6;
    }
  }

  std::vector<unsigned char> pixels(static_cast<size_t>(width * height), 0);
  FT_Pos pen = 0;

  for (const char *c = text; *c != '\0'; ++c) {
    if (FT_Load_Char(face, static_cast<unsigned char>(*c), FT_LOAD_RENDER) != 0) {
      continue;
    }

    const FT_GlyphSlot glyph = face->glyph;
    const FT_Bitmap &bitmap = glyph->bitmap;

    for (unsigned row = 0; row < bitmap.rows; ++row) {
      const FT_Pos y = ascender - glyph->bitmap_top + static_cast<FT_Pos>(row);
      const unsigned char *src = bitmap.buffer + static_cast<FT_Pos>(row) * bitmap.pitch;

      for (unsigned col = 0; col < bitmap.width; ++col) {
        const FT_Pos x = pen + glyph->bitmap_left + static_cast<FT_Pos>(col);

        // Гліф може виступати за рамку рядка: діакритичний знак, нахил курсиву.
        if (x >= 0 && x < width && y >= 0 && y < height) {
          unsigned char &dst = pixels[static_cast<size_t>(y * width + x)];
          dst = std::max(dst, src[col]);
        }
      }
    }

    pen += glyph->advance.x >> 6;
  }

  return {static_cast<unsigned>(width), static_cast<unsigned>(height),
          std::move(pixels)};
}
```

Рядки пікселів щільно запаковані, тож завантажуй їх після `glPixelStorei(GL_UNPACK_ALIGNMENT, 1)` викликом `glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, pixels.data())` або копіюй їх через проміжний (staging) буфер у зображення `VK_FORMAT_R8_UNORM` з Vulkan, а у фрагментному шейдері бери червоний канал як альфу кольору тексту. Рядки йдуть згори донизу - у порядку зображень Vulkan - тож в OpenGL признач верхньому краю чотирикутника координату текстури `t = 0`.

Сама FreeType перетворює кожен символ на один гліф: дивись [розділ HarfBuzz](/doc/sections/uk_UA/5-project-build/fonts/5-42-enabling-the-harfbuzz-library.md) щодо кернінгу, лігатур та складних писемностей.
