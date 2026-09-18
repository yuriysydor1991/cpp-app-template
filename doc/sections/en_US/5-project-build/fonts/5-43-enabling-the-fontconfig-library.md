## Enabling the Fontconfig library

In order to enable the [Fontconfig](https://www.freedesktop.org/wiki/Software/fontconfig/) library (the lookup of the installed fonts by their family, style and character coverage) for the project set an `ON` value to the `ENABLE_FONTCONFIG` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_FONTCONFIG=ON
```

Fontconfig ships the Meson and the autotools builds only, so it is probed from the system exclusively (install `libfontconfig-dev` on Debian/Ubuntu, `fontconfig-devel` on Fedora/openSUSE or `fontconfig` on Arch) - there is no FetchContent fallback. See the `cmake/enablers/fonts/template-project-fontconfig-enabler.cmake` module for the target (`Fontconfig::Fontconfig`) to link to your targets of interest.

### Finding the font files of interest (copy-paste example)

After `ENABLE_FONTCONFIG=ON` and linking the Fontconfig target (e.g. `target_link_libraries(${PROJECT_BINARY_NAME} Fontconfig::Fontconfig)`), include `<fontconfig/fontconfig.h>` and copy-paste the snippet below. It turns a font name into the font file the FreeType, HarfBuzz, msdfgen and stb_truetype libraries load, so the application follows the fonts the user has configured instead of a hardcoded path:

```cpp
#include <fontconfig/fontconfig.h>

#include <string>
#include <tuple>

// The font file path and the index of the face inside it (a .ttc collection
// file holds several faces), ready for FT_New_Face() and hb_face_create().
using FontFile = std::tuple<std::string, int>;

// Finds the installed font which matches a pattern like "sans-serif",
// "DejaVu Serif:bold" or "monospace:italic" best and, unless the character is
// zero, also has a glyph for that character - the fallback font lookup.
FontFile fontconfig_find_font(const char *pattern, FcChar32 character)
{
  FontFile found{"", 0};

  // Loading the configuration scans the font directories, so keep a single
  // configuration for the whole application run in the real code.
  FcConfig *config = FcInitLoadConfigAndFonts();
  FcPattern *query = FcNameParse(reinterpret_cast<const FcChar8 *>(pattern));

  if (character != 0) {
    FcCharSet *charset = FcCharSetCreate();
    FcCharSetAddChar(charset, character);
    FcPatternAddCharSet(query, FC_CHARSET, charset);
    FcCharSetDestroy(charset);
  }

  // Complete the query with the configured and the default values (this is
  // where the aliases like sans-serif resolve) and pick the closest font.
  FcConfigSubstitute(config, query, FcMatchPattern);
  FcDefaultSubstitute(query);

  FcResult result = FcResultNoMatch;
  FcPattern *match = FcFontMatch(config, query, &result);
  FcChar8 *file = nullptr;

  if (match != nullptr &&
      FcPatternGetString(match, FC_FILE, 0, &file) == FcResultMatch) {
    std::get<0>(found) = reinterpret_cast<const char *>(file);
    FcPatternGetInteger(match, FC_INDEX, 0, &std::get<1>(found));
  }

  FcPatternDestroy(match);
  FcPatternDestroy(query);
  FcConfigDestroy(config);

  return found;
}
```

For example, `fontconfig_find_font("sans-serif", 0)` gives the default sans-serif font of the system and `fontconfig_find_font("sans-serif", 0x0457)` the closest one having the `ї` letter as well - the way to pick a fallback font for the characters the main one lacks.
