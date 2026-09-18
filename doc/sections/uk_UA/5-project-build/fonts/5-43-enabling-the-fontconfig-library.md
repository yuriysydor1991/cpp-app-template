## Вмикання інтеграції Fontconfig

Для того щоб увімкнути бібліотеку [Fontconfig](https://www.freedesktop.org/wiki/Software/fontconfig/) (пошук встановлених шрифтів за їхньою родиною, накресленням та покриттям символів) для проекту, необхідно встановити значення `ON` для CMake змінної `ENABLE_FONTCONFIG`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_FONTCONFIG=ON
```

Fontconfig постачається лише зі збірками на Meson та autotools, отож вона шукається виключно в системі (встанови `libfontconfig-dev` на Debian/Ubuntu, `fontconfig-devel` на Fedora/openSUSE або `fontconfig` на Arch) - резервного механізму FetchContent немає. Дивись модуль `cmake/enablers/fonts/template-project-fontconfig-enabler.cmake` щодо цілі (`Fontconfig::Fontconfig`), яку слід прилінкувати до твоїх цільових об'єктів.

### Пошук потрібних файлів шрифтів (приклад для копіювання)

Після `ENABLE_FONTCONFIG=ON` та прилінкування цілі Fontconfig (наприклад `target_link_libraries(${PROJECT_BINARY_NAME} Fontconfig::Fontconfig)`) підключи `<fontconfig/fontconfig.h>` і скопіюй сніпет нижче. Він перетворює назву шрифту на файл шрифтів, який завантажують бібліотеки FreeType, HarfBuzz, msdfgen та stb_truetype, тож застосунок слідує шрифтам, налаштованим користувачем, замість жорстко заданого шляху:

```cpp
#include <fontconfig/fontconfig.h>

#include <string>
#include <tuple>

// Шлях до файлу шрифтів та індекс face в ньому (файл колекції .ttc містить
// декілька face), готові для FT_New_Face() та hb_face_create().
using FontFile = std::tuple<std::string, int>;

// Знаходить встановлений шрифт, що найкраще відповідає шаблону на кшталт
// "sans-serif", "DejaVu Serif:bold" чи "monospace:italic" і, якщо символ не
// нульовий, також має гліф для цього символу - пошук резервного шрифту.
FontFile fontconfig_find_font(const char *pattern, FcChar32 character)
{
  FontFile found{"", 0};

  // Завантаження конфігурації сканує директорії шрифтів, тож у справжньому
  // коді тримай одну конфігурацію на весь час роботи застосунку.
  FcConfig *config = FcInitLoadConfigAndFonts();
  FcPattern *query = FcNameParse(reinterpret_cast<const FcChar8 *>(pattern));

  if (character != 0) {
    FcCharSet *charset = FcCharSetCreate();
    FcCharSetAddChar(charset, character);
    FcPatternAddCharSet(query, FC_CHARSET, charset);
    FcCharSetDestroy(charset);
  }

  // Доповни запит налаштованими та типовими значеннями (саме тут
  // розв'язуються псевдоніми на кшталт sans-serif) та обери найближчий шрифт.
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

Наприклад, `fontconfig_find_font("sans-serif", 0)` дає типовий шрифт без засічок системи, а `fontconfig_find_font("sans-serif", 0x0457)` - найближчий, що має ще й літеру `ї`: так обирається резервний шрифт для символів, яких бракує основному.
