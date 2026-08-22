## Enabling the Font Awesome icons

The [Font Awesome](https://fontawesome.com/) Free icon set is made available to the project by the `ENABLE_FONTAWESOME` CMake variable, which is `ON` by default on this branch:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_FONTAWESOME=ON
```

The enabler checks out the whole [FortAwesome/Font-Awesome](https://github.com/FortAwesome/Font-Awesome) repository (a shallow single tag clone), keeps it **intact** and reachable both from CMake and from the C++ code, and leaves the decision of what ends up inside the application binary to the developer. No browser, no icon by icon "save as" ritual and no network access at the application run time.

The whole set is a big one, so the numbers below are the ones of the pinned release:

| Style | Icons | Webfont file |
| --- | --- | --- |
| `solid` | 2001 | `fa-solid-900.woff2` |
| `regular` | 273 | `fa-regular-400.woff2` |
| `brands` | 609 | `fa-brands-400.woff2` |

### The enabler variables

The `cmake/enablers/icons/template-project-fontawesome-enabler.cmake` module declares the following:

| Variable | Default | Meaning |
| --- | --- | --- |
| `ENABLE_FONTAWESOME` | `ON` | enables the whole integration |
| `TEMPLATE_APP_FONTAWESOME_GIT` | the upstream repository | the git source repository |
| `TEMPLATE_APP_FONTAWESOME_GIT_TAG` | `7.3.1` | the [release](https://github.com/FortAwesome/Font-Awesome/releases) to pin |
| `TEMPLATE_APP_FONTAWESOME_DIR` | empty | an already available checkout to reuse instead of downloading one |
| `FONTAWESOME_STYLES` | `solid;regular;brands` | the styles to make available |
| `FONTAWESOME_QT_RESOURCE_PREFIX` | `/icons` | the prefix of the generated Qt manifests |
| `FONTAWESOME_GRESOURCE_PREFIX` | `/ua/org/kytok/template/<binary>/icons` | the prefix of the generated GResource manifests |
| `FONTAWESOME_GENERATE_FULL_MANIFESTS` | `ON` | write the resource manifests carrying the whole icon set |

A checkout is a heavy download, so reuse one across the build directories (or work offline) with:

```
cmake -S . -B build -DTEMPLATE_APP_FONTAWESOME_DIR=/opt/Font-Awesome
```

Once configured, the module exports the checkout layout for the rest of the CMake files: `FONTAWESOME_ROOT_DIR`, `FONTAWESOME_SVGS_DIR`, `FONTAWESOME_WEBFONTS_DIR`, `FONTAWESOME_SPRITES_DIR`, `FONTAWESOME_METADATA_DIR`, `FONTAWESOME_LICENSE_FILE` and `FONTAWESOME_ICONS_COUNT`.

### Reaching the icons from the code

The icon names of the very checkout in use are gathered at the configure time and generated into the build directory, so the complete set is compiled into the binary and no directory is ever scanned at the run time. The `src/fontawesome` subsystem serves them:

```cpp
#include "src/fontawesome/icons/FontAwesomeIcons.h"

const auto icons = fontawesome::FontAwesomeIcons::create();

icons->count();               // every icon of every enabled style
icons->all();                 // the whole set
icons->ofStyle("brands");     // one style only
icons->find("solid", "gear"); // a single icon, nullptr when there is none
icons->search("arrow");       // every icon which name contains the part
```

A single icon derives every name the surrounding code asks it for:

```cpp
const auto icon = icons->find("solid", "folder-open");

icon->name();          // "folder-open"
icon->fileName();      // "folder-open.svg"
icon->alias();         // "solid/folder-open.svg"
icon->relativePath();  // "svgs/solid/folder-open.svg"
icon->filePath();      // the absolute path inside the checkout
icon->style()->webfontFileName();  // "fa-solid-900.woff2"
```

The `fontawesome-decls.h` header generated next to the `project-global-decls.h` one carries the checkout itself: `FONTAWESOME_VERSION`, `FONTAWESOME_ROOT_DIR`, `FONTAWESOME_SVGS_DIR`, `FONTAWESOME_WEBFONTS_DIR`, `FONTAWESOME_LICENSE_FILE` and both resource prefixes.

Browsing the set with the ordinary tools works just as well:

```
find build/_deps/fontawesome-src/svgs -iname '*arrow*'
```

The [fontawesome.com/search](https://fontawesome.com/search) gallery shows the very same names.

### Handing the icons to a GUI resource system

An icon compiled into a binary is no file any more, so a GUI toolkit resolves it through it's own resource system. The `cmake/enablers/icons/template-project-fontawesome-resources.cmake` module writes the manifest of the toolkit in use, keying every icon by it's `<style>/<name>.svg` alias:

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

Both functions take an optional `PREFIX`, a `STYLES` list (every icon of the given styles) and an `ICONS` list (the single icons of interest); requesting neither selects the whole available set.

For a [Qt6](https://www.qt.io/development/qt-framework/qt6) branch the written manifest goes straight into [qt_add_resources](https://doc.qt.io/qt-6/qt-add-resources.html) (see [The Qt Resource System](https://doc.qt.io/qt-6/resources.html)):

```cmake
qt_add_resources(
  FONTAWESOME_RESOURCE_SOURCES
  "${CMAKE_CURRENT_BINARY_DIR}/fontawesome.qrc"
)

target_sources(${PROJECT_BINARY_NAME} PRIVATE ${FONTAWESOME_RESOURCE_SOURCES})
```

The prefix already sits inside the written manifest, so the variable based `qt_add_resources` form (the one taking the `.qrc` files) is the one to call here. The run time path comes from the locator, so the manifest and the code never drift apart:

```cpp
#include "src/fontawesome/resources/FontAwesomeQtResourcePath.h"

const auto resources = fontawesome::FontAwesomeQtResourcePath::create();

const QIcon openIcon{QString::fromStdString(resources->of(icon))};
// resources->of(icon)    -> ":/icons/solid/folder-open.svg"
// resources->uriOf(icon) -> "qrc:/icons/solid/folder-open.svg"
```

For a [Gtkmm](https://gtkmm.gnome.org/en/index.html) branch the manifest is compiled by `glib-compile-resources` exactly like the one the branch already carries (see the [GResource](https://docs.gtk.org/gio/struct.Resource.html) documentation):

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

See the [Gtk::Image](https://docs.gtk.org/gtk4/class.Image.html) and the [QIcon](https://doc.qt.io/qt-6/qicon.html) documentation for the widgets taking those paths.

### The whole set in one manifest

With `FONTAWESOME_GENERATE_FULL_MANIFESTS=ON` the enabler writes both manifests for the complete icon set into the build directory and points the `FONTAWESOME_FULL_QRC` and the `FONTAWESOME_FULL_GRESOURCE_XML` variables at them, ready to be compiled as they are.

Keep in mind that embedding all of the icons costs about 12 MiB of SVG data (the GResource one is written with the `compressed="true"` attribute, which roughly halves it). Selecting the icons an application actually shows is the cheaper and the usual way; the complete manifests are there for the cases where the set has to be browsable at the run time.

### Licensing

The checkout keeps it's own `LICENSE.txt` and so must every redistribution of the assets: Font Awesome Free is licensed under the [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) for the icons, the [SIL OFL 1.1](https://openfontlicense.org/) for the fonts and the [MIT](https://opensource.org/license/mit) one for the code. The `FONTAWESOME_LICENSE_FILE` variable (and the declaration of the same name) points at the file, so a packaging step installs it with no path guessing. The full terms are at [fontawesome.com/license/free](https://fontawesome.com/license/free).
