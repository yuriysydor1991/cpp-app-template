## The libadwaita main window

The whole application window of this branch is built out of the
[libadwaita](https://gnome.pages.gitlab.gnome.org/libadwaita/) widgets by the
`Gtkmm4i::main_window::AdwaitaWindow` class, which lives in
[src/gtkmm4/main-window/AdwaitaWindow.h](/src/gtkmm4/main-window/AdwaitaWindow.h).

### Why the window is not a Gtk::Window descendant

libadwaita ships no official C++ binding, so it is consumed through its C API
next to the gtkmm-4.0 one. Both bindings wrap the very same GObject instances,
which is what makes the mixing safe, but it also means an `AdwApplicationWindow`
can not simply become a C++ base class the way `Gtk::Window` does. The
`AdwaitaWindow` therefore owns the window pointer instead of deriving from it,
and hands the ready window over to the caller as a `Gtk::Window*` through
`Glib::wrap`. The GTK widget tree owns every child widget, and the running
`Gtk::Application` owns the window itself, so the class frees nothing on its
own.

### The window layout

```
AdwApplicationWindow          <- the window, with the libadwaita rounded corners
└── AdwToolbarView            <- puts the header bar inside the window content
    ├── AdwHeaderBar          <- the top bar
    │   └── AdwWindowTitle    <- the project name, version and the build commit
    └── GtkBox (vertical)     <- the replaceable placeholder content
        ├── GtkLabel          <- the heading, enlarged by the title-1 class
        ├── GtkLabel          <- the smaller description, body and dim-label
        └── GtkPicture        <- the logo from the GResource bundle, grown over
                                 all the free height with a proportional width
```

An `AdwApplicationWindow` with an `AdwToolbarView` is the recommended
libadwaita window composition. Unlike a plain `Gtk::Window` with a title bar, it
keeps the header bar inside the window content, which is what enables the
adaptive libadwaita behaviour and the correct rounded window corners.

The content itself is a plain vertical `GtkBox` and not an `AdwStatusPage`,
because a status page centers its whole content vertically, while the texts here
belong to the very top of the window. Neither label expands, so the box hands
them their natural height first and leaves everything below to the
`GtkPicture`, which does expand.

The heading is enlarged by the `title-1` libadwaita typography style class - the
H1 counterpart of the heading styles - and the description carries the smaller
`body` one together with the `dim-label`. No custom CSS rule is involved, so the
whole window follows the light and dark libadwaita palettes.

A `GtkPicture` is used instead of a `GtkImage`, because an image draws its
texture at a fixed pixel size, while a picture scales the very same texture into
whatever allocation it gets. The `AdwaitaWindow::logo_content_fit` constant
decides how it scales: the default `GTK_CONTENT_FIT_CONTAIN` grows the logo
until it hits the free height and keeps its width proportional to it, so the
logo never gets deformed. The `GTK_CONTENT_FIT_FILL` stretches it over the whole
free area instead, and the `GTK_CONTENT_FIT_COVER` fills that area keeping the
ratio but cropping whatever does not fit.

`adw_init()` is called by the `Gtkmm4i::GtkmmIniter::run` from the application
`activate` handler and not before the `Gtk::Application::run` call, because it
needs the GTK display that the application opens for itself.

### Starting the development

Replace the widgets created by the `AdwaitaWindow::create_content` method with
the real application ones. The `create_header_bar`, `create_content`,
`create_title_label`, `create_description_label` and `create_logo_picture`
methods are all virtual, so a descendant class may replace any single part
without touching the window assembly itself.

The GResource bundle and the additional stylesheet stay exactly the same as on
the plain `appGtkmm4` branch - see the [Resource embedding](/doc/sections/en_US/4-project-structure/4-6-gtkmm4-resource-embedding.md)
section. The libadwaita stylesheet is applied first and the bundled
`main-window.css` on top of it, with the `GTK_STYLE_PROVIDER_PRIORITY_APPLICATION`
priority.

### Requirements and the build option

The branch needs the libadwaita development files - the `libadwaita-1-dev`
package on the Debian based distributions, `libadwaita-devel` on the Fedora
based ones. The [cmake/enablers/template-project-libadwaita-enabler.cmake](/cmake/enablers/template-project-libadwaita-enabler.cmake)
module finds the library with `pkg_check_modules(ADWAITA libadwaita-1 REQUIRED)`
and exposes the `ENABLE_LIBADWAITA` option, which defaults to `ON`. There is no
FetchContent fallback, exactly like for the gtkmm-4.0 itself.

### Tests

The `CTEST_AdwaitaWindow` component test covers everything the window decides
before it touches a display: the shown strings, the GResource paths, the style
classes and the content fit of the layout, the requested geometry and the
argument guard of the `build` method. It also asserts
the libadwaita runtime version, which proves the enabler found the library and
the binary really links against it.

The widget tree itself is not covered, because building any GTK4 widget requires
an opened display, and the project test suites are expected to run headless on a
CI agent.
