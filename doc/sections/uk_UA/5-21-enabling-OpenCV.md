## Вмикання інтеграції OpenCV

Для того щоб увімкнути підтримку бібліотеки компʼютерного зору [OpenCV](https://opencv.org/) для проекту, використовуючи її встановлену системну версію, необхідно встановити значення `true` для Meson-опції `ENABLE_OPENCV`:

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_OPENCV=true
```

Залежність шукається через `dependency('opencv4', required: true)` (спочатку pkg-config, потім CMake-конфіг). Знайдена залежність додається до змінної `template_project_extra_deps` у файлі `meson/template-project-OpenCV-enabler/meson.build` і підключається до головного бінарника і `applib`.

Деталі встановлення системного пакету: [Необов'язкові пакети для інтеграції OpenCV](/doc/sections/uk_UA/3-12-optional-for-the-OpenCV-integration.md).
