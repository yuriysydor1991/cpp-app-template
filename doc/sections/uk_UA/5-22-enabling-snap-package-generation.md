## Вмикання підтримки генерації snap-пакету

Для того щоб увімкнути ціль генерації [snap](https://snapcraft.io/)-пакету для шаблонного проекту необхідно встановити значення `true` для Meson-опції `ENABLE_SNAP`:

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_SNAP=true
```

Яка у свою чергу вмикає Meson-ціль `snap` (`custom_target`) що під капотом використовує програму командного рядка `snapcraft`.

Для генерації snap-пакету необхідно побудувати ціль `snap`:

```
# всередині кореневої директорії проекту

meson compile -C build snap
```

Артефакт іменується за шаблоном `<проект>_<версія>_<арх>.snap` і потрапляє у директорію побудови. Деталі і параметри цілі можна переглянути або змінити у файлах `meson/template-project-snap-enabler/meson.build` чи у шаблоні `misc/snap/snapcraft.yaml.meson.in`.

Деталі встановлення `snapcraft`: [Необов'язкові пакети для пакувальника snap](/doc/sections/uk_UA/3-13-optional-for-the-snap-packager.md).
