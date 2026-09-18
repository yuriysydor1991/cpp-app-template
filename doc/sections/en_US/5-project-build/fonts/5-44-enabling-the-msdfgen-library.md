## Enabling the msdfgen library

In order to enable the [msdfgen](https://github.com/Chlumsky/msdfgen) library (the multi-channel signed distance fields of the glyphs, which the GPU scales and rotates with their corners kept sharp) for the project by using the installed system one or by fetching it through the available connection set an `ON` value to the `ENABLE_MSDFGEN` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_MSDFGEN=ON -DENABLE_FREETYPE=ON
```

msdfgen loads the fonts through FreeType, so keep `ENABLE_FREETYPE=ON` (or a system FreeType available) so the dependency resolves. See the `cmake/enablers/fonts/template-project-msdfgen-enabler.cmake` module for the target (`msdfgen::msdfgen` for both a system install and the FetchContent build) to link to your targets of interest.

The fetched revision is driven by the `TEMPLATE_APP_MSDFGEN_GIT_TAG` CMake variable (`v1.13` by default). The enabler also sets five msdfgen options against the upstream defaults, which break a plain consumer build or build more than it needs:

- `MSDFGEN_USE_VCPKG` is switched `OFF`, since it demands the vcpkg toolchain;
- `MSDFGEN_USE_SKIA` is switched `OFF`, since it demands the Skia library;
- `MSDFGEN_DISABLE_SVG` is switched `ON`, since the SVG shape input demands the tinyxml2 library;
- `MSDFGEN_DISABLE_PNG` is switched `ON`, since the PNG file output demands the libpng library;
- `MSDFGEN_BUILD_STANDALONE` is switched `OFF`, since the glyphs generated at the run time need no command line generator.

All five stay ordinary cache variables, so pass e.g. `-DMSDFGEN_DISABLE_PNG=OFF` on a host with the libpng installed to get the `msdfgen::savePng()` back. The FetchContent build targets are marked `SYSTEM` to keep the project warnings off their headers.

### Generating the glyph distance fields (copy-paste example)

After `ENABLE_MSDFGEN=ON` and linking the msdfgen target (e.g. `target_link_libraries(${PROJECT_BINARY_NAME} msdfgen::msdfgen)`), include `<msdfgen.h>` with `<msdfgen-ext.h>` and copy-paste the snippet below:

```cpp
#include <msdfgen-ext.h>
#include <msdfgen.h>

#include <vector>

// Generates the 32x32 multi-channel signed distance field of one character
// and converts it into the RGB8 texels of a texture to sample with the linear
// filtering, the bottom row first as the OpenGL textures expect.
std::vector<unsigned char> msdfgen_glyph(const char *fontPath,
                                         msdfgen::unicode_t character)
{
  std::vector<unsigned char> texels;

  if (msdfgen::FreetypeHandle *ft = msdfgen::initializeFreetype()) {
    if (msdfgen::FontHandle *font = msdfgen::loadFont(ft, fontPath)) {
      msdfgen::Shape shape;

      // The EM normalized scaling gives the glyph outline in the EM units,
      // 1.0 being the whole font size.
      if (msdfgen::loadGlyph(shape, font, character,
                             msdfgen::FONT_SCALING_EM_NORMALIZED)) {
        shape.normalize();

        // Spread the edges over the three channels, keeping the edge joints of
        // up to 3 radians (about 172 degrees) as the sharp corners.
        msdfgen::edgeColoringSimple(shape, 3.0);

        // 32 pixels per EM, the glyph moved by 0.125 EM off the bitmap corner
        // and the distances encoded in a range 0.125 EM (4 pixels) wide across
        // its edges. Pass msdfgen::Y_DOWNWARD as the third argument for the top
        // row first order of the Vulkan images.
        msdfgen::Bitmap<float, 3> msdf(32, 32);
        const msdfgen::SDFTransformation transformation(
            msdfgen::Projection(32.0, msdfgen::Vector2(0.125, 0.125)),
            msdfgen::Range(0.125));

        msdfgen::generateMSDF(msdf, shape, transformation);

        for (int y = 0; y < msdf.height(); ++y) {
          for (int x = 0; x < msdf.width(); ++x) {
            for (int channel = 0; channel < 3; ++channel) {
              texels.push_back(msdfgen::pixelFloatToByte(msdf(x, y)[channel]));
            }
          }
        }
      }

      msdfgen::destroyFont(font);
    }

    msdfgen::deinitializeFreetype(ft);
  }

  return texels;
}
```

Upload the texels into a `GL_RGB8` texture after a `glPixelStorei(GL_UNPACK_ALIGNMENT, 1)` (the 3 byte texels break the default 4 byte row alignment), or add the alpha channel for a `VK_FORMAT_R8G8B8A8_UNORM` image with Vulkan. Keep the format linear either way, since an sRGB one would distort the stored distances.

### Drawing the distance field

The fragment shader takes the median of the three channels as the distance to the glyph edge and turns it into the coverage with an anti-aliased edge at whatever size the quad is drawn:

```glsl
#version 330 core

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D msdf;
uniform vec4 textColor;
uniform float screenPxRange;

float median(float r, float g, float b)
{
  return max(min(r, g), min(max(r, g), b));
}

void main()
{
  vec3 channels = texture(msdf, texCoord).rgb;
  float distance = screenPxRange * (median(channels.r, channels.g, channels.b) - 0.5);

  fragColor = vec4(textColor.rgb, textColor.a * clamp(distance + 0.5, 0.0, 1.0));
}
```

The `screenPxRange` uniform holds the distance range in the screen pixels: the 4 pixels wide range of the 32x32 field above drawn on a 64x64 pixels quad gives `4 * 64 / 32 = 8`.

For Vulkan compile the same shader into SPIR-V with the `layout(location = ...)` qualifiers on its input and output, the `layout(binding = ...)` one on the sampler and the two plain uniforms moved into a uniform or push constant block.

### Using each font type (copy-paste examples)

msdfgen loads every outline font FreeType opens - the TrueType, the OpenType (CFF), the `.woff` / `.woff2` and the Type 1 ones - with the same `msdfgen::loadFont()` and `msdfgen::loadGlyph()` of the snippet above. The variable fonts and the collections need one more step:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H
// FreeType goes first, since it enables the msdfgen::adoptFreetypeFont()
#include <msdfgen-ext.h>
#include <msdfgen.h>

// Opens a variable font at the given weight, e.g. 700 for the bold. msdfgen
// takes the axes by the names the font gives them ("Weight" here), which the
// msdfgen::listFontVariationAxes() lists together with their ranges.
msdfgen::FontHandle *msdfgen_load_weight(msdfgen::FreetypeHandle *ft,
                                         const char *fontPath, double weight)
{
  msdfgen::FontHandle *font = msdfgen::loadFont(ft, fontPath);

  if (font != nullptr) {
    // false for the fonts with no such axis, which then stay as they are
    msdfgen::setFontVariationAxis(ft, font, "Weight", weight);
  }

  return font;
}

// Opens the face of the given index out of a font collection (.ttc, .otc),
// since the msdfgen::loadFont() takes the first face only. The
// msdfgen::destroyFont() leaves the face itself to the FT_Done_Face().
msdfgen::FontHandle *msdfgen_collection_face(FT_Library library,
                                             const char *fontPath,
                                             FT_Long faceIndex, FT_Face &face)
{
  if (FT_New_Face(library, fontPath, faceIndex, &face) != 0) {
    return nullptr;
  }

  return msdfgen::adoptFreetypeFont(face);
}
```

Link the `Freetype::Freetype` target as well for the `FT_New_Face()` of the collection snippet. The bitmap fonts (`.pcf`, `.bdf`, `.fon`) and the bitmap color emoji (CBDT, sbix) have no outlines to measure the distances from - the `msdfgen::loadGlyph()` gives an empty shape for them - so draw those with the glyph pixels of the [FreeType section](/doc/sections/en_US/5-project-build/fonts/5-41-enabling-the-freetype-library.md).
