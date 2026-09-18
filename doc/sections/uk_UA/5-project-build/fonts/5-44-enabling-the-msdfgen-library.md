## Вмикання інтеграції msdfgen

Для того щоб увімкнути бібліотеку [msdfgen](https://github.com/Chlumsky/msdfgen) (багатоканальні поля знакових відстаней гліфів, які GPU масштабує та обертає, зберігаючи їхні кути гострими) для проекту, використовуючи встановлену версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_MSDFGEN`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_MSDFGEN=ON -DENABLE_FREETYPE=ON
```

msdfgen завантажує шрифти через FreeType, отож залиш `ENABLE_FREETYPE=ON` (або наявну системну FreeType) щоб залежність вирішилась. Дивись модуль `cmake/enablers/fonts/template-project-msdfgen-enabler.cmake` щодо цілі (`msdfgen::msdfgen` як для системної версії, так і для побудови через FetchContent), яку слід прилінкувати до твоїх цільових об'єктів.

Версія, що завантажується, визначається CMake змінною `TEMPLATE_APP_MSDFGEN_GIT_TAG` (типово `v1.13`). Модуль також перевизначає п'ять налаштувань msdfgen всупереч оригінальним типовим значенням, які ламають звичайну побудову споживача або будують більше, ніж йому потрібно:

- `MSDFGEN_USE_VCPKG` вимкнено, оскільки воно вимагає інструментарію vcpkg;
- `MSDFGEN_USE_SKIA` вимкнено, оскільки воно вимагає бібліотеки Skia;
- `MSDFGEN_DISABLE_SVG` увімкнено, оскільки введення форм з SVG вимагає бібліотеки tinyxml2;
- `MSDFGEN_DISABLE_PNG` увімкнено, оскільки виведення у файли PNG вимагає бібліотеки libpng;
- `MSDFGEN_BUILD_STANDALONE` вимкнено, оскільки гліфам, що генеруються під час виконання, не потрібен генератор командного рядка.

Усі п'ять лишаються звичайними кеш змінними, тож передай, наприклад, `-DMSDFGEN_DISABLE_PNG=OFF` на машині зі встановленою libpng, щоб повернути `msdfgen::savePng()`. Цілі побудови через FetchContent позначено як `SYSTEM`, щоб уберегти їхні заголовки від попереджень проекту.

### Генерування полів відстаней гліфів (приклад для копіювання)

Після `ENABLE_MSDFGEN=ON` та прилінкування цілі msdfgen (наприклад `target_link_libraries(${PROJECT_BINARY_NAME} msdfgen::msdfgen)`) підключи `<msdfgen.h>` разом з `<msdfgen-ext.h>` і скопіюй сніпет нижче:

```cpp
#include <msdfgen-ext.h>
#include <msdfgen.h>

#include <vector>

// Генерує багатоканальне поле знакових відстаней 32x32 для одного символу та
// перетворює його на RGB8 тексели текстури для вибірки з лінійною фільтрацією,
// починаючи з нижнього рядка, як на це очікують текстури OpenGL.
std::vector<unsigned char> msdfgen_glyph(const char *fontPath,
                                         msdfgen::unicode_t character)
{
  std::vector<unsigned char> texels;

  if (msdfgen::FreetypeHandle *ft = msdfgen::initializeFreetype()) {
    if (msdfgen::FontHandle *font = msdfgen::loadFont(ft, fontPath)) {
      msdfgen::Shape shape;

      // Нормалізоване до EM масштабування дає контур гліфа в одиницях EM, де
      // 1.0 - це весь розмір шрифту.
      if (msdfgen::loadGlyph(shape, font, character,
                             msdfgen::FONT_SCALING_EM_NORMALIZED)) {
        shape.normalize();

        // Розподіли ребра по трьох каналах, зберігаючи з'єднання ребер до 3
        // радіан (близько 172 градусів) гострими кутами.
        msdfgen::edgeColoringSimple(shape, 3.0);

        // 32 пікселі на EM, гліф зсунуто на 0.125 EM від кута растра, а
        // відстані закодовано в діапазоні завширшки 0.125 EM (4 пікселі)
        // поперек його ребер. Передай msdfgen::Y_DOWNWARD третім аргументом
        // для порядку рядків згори донизу, як у зображень Vulkan.
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

Завантаж тексели в текстуру `GL_RGB8` після `glPixelStorei(GL_UNPACK_ALIGNMENT, 1)` (3 байтні тексели порушують типове 4 байтне вирівнювання рядків) або додай альфа канал для зображення `VK_FORMAT_R8G8B8A8_UNORM` з Vulkan. В обох випадках формат має лишатися лінійним, адже sRGB спотворить збережені відстані.

### Малювання поля відстаней

Фрагментний шейдер бере медіану трьох каналів як відстань до краю гліфа та перетворює її на покриття зі згладженим краєм за будь-якого розміру, з яким малюється чотирикутник:

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

Uniform змінна `screenPxRange` містить діапазон відстаней у пікселях екрана: діапазон завширшки 4 пікселі поля 32x32 вище, намальованого на чотирикутнику 64x64 пікселі, дає `4 * 64 / 32 = 8`.

Для Vulkan скомпілюй той самий шейдер у SPIR-V з кваліфікаторами `layout(location = ...)` на його вході та виході, кваліфікатором `layout(binding = ...)` на семплері та двома звичайними uniform змінними, перенесеними в uniform або push constant блок.

### Використання кожного типу шрифтів (приклади для копіювання)

msdfgen завантажує кожен контурний шрифт, який відкриває FreeType - TrueType, OpenType (CFF), `.woff` / `.woff2` та Type 1 - тими ж `msdfgen::loadFont()` та `msdfgen::loadGlyph()`, що й у сніпеті вище. Варіативні шрифти та колекції потребують ще одного кроку:

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H
// FreeType іде першою, адже вона вмикає msdfgen::adoptFreetypeFont()
#include <msdfgen-ext.h>
#include <msdfgen.h>

// Відкриває варіативний шрифт із заданою товщиною, наприклад 700 для
// жирного. msdfgen приймає осі за іменами, які дає їм шрифт ("Weight" тут), а
// msdfgen::listFontVariationAxes() перелічує їх разом з їхніми діапазонами.
msdfgen::FontHandle *msdfgen_load_weight(msdfgen::FreetypeHandle *ft,
                                         const char *fontPath, double weight)
{
  msdfgen::FontHandle *font = msdfgen::loadFont(ft, fontPath);

  if (font != nullptr) {
    // false для шрифтів без такої осі, які тоді лишаються як є
    msdfgen::setFontVariationAxis(ft, font, "Weight", weight);
  }

  return font;
}

// Відкриває face з заданим індексом із колекції шрифтів (.ttc, .otc), адже
// msdfgen::loadFont() бере лише перший face. msdfgen::destroyFont() лишає сам
// face для FT_Done_Face().
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

Для `FT_New_Face()` у сніпеті колекції прилінкуй також ціль `Freetype::Freetype`. Растрові шрифти (`.pcf`, `.bdf`, `.fon`) та растрові кольорові емодзі (CBDT, sbix) не мають контурів, від яких можна виміряти відстані - `msdfgen::loadGlyph()` дає для них порожню форму - тож малюй їх пікселями гліфів з [розділу FreeType](/doc/sections/uk_UA/5-project-build/fonts/5-41-enabling-the-freetype-library.md).
