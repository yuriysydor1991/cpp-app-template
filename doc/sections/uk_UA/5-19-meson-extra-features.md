## Додаткові можливості Meson

Гілка `libMeson` пропонує Meson-еквівалент набору можливостей CMake з гілки `lib`. Кожна функція вмикається відповідним прапорцем у `meson_options.txt` під час конфігурування: `meson setup -D<OPTION>=true`. Інтеграція виконується через Meson-змінні `template_project_extra_deps`, `template_project_extra_cpp_args` і `template_project_extra_link_args`, до яких кожен модуль `meson/template-project-<feature>-*/meson.build` додає своє значення.

Матриця нижче ставить у відповідність кожній опції її окрему підсекцію, щоб команди, підказки по встановленню і деталі цілей знаходились поруч з функцією, яку вони вмикають.

### Опціональні сторонні бібліотеки

| Опція | Підсекція |
|---|---|
| `-DENABLE_LIBCURL=true` | [Вмикання інтеграції libcurl](/doc/sections/uk_UA/5-14-enabling-libcurl.md) |
| `-DENABLE_LIBXML2=true` | [Вмикання інтеграції libxml2](/doc/sections/uk_UA/5-20-enabling-libxml2.md) |
| `-DENABLE_NLOHMANN_JSON=true` | [Вмикання інтеграції бібліотеки nlohmann JSON](/doc/sections/uk_UA/5-18-enabling-the-nlohmann-json-library.md) |
| `-DENABLE_OPENCV=true` | [Вмикання інтеграції OpenCV](/doc/sections/uk_UA/5-21-enabling-OpenCV.md) |

### Аналізатори

| Опція | Підсекція |
|---|---|
| `-DENABLE_CPPCHECK=true` | [Вмикання підтримки цілі статичного аналізатора коду cppcheck](/doc/sections/uk_UA/5-7-enabling-the-static-code-analyzer-target-with-cppcheck.md) |
| `-DENABLE_CLANGFORMAT=true` | [Вмикання підтримки форматування коду](/doc/sections/uk_UA/5-6-enabling-and-performing-code-formatting-target.md) |
| `-DENABLE_CLANG_TIDY=true` | [Вмикання підтримки статичного аналізатора коду clang-tidy](/doc/sections/uk_UA/5-8-enabling-static-code-analyzer-with-clang-tidy.md) |

### Sanitizers

| Опція | Підсекція |
|---|---|
| `-DENABLE_SANITIZERS=true` | [Вмикання перевірок під час виконання програми (sanitizers)](/doc/sections/uk_UA/5-13-enabling-sanitizers.md) |
| `-DENABLE_SANITIZERS_THREADS=true` | [Вмикання перевірок під час виконання програми (sanitizers)](/doc/sections/uk_UA/5-13-enabling-sanitizers.md) |

### Тести

| Опція | Підсекція |
|---|---|
| `-DENABLE_UNIT_TESTS=true` | [Вмикання юніт-тестів](/doc/sections/uk_UA/5-3-1-enabling-unit-testing.md) |
| `-DENABLE_COMPONENT_TESTS=true` | [Вмикання компонентних тестів](/doc/sections/uk_UA/5-3-3-enabling-component-testing.md) |

### Пакувальники

Кожен пакувальник це `custom_target`, який всередині виконує `meson install` у staging-директорію і викликає відповідний нативний інструмент пакування.

| Опція | Артефакт | Підсекція |
|---|---|---|
| `-DENABLE_DEB=true` | `<проект>-<версія>_<арх>.deb` | [Вмикання підтримки генерації DEB-пакету](/doc/sections/uk_UA/5-23-enabling-deb-package-generation.md) |
| `-DENABLE_RPM=true` | `<проект>-<версія>-1.<арх>.rpm` | [Вмикання підтримки генерації RPM-пакету](/doc/sections/uk_UA/5-24-enabling-rpm-package-generation.md) |
| `-DENABLE_FREEBSD_PKG=true` | `<проект>-<версія>.pkg` | [Вмикання підтримки генерації FreeBSD pkg-пакету](/doc/sections/uk_UA/5-25-enabling-freebsd-pkg-package-generation.md) |
| `-DENABLE_WIX=true` | `<проект>-<версія>-win-<арх>.msi` | [Вмикання підтримки генерації WIX MSI-інсталятора](/doc/sections/uk_UA/5-27-enabling-the-WIX-MSI-installer-generation.md) |

Пакувальники DEB / RPM / FreeBSD pkg / WIX поділяють спільні опції `PROJECT_MAINTAINER` / `PROJECT_MAINTAINER_EMAIL` - див. [Опції супровідника проекту](/doc/sections/uk_UA/5-28-project-maintainer-options.md).

### Логування

| Опція | За замовчуванням | Ефект |
|---|---|---|
| `-DMAX_LOG_LEVEL=N` | `3` (info) | Максимальний рівень повідомлень логу (`0` error - `5` trace) |
| `-DENABLE_LOGS_MICROSECONDS_TIME=true` | `true` | Додавати поле мікросекунд у повідомлення логу |
| `-DDEFAULT_LOG_FILE_PATH=...` | `""` | Директорія за замовчуванням для лог-файлу (порожньо - поточна директорія) |

### Doxygen

| Опція | Підсекція |
|---|---|
| `-DENABLE_DOC_DOXYGEN=true` | [Побудова документації](/doc/sections/uk_UA/5-4-documentation-build.md) |
| `-DDOXYGEN_DO_INSTALL=true` | [Вмикання підтримки встановлення документації](/doc/sections/uk_UA/5-5-configuring-the-documentation-install-support.md) |
