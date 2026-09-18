## Enabling the stb_truetype library

In order to enable the [stb_truetype](https://github.com/nothings/stb) single header font rasterization library (the TrueType fonts parsed and the glyphs packed into a texture atlas with no dependencies at all) for the project by fetching it through the available connection set an `ON` value to the `ENABLE_STB_TRUETYPE` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_STB_TRUETYPE=ON
```

The stb headers come with neither a build system nor a package to probe for, so the enabler always fetches them and exposes them through its own interface target. See the `cmake/enablers/fonts/template-project-stb-truetype-enabler.cmake` module for the target (`stb_truetype`) to link to your targets of interest.

The fetched revision is driven by the `TEMPLATE_APP_STB_GIT_TAG` CMake variable (the `master` branch by default). The target include directory is a `SYSTEM` one, since the library implementation gets compiled inside one of the project sources, which the project warnings would flood otherwise.

### Packing the glyphs into an atlas (copy-paste example)

After `ENABLE_STB_TRUETYPE=ON` and linking the stb_truetype target (e.g. `target_link_libraries(${PROJECT_BINARY_NAME} stb_truetype)`), define the `STB_TRUETYPE_IMPLEMENTATION` in exactly one source file before it includes `<stb_truetype.h>` (the other sources include the header alone) and copy-paste the snippet below:

```cpp
// in exactly one source file of the project
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#include <fstream>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

// The 8 bit coverage atlas pixels and the x, y, s, t vertices of the two
// triangles per character sampling it.
using TextMesh = std::tuple<std::vector<unsigned char>, std::vector<float>>;

// Packs the printable ASCII characters of a font into a 512x512 atlas and lays
// a line of text out of it, ready for a GL_R8 texture or a VK_FORMAT_R8_UNORM
// image and a vertex buffer.
TextMesh stb_truetype_line(const char *fontPath, const char *text)
{
  constexpr int atlasSize = 512;
  constexpr int firstChar = ' ';
  constexpr int charCount = '~' - ' ' + 1;

  // stb_truetype reads the font straight out of the file bytes in memory.
  std::ifstream file(fontPath, std::ios::binary);
  const std::vector<unsigned char> font{std::istreambuf_iterator<char>(file),
                                        std::istreambuf_iterator<char>()};

  std::vector<unsigned char> atlas(atlasSize * atlasSize, 0);
  std::vector<float> vertices;
  stbtt_packedchar chars[charCount];
  stbtt_pack_context context;

  if (stbtt_PackBegin(&context, atlas.data(), atlasSize, atlasSize, 0, 1,
                      nullptr) == 0) {
    return {};
  }

  // The 2x2 oversampling keeps the small sizes sharp with the linear filtering.
  stbtt_PackSetOversampling(&context, 2, 2);
  const int packed = stbtt_PackFontRange(&context, font.data(), 0, 32.0f,
                                         firstChar, charCount, chars);
  stbtt_PackEnd(&context);

  if (packed == 0) {
    return {};
  }

  // x and y are the screen pixels (y grows down, the line baseline at 0), s
  // and t the atlas texture coordinates.
  float x = 0.0f;
  float y = 0.0f;

  for (const char *c = text; *c != '\0'; ++c) {
    if (*c < firstChar || *c >= firstChar + charCount) {
      continue;
    }

    stbtt_aligned_quad q;
    stbtt_GetPackedQuad(chars, atlasSize, atlasSize, *c - firstChar, &x, &y, &q, 0);

    vertices.insert(vertices.end(),
                    {q.x0, q.y0, q.s0, q.t0, q.x1, q.y0, q.s1, q.t0,
                     q.x1, q.y1, q.s1, q.t1, q.x0, q.y0, q.s0, q.t0,
                     q.x1, q.y1, q.s1, q.t1, q.x0, q.y1, q.s0, q.t1});
  }

  return {std::move(atlas), std::move(vertices)};
}
```

The atlas rows are tightly packed and go from the top down - upload them as described in the [FreeType section](/doc/sections/en_US/5-project-build/fonts/5-41-enabling-the-freetype-library.md). The `s` and `t` coordinates already point the top of every quad at the top of its glyph, so the vertices draw right as they are in both OpenGL and Vulkan, given a projection with the y axis going down the screen.

stb_truetype does no range checking of the offsets it reads out of a font file, so load the trusted fonts only with it (e.g. the ones shipped together with the application) and FreeType for the rest.

### Using each font type (copy-paste example)

stb_truetype reads the TrueType (`.ttf`) and the OpenType CFF (`.otf`) fonts together with their collections (`.ttc`, `.otc`):

```cpp
#include <stb_truetype.h>

// Opens the font of the given index out of the bytes of a font file: a
// collection (.ttc, .otc) holds stbtt_GetNumberOfFonts(data) of them, the
// other files one at the index 0. The packing functions like the
// stbtt_PackFontRange() take the same index as their font_index argument.
bool stb_truetype_open(stbtt_fontinfo &info, const unsigned char *data, int index)
{
  const int offset = stbtt_GetFontOffsetForIndex(data, index);

  return offset >= 0 && stbtt_InitFont(&info, data, offset) != 0;
}
```

The web fonts (`.woff`, `.woff2`), the Type 1 and the bitmap fonts, as well as the bitmap only color emoji (CBDT, sbix), do not open with it at all. Out of a variable font it renders the default design only and out of a COLR color font the plain outlines only, without the color layers - use FreeType for all of those.
