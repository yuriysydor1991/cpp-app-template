## The toolkit messages

The application logs through the `src/log/log.h` macroses, while GTK, GDK, GIO, Pango, gtkmm and GLib itself report through the GLib logging, which writes into the standard output and the standard error streams of the process by it's own default writer. So without any further ado a toolkit complaint is seen by whoever watches the terminal and by nobody else - it never reaches the log file, it carries no timestamp of the application format, no thread id and it obeys no level setting of the application.

The `Gtkmm3i::gtklog::GtkLogBridge` class of the `src/gtkmm3/log` directory takes that over. It's `install` method, called at the very start of the `Gtkmm3i::GtkmmIniter::run` before anything of the toolkit is touched, puts three things in place:

- an own GLib writer, in the place of the default one, which converts every message field set into a call of the application logging macroses;
- a `g_print` handler, which logs the printed text with the info level;
- a `g_printerr` handler, which logs it with the warning level.

The GLib levels are mapped this way:

| GLib level | Application level |
| --- | --- |
| `G_LOG_LEVEL_ERROR` | error |
| `G_LOG_LEVEL_CRITICAL` | error |
| `G_LOG_LEVEL_WARNING` | warning |
| `G_LOG_LEVEL_MESSAGE` | info |
| `G_LOG_LEVEL_INFO` | info |
| `G_LOG_LEVEL_DEBUG` | debug |
| anything else | info |

The GLib error and critical levels both stand for a broken invariant, which is why both of them are errors here. A library is free to declare levels of it's own above the GLib ones and those carry no severity the application knows about, so they are logged and never dropped.

The GTK is built with the structured logging, so it's messages name the toolkit source file, line and function they came from, and the log line carries all three of them. The GLib itself reports most of it's own troubles through the older path, which carries no such fields, and then the domain alone stands at the front of the message:

```
... DBG ... GtkLogBridge.cpp:157 : Gtk: gtkiconpaintable.c:365: gtk_icon_paintable_snapshot_with_weight: snapshot symbolic icon as recolored node
... DBG ... GtkLogBridge.cpp:157 : GLib-GIO: _g_io_module_get_default: Found default implementation local (GLocalVfs) for ‘gio-vfs’
... WRN ... GtkLogBridge.cpp:154 : Gtk: gtkmain.c:738: gtk_init: Failed to open display
```

The bridge logs through the `LOG*` macroses and not through a logger class directly, so it keeps working on the branches which replace the whole logging implementation (`appLog4Cpp5`, `appBoostLog`). The price of it is the source coordinates of a log line: they name the `GtkLogBridge.cpp` file itself, while the toolkit ones stand inside the message text.

### What is reported at all

Two gates stand in front of the log file and the bridge keeps both of them.

The first one is the toolkit own: the info and the debug messages are reported only while their domain is switched on through the `G_MESSAGES_DEBUG` environment variable, exactly the way the default GLib writer decides it:

```bash
G_MESSAGES_DEBUG=all ./YourApplication
```

Without that variable the warnings, the criticals and the errors still reach the log - only the chatter of the toolkit internals stays out of it. That is the behaviour every GTK application has, and replacing the writer must not change it.

The second gate is the `MAX_LOG_LEVEL` of the build, the very one the application own messages obey. A build which names the info level as it's highest (the default `-DMAX_LOG_LEVEL=3`) drops the toolkit debug messages whatever the `G_MESSAGES_DEBUG` variable says, and it does not even assemble their text.

### The one writer per process rule

The GLib accepts a log writer only once in the life of a process and kills the process on a second `g_log_set_writer_func` call, which is why the bridge installs itself once and ignores every further call. Keep that single slot for it: since the writer is a process wide one, it catches the GLib messages of every library of the binary anyway, the GStreamer and the WebKitGTK ones included.
