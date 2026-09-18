## Вмикання інтеграції stb_truetype

Для того щоб увімкнути однофайлову заголовкову бібліотеку растеризації шрифтів [stb_truetype](https://github.com/nothings/stb) (розбір шрифтів TrueType та пакування гліфів в атлас текстури взагалі без залежностей) для проекту через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_STB_TRUETYPE`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_STB_TRUETYPE=ON
```

Заголовки stb не мають ні системи побудови, ні пакета, який можна було б шукати, тож модуль завжди завантажує їх і надає через власну інтерфейсну ціль. Дивись модуль `cmake/enablers/fonts/template-project-stb-truetype-enabler.cmake` щодо цілі (`stb_truetype`), яку слід прилінкувати до твоїх цільових об'єктів.

Версія, що завантажується, визначається CMake змінною `TEMPLATE_APP_STB_GIT_TAG` (типово гілка `master`). Директорія заголовків цілі є `SYSTEM` директорією, оскільки реалізація бібліотеки компілюється всередині одного з файлів сирців проекту, який інакше заполонили б попередження проекту.

### Пакування гліфів в атлас (приклад для копіювання)

Після `ENABLE_STB_TRUETYPE=ON` та прилінкування цілі stb_truetype (наприклад `target_link_libraries(${PROJECT_BINARY_NAME} stb_truetype)`) визнач `STB_TRUETYPE_IMPLEMENTATION` рівно в одному файлі сирців перед тим, як він підключить `<stb_truetype.h>` (інші файли сирців підключають лише заголовок) і скопіюй сніпет нижче:

```cpp
// рівно в одному файлі сирців проекту
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#include <fstream>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

// 8 бітні пікселі покриття атласу та вершини x, y, s, t двох трикутників на
// кожен символ, що робить з нього вибірку.
using TextMesh = std::tuple<std::vector<unsigned char>, std::vector<float>>;

// Пакує друковані ASCII символи шрифту в атлас 512x512 та розкладає з нього
// рядок тексту, готові для текстури GL_R8 чи зображення VK_FORMAT_R8_UNORM та
// буфера вершин.
TextMesh stb_truetype_line(const char *fontPath, const char *text)
{
  constexpr int atlasSize = 512;
  constexpr int firstChar = ' ';
  constexpr int charCount = '~' - ' ' + 1;

  // stb_truetype читає шрифт просто з байтів файлу в пам'яті.
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

  // Надвибірка 2x2 зберігає малі розміри чіткими при лінійній фільтрації.
  stbtt_PackSetOversampling(&context, 2, 2);
  const int packed = stbtt_PackFontRange(&context, font.data(), 0, 32.0f,
                                         firstChar, charCount, chars);
  stbtt_PackEnd(&context);

  if (packed == 0) {
    return {};
  }

  // x та y - це пікселі екрана (y зростає донизу, базова лінія рядка на 0), s
  // та t - координати текстури атласу.
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

Рядки атласу щільно запаковані та йдуть згори донизу - завантажуй їх так, як описано в [розділі FreeType](/doc/sections/uk_UA/5-project-build/fonts/5-41-enabling-the-freetype-library.md). Координати `s` та `t` уже спрямовують верх кожного чотирикутника на верх його гліфа, тож вершини малюються правильно як є і в OpenGL, і у Vulkan за проекції з віссю y, спрямованою вниз екрана.

stb_truetype не перевіряє меж зсувів, які читає з файлу шрифтів, тож завантажуй нею лише довірені шрифти (наприклад, ті, що постачаються разом із застосунком), а решту - через FreeType.
