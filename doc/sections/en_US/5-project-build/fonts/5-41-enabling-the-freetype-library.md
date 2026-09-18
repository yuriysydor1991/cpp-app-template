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
