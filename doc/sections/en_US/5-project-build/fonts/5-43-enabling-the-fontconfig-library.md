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

### Finding the fonts of each type (copy-paste example)

Fontconfig records the type of every installed font, so a pattern of its properties lists all the fonts of a type:

```cpp
#include <fontconfig/fontconfig.h>

#include <cstdio>

// Prints the file, the face index and the format of every installed font of
// the type a pattern selects, e.g. ":fontformat=CFF" for the OpenType CFF
// fonts or ":color=True" for the color (emoji) ones.
void fontconfig_list_fonts(const char *pattern)
{
  FcConfig *config = FcInitLoadConfigAndFonts();
  FcPattern *query = FcNameParse(reinterpret_cast<const FcChar8 *>(pattern));
  FcObjectSet *properties =
      FcObjectSetBuild(FC_FILE, FC_INDEX, FC_FONTFORMAT, nullptr);
  FcFontSet *fonts = FcFontList(config, query, properties);

  for (int i = 0; fonts != nullptr && i < fonts->nfont; ++i) {
    FcChar8 *file = nullptr;
    FcChar8 *format = nullptr;
    int index = 0;

    FcPatternGetString(fonts->fonts[i], FC_FILE, 0, &file);
    FcPatternGetString(fonts->fonts[i], FC_FONTFORMAT, 0, &format);
    FcPatternGetInteger(fonts->fonts[i], FC_INDEX, 0, &index);

    std::printf("%s (face %d, %s)\n", reinterpret_cast<const char *>(file),
                index, format != nullptr ? reinterpret_cast<const char *>(format) : "?");
  }

  FcFontSetDestroy(fonts);
  FcObjectSetDestroy(properties);
  FcPatternDestroy(query);
  FcConfigDestroy(config);
}
```

| Font type | Pattern |
| --- | --- |
| TrueType | `:fontformat=TrueType` |
| OpenType (CFF) | `:fontformat=CFF` |
| PostScript Type 1 | `:fontformat=Type 1` |
| Web fonts | `:fontwrapper=WOFF`, `:fontwrapper=WOFF2` (Fontconfig 2.15 and newer) |
| Collections | `:index=1` (the second face of every collection) |
| Variable fonts | `:variable=True` |
| Color fonts (emoji) | `:color=True` |
| Bitmap fonts | `:scalable=False`, `:fontformat=PCF`, `:fontformat=BDF` |

The listed file and face index go straight to the `FT_New_Face()` of FreeType or the `hb_face_create()` of HarfBuzz. Many distributions keep the bitmap fonts out of use with a `70-no-bitmaps*.conf` Fontconfig configuration file, and the bitmap patterns list nothing there.
