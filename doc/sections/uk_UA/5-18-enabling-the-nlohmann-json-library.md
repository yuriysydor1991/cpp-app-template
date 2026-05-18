## Вмикання інтеграції бібліотеки nlohmann JSON

Для того щоб увімкнути підтримку header-only бібліотеки [nlohmann JSON](https://github.com/nlohmann/json) для проекту, використовуючи її встановлену системну версію, необхідно встановити значення `true` для Meson-опції `ENABLE_NLOHMANN_JSON`:

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_NLOHMANN_JSON=true
```

Залежність шукається через `dependency('nlohmann_json', required: true)` (спочатку pkg-config, потім CMake-конфіг). Знайдена залежність додається до змінної `template_project_extra_deps` у файлі `meson/template-project-nlohmann-json-enabler/meson.build` і підключається до головного бінарника і `applib`.

Деталі встановлення системного пакету: [Необов'язкові пакети для інтеграції nlohmann JSON](/doc/sections/uk_UA/3-17-optional-for-the-nlohmann-json-integration.md).
