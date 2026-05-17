## Додаткові можливості Meson

Гілка `appMeson` пропонує Meson-еквівалент набору можливостей CMake з гілки `app`. Кожна функція вмикається відповідним прапорцем у `meson_options.txt` під час конфігурування: `meson setup -D<OPTION>=true`.

### Опціональні сторонні бібліотеки

Усі чотири бібліотеки шукаються через `dependency()` (спочатку pkg-config, потім CMake-конфіг). За замовчуванням вимкнені - вмикай, якщо проект справді їх використовує.

| Параметр | Ефект | Системний пакет (Debian/Ubuntu) |
|---|---|---|
| `-DENABLE_LIBCURL=true` | додає `libcurl` до головного бінарника і `applib` | `libcurl4-openssl-dev` |
| `-DENABLE_LIBXML2=true` | додає `libxml-2.0` | `libxml2-dev` |
| `-DENABLE_NLOHMANN_JSON=true` | додає header-only `nlohmann_json` | `nlohmann-json3-dev` |
| `-DENABLE_OPENCV=true` | додає OpenCV (`opencv4`) | `libopencv-dev opencv-data` |

Інтеграція виконується через Meson-змінну `template_project_extra_deps`, до якої кожен модуль `meson/template-project-<lib>-enabler/meson.build` додає свою залежність.

### Аналізатори і динамічні перевірки

| Параметр | Ефект | Необхідна програма |
|---|---|---|
| `-DENABLE_CPPCHECK=true` | додає Meson-ціль `cppcheck` | `cppcheck` |
| `-DENABLE_CLANGFORMAT=true` | додає ціль `clang-format` | `clang-format` |
| `-DENABLE_CLANG_TIDY=true` | додає ціль `clang-tidy`, що використовує `misc/.clang-tidy` | `clang-tidy` |
| `-DENABLE_VALGRIND=true` | додає ціль перевірки памʼяті `valgrind` на головному бінарнику | `valgrind` |

Запуск: `meson compile -C build <ім'я-цілі>` (наприклад `meson compile -C build cppcheck`).

### Sanitizers і профайлери

| Параметр | Ефект |
|---|---|
| `-DENABLE_SANITIZERS=true` | перебудовує бінарник з `-fsanitize=address,leak,undefined` |
| `-DENABLE_SANITIZERS_THREADS=true` | перебудовує бінарник з `-fsanitize=thread` (взаємовиключно з попереднім) |
| `-DENABLE_GPROF=true` | інструментує побудову `-pg -fprofile-generate` і додає ціль `gprof-analyze` |
| `-DENABLE_CALLGRIND=true` | додає ціль `callgrind`, що запускає `valgrind --tool=callgrind` |

Профайлери вимагають `--buildtype=debug`. Sanitizers сумісні з будь-яким типом збирання.

### Тести

| Параметр | Ефект |
|---|---|
| `-DENABLE_UNIT_TESTS=true` | будує `UTEST_*` під `src/app/tests/unit/...` |
| `-DENABLE_COMPONENT_TESTS=true` | будує `CTEST_app` під `src/app/tests/component/` |

Обидва набори підключаються до `meson test -C build`.

### Пакувальники

Кожен пакувальник це `custom_target`, який всередині виконує `meson install` у staging-директорію і викликає відповідний нативний інструмент пакування.

| Параметр | Артефакт | Нативний інструмент |
|---|---|---|
| `-DENABLE_FLATPAK=true` | `<проект>-<версія>.flatpak` | `flatpak-builder`, `flatpak` |
| `-DENABLE_SNAP=true` | `<проект>_<версія>_<арх>.snap` | `snapcraft` |
| `-DENABLE_DEB=true` | `<проект>-<версія>_<арх>.deb` | `dpkg-deb` |
| `-DENABLE_RPM=true` | `<проект>-<версія>-1.<арх>.rpm` | `rpmbuild` |
| `-DENABLE_FREEBSD_PKG=true` | `<проект>-<версія>.pkg` | `pkg(8)` (тільки FreeBSD) |
| `-DENABLE_APPIMAGE=true` | `<проект>-<версія>-<арх>.AppImage` | `meson install` + вбудований `tar` |
| `-DENABLE_WIX=true` | `<проект>-<версія>-win-<арх>.msi` | WiX Toolset (`candle.exe` / `light.exe`) (тільки Windows) |
| `-DENABLE_DOCKER=true` | побудова і запуск контейнера | `docker` |

Метадані пакетів (DEB / RPM / FreeBSD pkg / WIX) налаштовуються через опції `PROJECT_MAINTAINER` і `PROJECT_MAINTAINER_EMAIL`:

```
meson setup build -DENABLE_DEB=true \
  -DPROJECT_MAINTAINER='Your Name' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
meson compile -C build deb
```

Згенерований артефакт зʼявляється у директорії побудови.

### Doxygen

`-DENABLE_DOC_DOXYGEN=true` зберігає попередню поведінку - побудова документації Doxygen у `doc/`. `-DDOXYGEN_DO_INSTALL=true` встановлює згенеровану документацію разом з бінарником.
