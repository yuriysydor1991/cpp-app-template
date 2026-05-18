## Вмикання інтеграції libxml2

Для того щоб увімкнути підтримку бібліотеки [libxml2](https://gitlab.gnome.org/GNOME/libxml2) для проекту, використовуючи її встановлену системну версію, необхідно встановити значення `true` для Meson-опції `ENABLE_LIBXML2`:

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_LIBXML2=true
```

Залежність шукається через `dependency('libxml-2.0', required: true)` (спочатку pkg-config, потім CMake-конфіг). Знайдена залежність додається до змінної `template_project_extra_deps` у файлі `meson/template-project-libxml2-enabler/meson.build` і підключається до головного бінарника і `applib`.

Деталі встановлення системного пакету: [Необов'язкові пакети для інтеграції libxml2](/doc/sections/uk_UA/3-11-optional-for-the-libxml2-integration.md).
