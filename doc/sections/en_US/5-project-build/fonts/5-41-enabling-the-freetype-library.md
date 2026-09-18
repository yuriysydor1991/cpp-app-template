## Enabling the FreeType library

In order to enable the [FreeType](https://freetype.org/) font rasterization library (the TrueType, OpenType, WOFF and other font formats turned into the glyph bitmaps) for the project by using the installed system one or by fetching it through the available connection set an `ON` value to the `ENABLE_FREETYPE` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_FREETYPE=ON
```

See the `cmake/enablers/fonts/template-project-freetype-enabler.cmake` module for the target (`Freetype::Freetype` for both a system install and the FetchContent build) to link to your targets of interest.

The fetched revision is driven by the `TEMPLATE_APP_FREETYPE_GIT_TAG` CMake variable (`VER-2-14-3` by default). The FetchContent build names its library target `freetype`, so the enabler aliases it as `Freetype::Freetype` - the name the CMake `FindFreetype` module gives a system install - and marks it `SYSTEM`, which keeps the project warnings off the FreeType headers as off the system installed ones. The msdfgen enabler resolves its FreeType dependency through the same target, and the HarfBuzz FetchContent build links the fetched FreeType in by itself.

### Rendering the glyphs of interest (copy-paste examples)

After `ENABLE_FREETYPE=ON` and linking the FreeType target (e.g. `target_link_libraries(${PROJECT_BINARY_NAME} Freetype::Freetype)`), include `<ft2build.h>` followed by `FT_FREETYPE_H` and copy-paste any of the snippets below.

The whole FreeType lifecycle in one function - a library, a face out of a font file, its size and a glyph rendered into a bitmap:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdio>

void freetype_render_glyph(const char *fontPath)
{
  // The library holds the FreeType modules, a face is one font of a font file.
  FT_Library library{nullptr};
  if (FT_Init_FreeType(&library) != 0) {
    return;
  }

  FT_Face face{nullptr};
  if (FT_New_Face(library, fontPath, 0, &face) == 0) {
    // 48 pixels per EM; the zero width means "same as the height".
    FT_Set_Pixel_Sizes(face, 0, 48);

    // FT_LOAD_RENDER turns the glyph outline into an 8 bit coverage bitmap.
    if (FT_Load_Char(face, 'A', FT_LOAD_RENDER) == 0) {
      const FT_GlyphSlot glyph = face->glyph;

      // bitmap_left / bitmap_top place the bitmap against the pen on the
      // baseline, the advance (in 1/64 pixels) moves the pen further.
      std::printf("%ux%u bitmap, bearing %d,%d, advance %ld px\n",
                  glyph->bitmap.width, glyph->bitmap.rows, glyph->bitmap_left,
                  glyph->bitmap_top, glyph->advance.x >> 6);
    }

    FT_Done_Face(face);
  }

  FT_Done_FreeType(library);
}
```

### Rendering a line of text into a texture

OpenGL and Vulkan draw the text out of the textures, so a simple start is a whole line rendered into a single bitmap and shown by a single textured quad:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

// The width, the height and the 8 bit coverage pixels, the top row first.
using TextBitmap = std::tuple<unsigned, unsigned, std::vector<unsigned char>>;

// Renders a line of text with a face sized by FT_Set_Pixel_Sizes() into one
// bitmap, ready for a GL_R8 texture or a VK_FORMAT_R8_UNORM image.
TextBitmap freetype_render_line(FT_Face face, const char *text)
{
  // The line box: the sum of the advances wide, from the ascender down to
  // the descender high, with the baseline at the ascender.
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

        // A glyph may overhang the line box: an accent, an italic slant.
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

The rows are tightly packed, so upload them after a `glPixelStorei(GL_UNPACK_ALIGNMENT, 1)` with `glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, pixels.data())`, or copy them through a staging buffer into a `VK_FORMAT_R8_UNORM` image with Vulkan, and take the red channel as the alpha of the text color in the fragment shader. The rows go from the top down - the Vulkan image order - so in OpenGL give the top edge of the quad the `t = 0` texture coordinate.

FreeType on its own maps every character to a single glyph: see the [HarfBuzz section](/doc/sections/en_US/5-project-build/fonts/5-42-enabling-the-harfbuzz-library.md) for the kerning, the ligatures and the complex scripts.

### Using each font type (copy-paste examples)

FreeType opens every font type with the same `FT_New_Face()` of the examples above, and only a few types need code of their own:

| Font type | Files | What differs |
| --- | --- | --- |
| TrueType, OpenType (CFF) | `.ttf`, `.otf` | nothing |
| Web fonts | `.woff`, `.woff2` | nothing, but the WOFF2 needs a FreeType built with the Brotli library |
| PostScript Type 1 | `.pfb`, `.pfa`, `.t1` | `FT_Attach_File(face, "font.afm")` adds the kerning of the separate `.afm` (or `.pfm`) metrics file |
| Collections | `.ttc`, `.otc` | several faces in a single file, picked by their index |
| Variable fonts | `.ttf`, `.otf` with the variation axes | the design picked along the axes (the weight, the width, ...) |
| Bitmap fonts | `.pcf`, `.bdf`, `.fon` | a few fixed sizes (strikes) and 1 bit per pixel |
| Color fonts (emoji) | the CBDT and sbix bitmaps, the COLR layers | the `FT_LOAD_COLOR` flag and the BGRA pixels, the fixed sizes for the bitmap ones |

The distribution packages of FreeType come with the Brotli (for the WOFF2) and the libpng (for the PNG images of the CBDT and sbix emoji) support, and so does the FetchContent build when it finds those libraries.

Telling the type of a font file apart, together with every face of a collection:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_FONT_FORMATS_H

#include <cstdio>

// Prints the type of every face of a font file: its format ("TrueType" for
// the .ttf, .woff and .woff2 files, "CFF" for the .otf ones, "Type 1", "BDF",
// "PCF", "Windows FNT", ...) and the traits which pick the code it needs.
void freetype_font_types(FT_Library library, const char *fontPath)
{
  // A negative index opens no face, it counts the faces of the file instead:
  // a collection (.ttc, .otc) holds several of them, the other files one.
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

Sizing a face of any type:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdlib>

// Sizes a face of any font type: the outline fonts scale to any pixel size,
// while the bitmap fonts (.pcf, .bdf, .fon) and the bitmap color emoji ones
// (CBDT, sbix) come in a few fixed sizes (strikes) only - there the nearest
// strike gets selected, since FT_Set_Pixel_Sizes() fails on them.
bool freetype_set_size(FT_Face face, FT_UInt pixelHeight)
{
  if (FT_IS_SCALABLE(face)) {
    return FT_Set_Pixel_Sizes(face, 0, pixelHeight) == 0;
  }

  if (face->num_fixed_sizes <= 0) {
    return false;
  }

  // y_ppem holds the strike size in 1/64 pixels.
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

Loading the glyph pixels of any type - the coverage of the outline fonts, the 1 bit pixels of the bitmap fonts and the colors of the emoji:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H

#include <tuple>
#include <utility>
#include <vector>

// The width, the height, the bytes per pixel (1 for the coverage, 4 for the
// color) and the tightly packed pixels of a glyph, the top row first.
using GlyphPixels = std::tuple<unsigned, unsigned, unsigned, std::vector<unsigned char>>;

// Loads a character of a sized face of any font type: the outline fonts give
// the 8 bit coverage, the bitmap fonts 1 bit per pixel (expanded to 8 bits
// here) and the color fonts the premultiplied BGRA pixels, e.g. for a
// VK_FORMAT_B8G8R8A8_UNORM image or a GL_RGBA8 texture uploaded as GL_BGRA.
GlyphPixels freetype_load_pixels(FT_Face face, FT_ULong character)
{
  // FT_LOAD_COLOR asks for the color glyphs, the other fonts ignore it.
  if (FT_Load_Char(face, character, FT_LOAD_RENDER | FT_LOAD_COLOR) != 0) {
    return {};
  }

  const FT_Bitmap &bitmap = face->glyph->bitmap;
  const unsigned char mode = bitmap.pixel_mode;

  // The 2 and 4 bit pixels of a few bitmap fonts need FT_Bitmap_Convert().
  if (mode != FT_PIXEL_MODE_GRAY && mode != FT_PIXEL_MODE_MONO &&
      mode != FT_PIXEL_MODE_BGRA) {
    return {};
  }

  const unsigned depth = mode == FT_PIXEL_MODE_BGRA ? 4 : 1;
  std::vector<unsigned char> pixels;

  for (unsigned row = 0; row < bitmap.rows; ++row) {
    const unsigned char *src = bitmap.buffer + static_cast<FT_Pos>(row) * bitmap.pitch;

    for (unsigned col = 0; col < bitmap.width * depth; ++col) {
      // The 1 bit pixels go from the highest bit of every byte.
      pixels.push_back(mode == FT_PIXEL_MODE_MONO
                           ? ((src[col / 8] >> (7 - col % 8)) & 1) * 255
                           : src[col]);
    }
  }

  return {bitmap.width, bitmap.rows, depth, std::move(pixels)};
}
```

The color pixels come premultiplied by their alpha, so blend them with the `GL_ONE` and `GL_ONE_MINUS_SRC_ALPHA` factors (the `VK_BLEND_FACTOR_ONE` and `VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA` ones in Vulkan). FreeType loads the CBDT and sbix bitmaps and blends the COLR v0 layers, but it has no renderer for the COLR v1 and the SVG glyphs - the [HarfBuzz section](/doc/sections/en_US/5-project-build/fonts/5-42-enabling-the-harfbuzz-library.md) tells the color technology of a font apart.

Moving a variable font along one of its axes, e.g. `freetype_set_axis(library, face, FT_MAKE_TAG('w', 'g', 'h', 't'), 700.0)` for the bold:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MULTIPLE_MASTERS_H

#include <vector>

// Moves a variable font along one of its axes, e.g. the FT_MAKE_TAG('w', 'g',
// 'h', 't') weight one to 700 for the bold, keeping the other axes at their
// defaults. The glyphs loaded afterwards come out of that design.
bool freetype_set_axis(FT_Library library, FT_Face face, FT_ULong tag, double value)
{
  FT_MM_Var *variations{nullptr};
  if (!FT_HAS_MULTIPLE_MASTERS(face) || FT_Get_MM_Var(face, &variations) != 0) {
    return false;
  }

  // The design coordinates are 16.16 fixed point numbers.
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

The named instances of a variable font (its Bold, Light, Condensed and so on) are picked with the `FT_Set_Named_Instance(face, index)` instead, the index starting at 1.
