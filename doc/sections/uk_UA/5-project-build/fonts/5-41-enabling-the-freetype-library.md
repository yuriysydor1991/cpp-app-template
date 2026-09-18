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

### Використання кожного типу шрифтів (приклади для копіювання)

FreeType відкриває шрифти кожного типу тією ж `FT_New_Face()`, що й у прикладах вище, і лише кілька типів потребують власного коду:

| Тип шрифту | Файли | Що відрізняється |
| --- | --- | --- |
| TrueType, OpenType (CFF) | `.ttf`, `.otf` | нічого |
| Вебшрифти | `.woff`, `.woff2` | нічого, проте WOFF2 потребує FreeType, побудованої з бібліотекою Brotli |
| PostScript Type 1 | `.pfb`, `.pfa`, `.t1` | `FT_Attach_File(face, "font.afm")` додає кернінг з окремого файлу метрик `.afm` (або `.pfm`) |
| Колекції | `.ttc`, `.otc` | декілька face в одному файлі, які обираються за їхнім індексом |
| Варіативні шрифти | `.ttf`, `.otf` з осями варіацій | дизайн, обраний уздовж осей (товщини, ширини, ...) |
| Растрові шрифти | `.pcf`, `.bdf`, `.fon` | кілька фіксованих розмірів (strikes) та 1 біт на піксель |
| Кольорові шрифти (емодзі) | растри CBDT та sbix, шари COLR | прапорець `FT_LOAD_COLOR` та BGRA пікселі, фіксовані розміри для растрових |

Пакети FreeType у дистрибутивах постачаються з підтримкою Brotli (для WOFF2) та libpng (для PNG зображень емодзі CBDT та sbix), як і побудова через FetchContent, коли вона знаходить ці бібліотеки.

Визначення типу файлу шрифтів разом з кожним face колекції:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_FONT_FORMATS_H

#include <cstdio>

// Виводить тип кожного face файлу шрифтів: його формат ("TrueType" для
// файлів .ttf, .woff та .woff2, "CFF" для файлів .otf, "Type 1", "BDF", "PCF",
// "Windows FNT", ...) та ознаки, які визначають потрібний йому код.
void freetype_font_types(FT_Library library, const char *fontPath)
{
  // Від'ємний індекс не відкриває face, а натомість рахує face файлу:
  // колекція (.ttc, .otc) містить їх декілька, інші файли - один.
  FT_Face face{nullptr};
  if (FT_New_Face(library, fontPath, -1, &face) != 0) {
    return;
  }

  const FT_Long count = face->num_faces;
  FT_Done_Face(face);

  for (FT_Long index = 0; index < count; ++index) {
    if (FT_New_Face(library, fontPath, index, &face) != 0) {
      continue;
    }

    std::printf("face %ld: %s, %s%s%s%s%s\n", index,
                face->family_name != nullptr ? face->family_name : "?",
                FT_Get_Font_Format(face),
                FT_IS_SCALABLE(face) ? ", outlines" : "",
                FT_HAS_FIXED_SIZES(face) ? ", bitmap strikes" : "",
                FT_HAS_COLOR(face) ? ", color" : "",
                FT_HAS_MULTIPLE_MASTERS(face) ? ", variable" : "");

    FT_Done_Face(face);
  }
}
```

Задання розміру face будь-якого типу:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdlib>

// Задає розмір face шрифту будь-якого типу: контурні шрифти масштабуються до
// будь-якого розміру в пікселях, тоді як растрові шрифти (.pcf, .bdf, .fon) та
// растрові кольорові шрифти емодзі (CBDT, sbix) мають лише кілька фіксованих
// розмірів (strikes) - для них обирається найближчий, адже на них
// FT_Set_Pixel_Sizes() завершується помилкою.
bool freetype_set_size(FT_Face face, FT_UInt pixelHeight)
{
  if (FT_IS_SCALABLE(face)) {
    return FT_Set_Pixel_Sizes(face, 0, pixelHeight) == 0;
  }

  if (face->num_fixed_sizes <= 0) {
    return false;
  }

  // y_ppem містить розмір strike в 1/64 пікселя.
  const FT_Pos wanted = static_cast<FT_Pos>(pixelHeight) * 64;
  FT_Int nearest = 0;

  for (FT_Int i = 1; i < face->num_fixed_sizes; ++i) {
    if (std::labs(face->available_sizes[i].y_ppem - wanted) <
        std::labs(face->available_sizes[nearest].y_ppem - wanted)) {
      nearest = i;
    }
  }

  return FT_Select_Size(face, nearest) == 0;
}
```

Завантаження пікселів гліфа будь-якого типу - покриття контурних шрифтів, 1 бітних пікселів растрових шрифтів та кольорів емодзі:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H

#include <tuple>
#include <utility>
#include <vector>

// Ширина, висота, байти на піксель (1 для покриття, 4 для кольору) та щільно
// запаковані пікселі гліфа, починаючи з верхнього рядка.
using GlyphPixels = std::tuple<unsigned, unsigned, unsigned, std::vector<unsigned char>>;

// Завантажує символ face шрифту будь-якого типу з уже заданим розміром:
// контурні шрифти дають 8 бітне покриття, растрові - 1 біт на піксель (тут
// розгорнутий до 8 біт), а кольорові - BGRA пікселі з попередньо помноженою
// альфою, наприклад для зображення VK_FORMAT_B8G8R8A8_UNORM чи текстури
// GL_RGBA8, завантаженої як GL_BGRA.
GlyphPixels freetype_load_pixels(FT_Face face, FT_ULong character)
{
  // FT_LOAD_COLOR запитує кольорові гліфи, інші шрифти його ігнорують.
  if (FT_Load_Char(face, character, FT_LOAD_RENDER | FT_LOAD_COLOR) != 0) {
    return {};
  }

  const FT_Bitmap &bitmap = face->glyph->bitmap;
  const unsigned char mode = bitmap.pixel_mode;

  // 2 та 4 бітні пікселі деяких растрових шрифтів потребують FT_Bitmap_Convert().
  if (mode != FT_PIXEL_MODE_GRAY && mode != FT_PIXEL_MODE_MONO &&
      mode != FT_PIXEL_MODE_BGRA) {
    return {};
  }

  const unsigned depth = mode == FT_PIXEL_MODE_BGRA ? 4 : 1;
  std::vector<unsigned char> pixels;

  for (unsigned row = 0; row < bitmap.rows; ++row) {
    const unsigned char *src = bitmap.buffer + static_cast<FT_Pos>(row) * bitmap.pitch;

    for (unsigned col = 0; col < bitmap.width * depth; ++col) {
      // 1 бітні пікселі йдуть від старшого біта кожного байта.
      pixels.push_back(mode == FT_PIXEL_MODE_MONO
                           ? ((src[col / 8] >> (7 - col % 8)) & 1) * 255
                           : src[col]);
    }
  }

  return {bitmap.width, bitmap.rows, depth, std::move(pixels)};
}
```

Кольорові пікселі вже помножені на свою альфу, тож змішуй їх з коефіцієнтами `GL_ONE` та `GL_ONE_MINUS_SRC_ALPHA` (`VK_BLEND_FACTOR_ONE` та `VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA` у Vulkan). FreeType завантажує растри CBDT та sbix і змішує шари COLR v0, але не вміє відмальовувати гліфи COLR v1 та SVG - [розділ HarfBuzz](/doc/sections/uk_UA/5-project-build/fonts/5-42-enabling-the-harfbuzz-library.md) розрізняє кольорову технологію шрифту.

Пересування варіативного шрифту вздовж однієї з його осей, наприклад `freetype_set_axis(library, face, FT_MAKE_TAG('w', 'g', 'h', 't'), 700.0)` для жирного:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MULTIPLE_MASTERS_H

#include <vector>

// Пересуває варіативний шрифт уздовж однієї з його осей, наприклад осі
// товщини FT_MAKE_TAG('w', 'g', 'h', 't') до 700 для жирного, лишаючи інші осі
// типовими. Гліфи, завантажені після цього, походять з цього дизайну.
bool freetype_set_axis(FT_Library library, FT_Face face, FT_ULong tag, double value)
{
  FT_MM_Var *variations{nullptr};
  if (!FT_HAS_MULTIPLE_MASTERS(face) || FT_Get_MM_Var(face, &variations) != 0) {
    return false;
  }

  // Координати дизайну - це числа з фіксованою комою 16.16.
  std::vector<FT_Fixed> coordinates;
  bool found = false;

  for (FT_UInt i = 0; i < variations->num_axis; ++i) {
    const FT_Var_Axis &axis = variations->axis[i];
    found = found || axis.tag == tag;
    coordinates.push_back(axis.tag == tag ? static_cast<FT_Fixed>(value * 65536.0) : axis.def);
  }

  FT_Done_MM_Var(library, variations);

  return found && FT_Set_Var_Design_Coordinates(
                      face, static_cast<FT_UInt>(coordinates.size()),
                      coordinates.data()) == 0;
}
```

Іменовані екземпляри варіативного шрифту (його Bold, Light, Condensed тощо) натомість обираються через `FT_Set_Named_Instance(face, index)`, де індекс починається з 1.
