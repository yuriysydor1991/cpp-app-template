## Enabling the GNU gettext translations

In order to translate the messages of the project into the language of the user with the [GNU gettext](https://www.gnu.org/software/gettext/) message catalogs set an `ON` value to the `ENABLE_GETTEXT` CMake variable (it is the default one for the `appGettext` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_GETTEXT=ON
cmake --build build --target all
```

The [cmake/enablers/i18n/template-project-gettext-enabler.cmake](/cmake/enablers/i18n/template-project-gettext-enabler.cmake) module looks for the libintl library, a part of the GNU C library on the GNU/Linux based OS, and for the gettext tools which compile the translations, so install them (the `scripts/packages/install-*.sh` scripts do it too):

```
sudo apt install -y gettext
```

The RPM-based distributions name the package `gettext` too, while FreeBSD splits it into the `gettext-runtime` (the libintl) and the `gettext-tools` ones. The module provides the libintl as the `Intl::Intl` target, the one the `FindIntl` module of the CMake 3.20 and newer creates and the module builds out of the `FindIntl` variables for the older CMake versions, so link it to your target(s) of interest. It's include directory matters on FreeBSD, whose base compiler searches no `/usr/local/include` directory the libintl header is installed into:

```
target_link_libraries(${PROJECT_BINARY_NAME} Intl::Intl)
```

### Translating the messages

Include the [src/gettext/tr.h](/src/gettext/tr.h) header and pass the English messages through the `gettexti::tr` call, or through the `gettexti::trn` one for a message which depends on a count (e.g. the Ukrainian language has three plural forms of it):

```
#include "src/gettext/tr.h"

std::cout << gettexti::tr("Usage:") << std::endl;
std::cout << count << " " << gettexti::trn("file", "files", count) << std::endl;
```

Pass the string literals only, since the `xgettext` tool extracts the messages to translate out of the sources by the `tr` and the `trn` names. A `// TRANSLATORS:` comment right above the call reaches the translators as a hint. The help and the version messages of the `ApplicationHelpPrinter` and the `ApplicationVersionPrinter` classes and the greeting of the `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file are translated this way, while the messages of the `LOGx` macros stay English, since the developers read and search the logs.

### The po directory

Every `po/<language>.po` file translates the messages into it's language, e.g. the [po/uk.po](/po/uk.po) one into the Ukrainian. The build compiles it into the `locale/<language>/LC_MESSAGES/<binary name>.mo` catalog of the build tree (the `gettext-catalogs` target) and the install puts the catalog into the `share/locale` directory (the `CMAKE_INSTALL_LOCALEDIR` one). The text domain is the project binary name, so a renamed project keeps it's translations. The `msgfmt --check` call fails the build on a broken translation, e.g. a missing plural form.

The `gettext-pot` target extracts the messages of the sources into the `po/<binary name>.pot` template of the build tree, while the `gettext-update-po` one merges the template into every po file once the messages of the sources change, so the translators see the new and the changed ones:

```
cmake --build build --target gettext-update-po
```

A new language starts out of the template, e.g. the German one:

```
cmake --build build --target gettext-pot
msginit --input=build/po/CppAppTemplate.pot --locale=de_DE.UTF-8 --output-file=po/de.po
```

Translate the file in a text editor or with a tool like the [Poedit](https://poedit.net/) one and build the project again: the configure picks the new po file up by itself.

### The language of the user

The `ApplicationFactory` binds the catalogs through the `gettexti::GettextController` class of the [src/gettext/GettextController.h](/src/gettext/GettextController.h) file before the application runs. The controller activates the messages locale of the environment (the `LC_ALL`, the `LC_MESSAGES` or the `LANG` variable, while the `LANGUAGE` one may list the languages to try) and gives the translations in the UTF-8:

```
LANG=uk_UA.UTF-8 ./build/src/CppAppTemplate --help
```

Only the messages category of the locale is activated, since the whole locale of the user switches the number formatting too: e.g. the `std::stod` and the `std::to_string` calls read and write the `1,5` instead of the `1.5` under the `uk_UA` one.

The translations show up only while the locale is installed on the system, otherwise the libintl translates nothing, even with the `LANGUAGE` variable, and the controller logs a warning about it. The GNU/Linux based containers usually lack the locales, so install the `locales-all` package (Debian, Ubuntu) or the `glibc-langpack-uk` one (Fedora, RHEL), while FreeBSD carries it's locales in the base system. The Docker images and the CI pipelines of the branch install the `locales-all` package, so the test cases translating into the Ukrainian language run there, while elsewhere they skip themselves without the locale.

### Finding the catalogs

The `gettexti::CatalogsLocator` class gives the catalogs directory to bind, the first existing one of:

| Directory | Serves |
| --- | --- |
| the `../share/locale` one next to the executable | an installed or relocated executable, e.g. the AppImage or the snap one mounted anywhere, or the one of a DEB package installed into the `/usr` prefix |
| the `locale` one of the build tree | the executable started from the build tree |
| the `CMAKE_INSTALL_FULL_LOCALEDIR` one | the rest of the cases |

The path of the running executable comes from the `/proc/self/exe` link on Linux, so the executable started through the `PATH` finds it's catalogs too, and from the first command line argument elsewhere.

### Merging into the other branches

The `gettexti::tr` name clashes with none of the `_()` macros of the GLib and the wxWidgets, and the translations come in the UTF-8 the GTK, the wxWidgets (`wxString::FromUTF8`) and the Qt (`QString::fromUtf8`) toolkits expect. The GTK and the Qt call the `setlocale(LC_ALL, "")` on their own, so reset the `LC_NUMERIC` category to the `"C"` one after the toolkit starts if the code reads or writes the floating point numbers. The `GtkBuilder` interface files translate their `translatable="yes"` properties with the bound default text domain, once their messages get into the po files (add the `.ui` files to the sources of the `gettext-pot` target), while the Qt branches keep translating their QML with the Qt Linguist tools.

### Packaging

The DEB, the RPM and the FreeBSD pkg packages carry the compiled catalogs together with the executable. The flatpak manifest keeps them inside the application (the `separate-locales` option is off), since a single file bundle carries no separate locale extension, and the snap compiles them with the `gettext` package of it's build packages.
