## Вмикання інтеграції HarfBuzz

Для того щоб увімкнути бібліотеку формування тексту [HarfBuzz](https://harfbuzz.github.io/) (перетворення тексту Unicode на розташовані гліфи шрифту: кернінг, лігатури, письмо справа наліво та складні писемності) для проекту, використовуючи встановлену версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_HARFBUZZ`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_HARFBUZZ=ON
```

Дивись модуль `cmake/enablers/fonts/template-project-harfbuzz-enabler.cmake` щодо цілі (`harfbuzz::harfbuzz` як для системної версії, так і для побудови через FetchContent), яку слід прилінкувати до твоїх цільових об'єктів.

Версія, що завантажується, визначається CMake змінною `TEMPLATE_APP_HARFBUZZ_GIT_TAG` (типово `14.4.0`). Основною системою побудови HarfBuzz є Meson, тож її CMake побудова, яку підтримує спільнота, виводить про це попередження під час конфігурації FetchContent. Модуль створює для завантаженої цілі `harfbuzz` псевдонім `harfbuzz::harfbuzz` (ім'я системної версії) та позначає її як `SYSTEM`, щоб уберегти її заголовки від попереджень проекту.

HarfBuzz формує текст власною реалізацією OpenType і не потребує для цього FreeType. Проте побудова через FetchContent додає зв'язку з FreeType `<hb-ft.h>`, коли `ENABLE_FREETYPE` також будує FreeType.

### Формування потрібного тексту (приклади для копіювання)

Після `ENABLE_HARFBUZZ=ON` та прилінкування цілі HarfBuzz (наприклад `target_link_libraries(${PROJECT_BINARY_NAME} harfbuzz::harfbuzz)`) підключи `<hb.h>` і скопіюй будь-який зі сніпетів нижче.

Формування тексту UTF-8 в індекси гліфів та їхні позиції - літери `ffi`, наприклад, виходять одним гліфом-лігатурою:

```cpp
#include <hb.h>

#include <cstdio>

void harfbuzz_shape(const char *fontPath, const char *utf8Text)
{
  // Blob утримує байти файлу шрифту, face - це один шрифт із них, а font - це
  // face певного розміру (типово одна одиниця на одиницю дизайну шрифту).
  hb_blob_t *blob = hb_blob_create_from_file(fontPath);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);

  // Буфер приймає текст і віддає розташовані гліфи.
  hb_buffer_t *buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, utf8Text, -1, 0, -1);

  // Визнач писемність, мову та напрям за самим текстом або задай їх через
  // hb_buffer_set_script(), _set_language() та _set_direction().
  hb_buffer_guess_segment_properties(buffer);

  hb_shape(font, buffer, nullptr, 0);

  unsigned int count = 0;
  const hb_glyph_info_t *infos = hb_buffer_get_glyph_infos(buffer, &count);
  const hb_glyph_position_t *positions =
      hb_buffer_get_glyph_positions(buffer, &count);

  for (unsigned int i = 0; i < count; ++i) {
    // Після формування поле codepoint містить індекс гліфа, а поле cluster -
    // зсув у байтах тексту, з якого походить гліф.
    std::printf("glyph %u (cluster %u): advance %d, offset %d,%d\n",
                infos[i].codepoint, infos[i].cluster, positions[i].x_advance,
                positions[i].x_offset, positions[i].y_offset);
  }

  hb_buffer_destroy(buffer);
  hb_font_destroy(font);
  hb_face_destroy(face);
  hb_blob_destroy(blob);
}
```

### Малювання сформованого тексту за допомогою FreeType

HarfBuzz розташовує гліфи, а FreeType їх відмальовує, тож разом (`ENABLE_FREETYPE=ON` поряд з `ENABLE_HARFBUZZ=ON`, обидві цілі прилінковано) вони правильно розміщують растри гліфів будь-якої писемності:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H
#include <hb.h>

#include <cstdio>

// Розміщує растри гліфів FreeType уздовж рядка, сформованого HarfBuzz. Face та
// font походять з одного файлу шрифтів з однаковим розміром, наприклад
// FT_Set_Pixel_Sizes(face, 0, 48) поряд із hb_font_set_scale(font, 48 * 64,
// 48 * 64), тож HarfBuzz розташовує гліфи в одиницях 1/64 пікселя, якими
// користуються метрики FreeType.
void harfbuzz_freetype_line(FT_Face face, hb_font_t *font, const char *utf8Text)
{
  hb_buffer_t *buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, utf8Text, -1, 0, -1);
  hb_buffer_guess_segment_properties(buffer);
  hb_shape(font, buffer, nullptr, 0);

  unsigned int count = 0;
  const hb_glyph_info_t *infos = hb_buffer_get_glyph_infos(buffer, &count);
  const hb_glyph_position_t *positions =
      hb_buffer_get_glyph_positions(buffer, &count);

  hb_position_t penX = 0;
  hb_position_t penY = 0;

  for (unsigned int i = 0; i < count; ++i) {
    // Індекс гліфа йде до FreeType як є, тож лігатури та контекстні форми,
    // які обрав HarfBuzz, відмальовуються також.
    if (FT_Load_Glyph(face, infos[i].codepoint, FT_LOAD_RENDER) == 0) {
      const FT_GlyphSlot glyph = face->glyph;

      // Верхній лівий кут растра відносно початку рядка на базовій лінії, з
      // віссю y, спрямованою вниз, як у просторі екрана.
      const int left =
          ((penX + positions[i].x_offset) >> 6) + glyph->bitmap_left;
      const int top = -((penY + positions[i].y_offset) >> 6) - glyph->bitmap_top;

      std::printf("glyph %u: %ux%u bitmap at %d,%d\n", infos[i].codepoint,
                  glyph->bitmap.width, glyph->bitmap.rows, left, top);
    }

    penX += positions[i].x_advance;
    penY += positions[i].y_advance;
  }

  hb_buffer_destroy(buffer);
}
```

HarfBuzz, побудована з підтримкою FreeType (як у пакетах дистрибутивів), також створює такий font просто з `FT_Face` із заданим розміром функцією `hb_ft_font_create_referenced()` з `<hb-ft.h>`.

### Формування тексту кожного типу шрифтів (приклади для копіювання)

HarfBuzz сама читає шрифти TrueType та OpenType (`.ttf`, `.otf`) разом з їхніми колекціями (`.ttc`, `.otc`), варіаціями та кольоровими таблицями і формує ними текст тим самим кодом - додаються лише індекс face колекції та дизайн варіативного шрифту:

```cpp
#include <hb.h>

// Відкриває face з заданим індексом із файлу шрифтів - колекція (.ttc, .otc)
// містить hb_face_count(blob) з них, інші файли - один - із заданим
// налаштуванням варіативного шрифту, наприклад "wght=700" для жирного (або nullptr).
hb_font_t *harfbuzz_open_font(const char *fontPath, unsigned int faceIndex,
                              const char *variation)
{
  hb_blob_t *blob = hb_blob_create_from_file(fontPath);
  hb_face_t *face = hb_face_create(blob, faceIndex);
  hb_font_t *font = hb_font_create(face);

  hb_variation_t setting;
  if (variation != nullptr && hb_variation_from_string(variation, -1, &setting)) {
    hb_font_set_variations(font, &setting, 1);
  }

  // Font утримує свій face, а face - свій blob.
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return font;
}
```

Кольорові шрифти (емодзі) формують текст, як і будь-які інші, а їхня технологія визначає спосіб відмальовування їхніх гліфів:

```cpp
#include <hb-ot.h>
#include <hb.h>

// Називає кольорову технологію face, яка визначає, як відмальовуються його
// гліфи: FreeType змішує шари COLR v0 та завантажує растри CBDT/sbix з
// FT_LOAD_COLOR, тоді як малюнки COLR v1 та SVG гліфи потребують бібліотеки
// векторної графіки. Саме формування тексту для них усіх однакове.
const char *harfbuzz_color_type(hb_face_t *face)
{
  if (hb_ot_color_has_paint(face)) {
    return "COLR v1";
  }

  if (hb_ot_color_has_layers(face)) {
    return "COLR v0";
  }

  if (hb_ot_color_has_png(face)) {
    return "CBDT/sbix bitmaps";
  }

  return hb_ot_color_has_svg(face) ? "SVG" : "no color";
}
```

Інші типи, які відкриває FreeType - вебшрифти `.woff` та `.woff2`, шрифти Type 1 та растрові - потрапляють до HarfBuzz через свій `FT_Face`: формуй текст шрифтом, який створює з нього `hb_ft_font_create_referenced()` з `<hb-ft.h>` (HarfBuzz, побудована з FreeType, дивись вище). Вебшрифти формують текст повністю, тоді як шрифти Type 1 та растрові не мають таблиць розкладки OpenType, тож їхній текст отримує просте відображення символів у гліфи разом з кернінгом, який читає FreeType (наприклад, з файлу `.afm`, приєднаного до шрифту Type 1, дивись [розділ FreeType](/doc/sections/uk_UA/5-project-build/fonts/5-41-enabling-the-freetype-library.md)).
