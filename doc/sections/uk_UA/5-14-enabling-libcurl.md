## Вмикання інтеграції libcurl

Для того щоб увімкнути підтримку бібліотеки [libcurl](https://curl.se/) для проекту, використовуючи її встановлену системну версію, необхідно встановити значення `true` для Meson-опції `ENABLE_LIBCURL`:

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_LIBCURL=true
```

Залежність шукається через `dependency('libcurl', required: true)` (спочатку pkg-config, потім CMake-конфіг). Знайдена залежність додається до змінної `template_project_extra_deps` у файлі `meson/template-project-libcurl-enabler/meson.build` і підключається до головного бінарника і `applib`.

Деталі встановлення системного пакету: [Необов'язкові пакети для інтеграції libcurl](/doc/sections/uk_UA/3-16-optional-for-the-libcurl-integration.md).
