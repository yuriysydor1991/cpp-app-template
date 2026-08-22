## Вмикання іконок Font Awesome

Набір іконок [Font Awesome](https://fontawesome.com/) Free стає доступним проекту через CMake змінну `ENABLE_FONTAWESOME`, яка на цій гілці має значення `ON` за замовчуванням:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_FONTAWESOME=ON
```

Модуль-вмикач викачує цілий репозиторій [FortAwesome/Font-Awesome](https://github.com/FortAwesome/Font-Awesome) (поверхневим клоном одного тега), тримає його **недоторканим** та доступним і з CMake, і з коду C++, а рішення про те, що саме потрапить у двійковий файл програми, залишає за розробником. Жодного браузера, жодного ритуалу "зберегти як" для кожної іконки та жодного звертання до мережі під час роботи програми.

Набір великий, тож числа нижче — це числа зафіксованого випуску:

| Стиль | Іконок | Файл шрифту |
| --- | --- | --- |
| `solid` | 2001 | `fa-solid-900.woff2` |
| `regular` | 273 | `fa-regular-400.woff2` |
| `brands` | 609 | `fa-brands-400.woff2` |

### Змінні модуля-вмикача

Модуль `cmake/enablers/icons/template-project-fontawesome-enabler.cmake` оголошує наступне:

| Змінна | За замовчуванням | Призначення |
| --- | --- | --- |
| `ENABLE_FONTAWESOME` | `ON` | вмикає всю інтеграцію |
| `TEMPLATE_APP_FONTAWESOME_GIT` | репозиторій розробників | git репозиторій джерела |
| `TEMPLATE_APP_FONTAWESOME_GIT_TAG` | `7.3.1` | [випуск](https://github.com/FortAwesome/Font-Awesome/releases), який слід зафіксувати |
| `TEMPLATE_APP_FONTAWESOME_DIR` | порожньо | вже наявна копія репозиторію, яку слід використати замість завантаження |
| `FONTAWESOME_STYLES` | `solid;regular;brands` | стилі, які слід зробити доступними |
| `FONTAWESOME_QT_RESOURCE_PREFIX` | `/icons` | префікс згенерованих Qt маніфестів |
| `FONTAWESOME_GRESOURCE_PREFIX` | `/ua/org/kytok/template/<binary>/icons` | префікс згенерованих GResource маніфестів |
| `FONTAWESOME_GENERATE_FULL_MANIFESTS` | `ON` | записувати маніфести ресурсів із цілим набором іконок |

Завантаження копії репозиторію важке, тож для повторного використання між директоріями побудови (або для роботи без мережі) слід вказати:

```
cmake -S . -B build -DTEMPLATE_APP_FONTAWESOME_DIR=/opt/Font-Awesome
```

Після конфігурації модуль експортує структуру копії для решти CMake файлів: `FONTAWESOME_ROOT_DIR`, `FONTAWESOME_SVGS_DIR`, `FONTAWESOME_WEBFONTS_DIR`, `FONTAWESOME_SPRITES_DIR`, `FONTAWESOME_METADATA_DIR`, `FONTAWESOME_LICENSE_FILE` та `FONTAWESOME_ICONS_COUNT`.

### Доступ до іконок із коду

Назви іконок саме тієї копії репозиторію, що використовується, збираються під час конфігурації та генеруються у директорію побудови, тож цілий набір компілюється у двійковий файл, і жодна директорія не сканується під час роботи програми. Підсистема `src/fontawesome` надає їх:

```cpp
#include "src/fontawesome/icons/FontAwesomeIcons.h"

const auto icons = fontawesome::FontAwesomeIcons::create();

icons->count();               // кожна іконка кожного увімкненого стилю
icons->all();                 // цілий набір
icons->ofStyle("brands");     // лише один стиль
icons->find("solid", "gear"); // одна іконка, nullptr коли такої немає
icons->search("arrow");       // кожна іконка, назва якої містить частину
```

Окрема іконка виводить кожну назву, яку від неї вимагає навколишній код:

```cpp
const auto icon = icons->find("solid", "folder-open");

icon->name();          // "folder-open"
icon->fileName();      // "folder-open.svg"
icon->alias();         // "solid/folder-open.svg"
icon->relativePath();  // "svgs/solid/folder-open.svg"
icon->filePath();      // абсолютний шлях в середині копії репозиторію
icon->style()->webfontFileName();  // "fa-solid-900.woff2"
```

Заголовок `fontawesome-decls.h`, згенерований поруч із `project-global-decls.h`, несе саму копію репозиторію: `FONTAWESOME_VERSION`, `FONTAWESOME_ROOT_DIR`, `FONTAWESOME_SVGS_DIR`, `FONTAWESOME_WEBFONTS_DIR`, `FONTAWESOME_LICENSE_FILE` та обидва префікси ресурсів.

Перегляд набору звичайними інструментами працює так само добре:

```
find build/_deps/fontawesome-src/svgs -iname '*arrow*'
```

Галерея [fontawesome.com/search](https://fontawesome.com/search) показує ті самі назви.

### Передача іконок у систему ресурсів графічного інтерфейсу

Іконка, скомпільована у двійковий файл, більше не є файлом, тож інструментарій графічного інтерфейсу знаходить її через власну систему ресурсів. Модуль `cmake/enablers/icons/template-project-fontawesome-resources.cmake` записує маніфест для того інструментарію, що використовується, ключуючи кожну іконку її псевдонімом `<стиль>/<назва>.svg`:

```cmake
template_project_fontawesome_write_qrc(
  "${CMAKE_CURRENT_BINARY_DIR}/fontawesome.qrc"
  ICONS solid/folder-open solid/gear regular/user brands/github
)

template_project_fontawesome_write_gresource(
  "${CMAKE_CURRENT_BINARY_DIR}/fontawesome.gresource.xml"
  COMPRESSED
  STYLES brands
)
```

Обидві функції приймають необов'язковий `PREFIX`, перелік `STYLES` (кожна іконка вказаних стилів) та перелік `ICONS` (окремі потрібні іконки); якщо не вказано жодного з них — обирається цілий доступний набір.

Для гілки на основі [Qt6](https://www.qt.io/development/qt-framework/qt6) записаний маніфест йде просто у [qt_add_resources](https://doc.qt.io/qt-6/qt-add-resources.html) (дивись [The Qt Resource System](https://doc.qt.io/qt-6/resources.html)):

```cmake
qt_add_resources(
  FONTAWESOME_RESOURCE_SOURCES
  "${CMAKE_CURRENT_BINARY_DIR}/fontawesome.qrc"
)

target_sources(${PROJECT_BINARY_NAME} PRIVATE ${FONTAWESOME_RESOURCE_SOURCES})
```

Префікс вже знаходиться в середині записаного маніфесту, тож тут слід викликати саме ту форму `qt_add_resources`, що приймає `.qrc` файли. Шлях часу виконання надає локатор, тож маніфест та код ніколи не розходяться:

```cpp
#include "src/fontawesome/resources/FontAwesomeQtResourcePath.h"

const auto resources = fontawesome::FontAwesomeQtResourcePath::create();

const QIcon openIcon{QString::fromStdString(resources->of(icon))};
// resources->of(icon)    -> ":/icons/solid/folder-open.svg"
// resources->uriOf(icon) -> "qrc:/icons/solid/folder-open.svg"
```

Для гілки на основі [Gtkmm](https://gtkmm.gnome.org/en/index.html) маніфест компілюється командою `glib-compile-resources` точно так само, як той, що гілка вже несе (дивись документацію [GResource](https://docs.gtk.org/gio/struct.Resource.html)):

```cmake
add_custom_command(
  OUTPUT ${FONTAWESOME_RESOURCE_C}
  COMMAND ${GRSC_EXEC}
          --target=${FONTAWESOME_RESOURCE_C}
          --generate-source
          "${CMAKE_CURRENT_BINARY_DIR}/fontawesome.gresource.xml"
  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/fontawesome.gresource.xml"
)
```

```cpp
#include "src/fontawesome/resources/FontAwesomeGResourcePath.h"

const auto resources = fontawesome::FontAwesomeGResourcePath::create();

Gtk::Image image;
image.set_from_resource(resources->of(icon));
// resources->of(icon)    -> "/ua/org/kytok/template/CppAppTemplate/icons/solid/folder-open.svg"
// resources->uriOf(icon) -> "resource:///ua/org/kytok/template/CppAppTemplate/icons/solid/folder-open.svg"
```

Дивись документацію [Gtk::Image](https://docs.gtk.org/gtk4/class.Image.html) та [QIcon](https://doc.qt.io/qt-6/qicon.html) щодо віджетів, які приймають ці шляхи.

### Цілий набір в одному маніфесті

При `FONTAWESOME_GENERATE_FULL_MANIFESTS=ON` модуль-вмикач записує обидва маніфести для цілого набору іконок у директорію побудови та вказує на них змінними `FONTAWESOME_FULL_QRC` і `FONTAWESOME_FULL_GRESOURCE_XML`, готовими до компіляції як є.

Слід памʼятати, що вбудовування всіх іконок коштує близько 12 МіБ даних SVG (маніфест GResource записується з атрибутом `compressed="true"`, що зменшує цей обсяг приблизно вдвічі). Вибір тих іконок, які програма справді показує — дешевший та звичний шлях; повні маніфести існують для випадків, коли набір має бути доступним для перегляду під час роботи програми.

### Ліцензування

Копія репозиторію тримає власний `LICENSE.txt`, і так само має чинити кожне розповсюдження цих матеріалів: Font Awesome Free ліцензовано за [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) щодо іконок, за [SIL OFL 1.1](https://openfontlicense.org/) щодо шрифтів та за [MIT](https://opensource.org/license/mit) щодо коду. Змінна `FONTAWESOME_LICENSE_FILE` (та однойменне оголошення) вказує на цей файл, тож крок пакування встановлює його без вгадування шляхів. Повні умови — на [fontawesome.com/license/free](https://fontawesome.com/license/free).
