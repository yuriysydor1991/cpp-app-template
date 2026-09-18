## Enabling the desktop application packaging

A windowed (GUI) application belongs to the application menus of the desktop, while a console one runs inside a terminal. The `ENABLE_DESKTOP_APPLICATION` CMake variable tells the packagers which kind the project binary is - the GUI branches of the template turn it on by default and the console ones leave it off:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_DESKTOP_APPLICATION=ON
```

With the variable on, the install step places the [desktop entry](https://specifications.freedesktop.org/desktop-entry-spec/latest/) and the icon of the application into the `share/applications` and the `share/icons/hicolor/scalable/apps` directories, both named after the reverse DNS id of the application (e.g. `ua.org.kytok.template.CppAppTemplate.desktop`), and every packager marks the application as a desktop one:

- the flatpak exports the desktop entry and the icon to the desktop menus, and its [AppStream](https://www.freedesktop.org/software/appstream/docs/) metainfo turns into a `desktop-application` component launched through that desktop entry;
- the snap gets the desktop entry and the `desktop`, `desktop-legacy`, `wayland`, `x11` and `opengl` interfaces a window needs;
- the AppImage desktop entry gets the `Terminal=false` key;
- the DEB, RPM and FreeBSD pkg packages carry the desktop entry and the icon, so the desktop menus list the installed application.

The desktop entry and the icon are configured from the templates of the [misc/packagers/desktop](/misc/packagers/desktop) directory, which the AppImage uses for a console application as well:

- [desktop.entry.in](/misc/packagers/desktop/desktop.entry.in) - the desktop entry;
- [desktop.icon.svg.in](/misc/packagers/desktop/desktop.icon.svg.in) - the icon the desktop entry names.

The following cache variables may optionally be overridden:

- `TEMPLATE_PROJECT_DESKTOP_CATEGORIES` - the semicolon terminated desktop entry categories (default: `Utility;`). Other typical values are `Development;`, `Network;`, `Graphics;`.
- `DESKTOP_ICON_SRC` - the SVG icon source file (default: the template one above).

In order to examine the details visit the [cmake/enablers/packagers/template-project-desktop-entry.cmake](/cmake/enablers/packagers/template-project-desktop-entry.cmake) file.
