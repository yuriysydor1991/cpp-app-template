## Вмикання підтримки генерації FreeBSD pkg-пакету

Для того щоб увімкнути ціль генерації FreeBSD `.pkg`-пакету для шаблонного проекту необхідно встановити значення `true` для Meson-опції `ENABLE_FREEBSD_PKG` (тільки для FreeBSD):

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_FREEBSD_PKG=true \
  -DPROJECT_MAINTAINER='Імʼя Прізвище' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
```

Яка у свою чергу вмикає Meson-ціль `freebsd-pkg` (`custom_target`) що під капотом виконує `meson install` у staging-директорію і викликає системний `pkg create -M <маніфест>`.

Для генерації FreeBSD pkg-пакету необхідно побудувати ціль `freebsd-pkg`:

```
# всередині кореневої директорії проекту

meson compile -C build freebsd-pkg
```

Артефакт іменується за шаблоном `<проект>-<версія>.pkg` і потрапляє у директорію побудови. Опції `PROJECT_MAINTAINER` і `PROJECT_MAINTAINER_EMAIL` потрапляють у поле `maintainer:` файлу `+MANIFEST`. Деталі і параметри цілі можна переглянути або змінити у файлах `meson/template-project-freebsd-pkg-enabler/meson.build` чи у шаблоні `misc/freebsd-pkg.manifest.in`.

Інструмент `pkg(8)` входить до базової системи FreeBSD і доступний "з коробки" на FreeBSD-хостах.
