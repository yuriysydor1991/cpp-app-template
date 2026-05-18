## Додаткові можливості Meson

Гілка `appMeson` пропонує Meson-еквівалент набору можливостей CMake з гілки `app`. Кожна функція вмикається відповідним прапорцем у `meson_options.txt` під час конфігурування: `meson setup -D<OPTION>=true`. Інтеграція виконується через Meson-змінні `template_project_extra_deps`, `template_project_extra_cpp_args` і `template_project_extra_link_args`, до яких кожен модуль `meson/template-project-<feature>-*/meson.build` додає своє значення.

Матриця нижче ставить у відповідність кожній опції її окрему підсекцію, щоб команди, підказки по встановленню і деталі цілей знаходились поруч з функцією, яку вони вмикають.

### Опціональні сторонні бібліотеки

| Опція | Підсекція |
|---|---|
| `-DENABLE_LIBCURL=true` | [Вмикання інтеграції libcurl](/doc/sections/uk_UA/5-14-enabling-libcurl.md) |
| `-DENABLE_LIBXML2=true` | [Вмикання інтеграції libxml2](/doc/sections/uk_UA/5-20-enabling-libxml2.md) |
| `-DENABLE_NLOHMANN_JSON=true` | [Вмикання інтеграції бібліотеки nlohmann JSON](/doc/sections/uk_UA/5-18-enabling-the-nlohmann-json-library.md) |
| `-DENABLE_OPENCV=true` | [Вмикання інтеграції OpenCV](/doc/sections/uk_UA/5-21-enabling-OpenCV.md) |

### Аналізатори і динамічні перевірки

| Опція | Підсекція |
|---|---|
| `-DENABLE_CPPCHECK=true` | [Вмикання підтримки цілі статичного аналізатора коду cppcheck](/doc/sections/uk_UA/5-7-enabling-the-static-code-analyzer-target-with-cppcheck.md) |
| `-DENABLE_CLANGFORMAT=true` | [Вмикання підтримки форматування коду](/doc/sections/uk_UA/5-6-enabling-and-performing-code-formatting-target.md) |
| `-DENABLE_CLANG_TIDY=true` | [Вмикання підтримки статичного аналізатора коду clang-tidy](/doc/sections/uk_UA/5-8-enabling-static-code-analyzer-with-clang-tidy.md) |
| `-DENABLE_VALGRIND=true` | [Вмикання цілі динамічної перевірки пам'яті Valgrind](/doc/sections/uk_UA/5-9-enabling-the-dynamic-memory-check-target-with-valgrind.md) |

### Sanitizers і профайлери

| Опція | Підсекція |
|---|---|
| `-DENABLE_SANITIZERS=true` | [Вмикання перевірок під час виконання програми (sanitizers)](/doc/sections/uk_UA/5-13-enabling-sanitizers.md) |
| `-DENABLE_SANITIZERS_THREADS=true` | [Вмикання перевірок під час виконання програми (sanitizers)](/doc/sections/uk_UA/5-13-enabling-sanitizers.md) |
| `-DENABLE_GPROF=true` | [Вмикання підтримки профілювання з gprof](/doc/sections/uk_UA/5-15-enabling-gprof-profiler-analysis.md) |
| `-DENABLE_CALLGRIND=true` | [Вмикання підтримки профілювання за допомогою vagrind/callgrind](/doc/sections/uk_UA/5-16-enabling-valgrinds-callgrind-profiler-analysis.md) |

### Тести

| Опція | Підсекція |
|---|---|
| `-DENABLE_UNIT_TESTS=true` | [Вмикання юніт-тестів](/doc/sections/uk_UA/5-3-1-enabling-unit-testing.md) |
| `-DENABLE_COMPONENT_TESTS=true` | [Вмикання компонентних тестів](/doc/sections/uk_UA/5-3-3-enabling-component-testing.md) |

### Пакувальники

Кожен пакувальник це `custom_target`, який всередині виконує `meson install` у staging-директорію і викликає відповідний нативний інструмент пакування. Жоден з них не покладається на сторонню обгортку CMake/CPack.

| Опція | Артефакт | Підсекція |
|---|---|---|
| `-DENABLE_FLATPAK=true` | `<проект>-<версія>.flatpak` | [Вмикання підтримки генерації flatpak пакету](/doc/sections/uk_UA/5-11-enabling-the-flatpak-package-generation-support.md) |
| `-DENABLE_SNAP=true` | `<проект>_<версія>_<арх>.snap` | [Вмикання підтримки генерації snap-пакету](/doc/sections/uk_UA/5-22-enabling-snap-package-generation.md) |
| `-DENABLE_DEB=true` | `<проект>-<версія>_<арх>.deb` | [Вмикання підтримки генерації DEB-пакету](/doc/sections/uk_UA/5-23-enabling-deb-package-generation.md) |
| `-DENABLE_RPM=true` | `<проект>-<версія>-1.<арх>.rpm` | [Вмикання підтримки генерації RPM-пакету](/doc/sections/uk_UA/5-24-enabling-rpm-package-generation.md) |
| `-DENABLE_FREEBSD_PKG=true` | `<проект>-<версія>.pkg` | [Вмикання підтримки генерації FreeBSD pkg-пакету](/doc/sections/uk_UA/5-25-enabling-freebsd-pkg-package-generation.md) |
| `-DENABLE_APPIMAGE=true` | `<проект>-<версія>-<арх>.AppImage` | [Вмикання підтримки генерації AppImage-збірки](/doc/sections/uk_UA/5-26-enabling-the-AppImage-bundle-generation.md) |
| `-DENABLE_WIX=true` | `<проект>-<версія>-win-<арх>.msi` | [Вмикання підтримки генерації WIX MSI-інсталятора](/doc/sections/uk_UA/5-27-enabling-the-WIX-MSI-installer-generation.md) |
| `-DENABLE_DOCKER=true` | побудова і запуск контейнера | [Вмикання підтримки запуску Docker-контейнера](/doc/sections/uk_UA/5-12-enabling-the-docker-container-build-and-run.md) |

Пакувальники DEB / RPM / FreeBSD pkg / WIX поділяють спільні опції `PROJECT_MAINTAINER` / `PROJECT_MAINTAINER_EMAIL` - див. [Опції супровідника проекту](/doc/sections/uk_UA/5-28-project-maintainer-options.md).

### Doxygen

| Опція | Підсекція |
|---|---|
| `-DENABLE_DOC_DOXYGEN=true` | [Побудова документації](/doc/sections/uk_UA/5-4-documentation-build.md) |
| `-DDOXYGEN_DO_INSTALL=true` | [Вмикання підтримки встановлення документації](/doc/sections/uk_UA/5-5-configuring-the-documentation-install-support.md) |
