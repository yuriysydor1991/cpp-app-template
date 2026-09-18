## Enabling the HarfBuzz library

In order to enable the [HarfBuzz](https://harfbuzz.github.io/) text shaping library (a Unicode text turned into the positioned glyphs of a font: the kerning, the ligatures, the right-to-left and the complex scripts) for the project by using the installed system one or by fetching it through the available connection set an `ON` value to the `ENABLE_HARFBUZZ` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_HARFBUZZ=ON
```

See the `cmake/enablers/fonts/template-project-harfbuzz-enabler.cmake` module for the target (`harfbuzz::harfbuzz` for both a system install and the FetchContent build) to link to your targets of interest.

The fetched revision is driven by the `TEMPLATE_APP_HARFBUZZ_GIT_TAG` CMake variable (`14.4.0` by default). Meson is the main HarfBuzz build system, so its community maintained CMake build prints a warning about it while the FetchContent build configures. The enabler aliases the fetched `harfbuzz` target as `harfbuzz::harfbuzz` (the name of a system install) and marks it `SYSTEM` to keep the project warnings off its headers.

HarfBuzz shapes the text with its own OpenType implementation and needs no FreeType for that. The FetchContent build still compiles the `<hb-ft.h>` FreeType glue in when `ENABLE_FREETYPE` builds FreeType as well.

### Shaping the text of interest (copy-paste examples)

After `ENABLE_HARFBUZZ=ON` and linking the HarfBuzz target (e.g. `target_link_libraries(${PROJECT_BINARY_NAME} harfbuzz::harfbuzz)`), include `<hb.h>` and copy-paste any of the snippets below.

Shaping a UTF-8 text into the glyph indices and their positions - the `ffi` letters come out as a single ligature glyph, for example:

```cpp
#include <hb.h>

#include <cstdio>

void harfbuzz_shape(const char *fontPath, const char *utf8Text)
{
  // A blob holds the font file bytes, a face is one font out of them and a
  // font is the face at a size (by default one unit per the font design unit).
  hb_blob_t *blob = hb_blob_create_from_file(fontPath);
  hb_face_t *face = hb_face_create(blob, 0);
  hb_font_t *font = hb_font_create(face);

  // The buffer takes the text in and gives the positioned glyphs out.
  hb_buffer_t *buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, utf8Text, -1, 0, -1);

  // Guess the script, the language and the direction from the text itself, or
  // set them with hb_buffer_set_script(), _set_language() and _set_direction().
  hb_buffer_guess_segment_properties(buffer);

  hb_shape(font, buffer, nullptr, 0);

  unsigned int count = 0;
  const hb_glyph_info_t *infos = hb_buffer_get_glyph_infos(buffer, &count);
  const hb_glyph_position_t *positions =
      hb_buffer_get_glyph_positions(buffer, &count);

  for (unsigned int i = 0; i < count; ++i) {
    // After the shaping the codepoint field holds the glyph index and the
    // cluster one the byte offset of the text the glyph comes from.
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

### Drawing the shaped text with FreeType

HarfBuzz positions the glyphs and FreeType renders them, so the two together (`ENABLE_FREETYPE=ON` next to the `ENABLE_HARFBUZZ=ON`, both targets linked) place the glyph bitmaps of any script right:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H
#include <hb.h>

#include <cstdio>

// Places the FreeType glyph bitmaps along a line shaped by HarfBuzz. The face
// and the font come out of the same font file at the same size, e.g.
// FT_Set_Pixel_Sizes(face, 0, 48) next to hb_font_set_scale(font, 48 * 64,
// 48 * 64), so that HarfBuzz positions the glyphs in the 1/64 pixel units the
// FreeType metrics use.
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
    // The glyph index goes to FreeType as it is, so the ligatures and the
    // contextual forms HarfBuzz has picked get rendered as well.
    if (FT_Load_Glyph(face, infos[i].codepoint, FT_LOAD_RENDER) == 0) {
      const FT_GlyphSlot glyph = face->glyph;

      // The top left bitmap corner against the line origin on the baseline,
      // with the y axis going down as the screen space does.
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

A HarfBuzz built with the FreeType support (the distribution packages are) also creates such a font straight out of the sized `FT_Face` with the `hb_ft_font_create_referenced()` of `<hb-ft.h>`.

### Shaping each font type (copy-paste examples)

HarfBuzz reads the TrueType and the OpenType fonts (`.ttf`, `.otf`) together with their collections (`.ttc`, `.otc`), variations and color tables on its own and shapes them all with the same code - only the face index of a collection and the design of a variable font come on top:

```cpp
#include <hb.h>

// Opens the face of the given index out of a font file - a collection (.ttc,
// .otc) holds hb_face_count(blob) of them, the other files one - at the given
// setting of a variable font, e.g. "wght=700" for the bold (or nullptr).
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

  // The font keeps its face alive and the face its blob.
  hb_face_destroy(face);
  hb_blob_destroy(blob);

  return font;
}
```

The color fonts (emoji) shape like any other font, while their technology picks the way their glyphs render:

```cpp
#include <hb-ot.h>
#include <hb.h>

// Names the color technology of a face, which decides how its glyphs render:
// FreeType blends the COLR v0 layers and loads the CBDT/sbix bitmaps with
// FT_LOAD_COLOR, while the COLR v1 paints and the SVG glyphs need a vector
// graphics library. The shaping itself stays the same for all of them.
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

The other types FreeType opens - the `.woff` and `.woff2` web fonts, the Type 1 and the bitmap fonts - reach HarfBuzz through their `FT_Face`: shape them with the font the `hb_ft_font_create_referenced()` of `<hb-ft.h>` makes out of it (a HarfBuzz built with FreeType, see above). The web fonts shape in full, while the Type 1 and the bitmap fonts carry no OpenType layout tables, so their text gets the plain character to glyph mapping together with the kerning FreeType reads (e.g. out of the `.afm` file attached to a Type 1 font, see the [FreeType section](/doc/sections/en_US/5-project-build/fonts/5-41-enabling-the-freetype-library.md)).
