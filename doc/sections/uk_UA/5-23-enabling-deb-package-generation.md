## Вмикання підтримки генерації DEB-пакету

Для того щоб увімкнути ціль генерації Debian/Ubuntu `.deb`-пакету для шаблонного проекту необхідно встановити значення `true` для Meson-опції `ENABLE_DEB`:

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_DEB=true \
  -DPROJECT_MAINTAINER='Імʼя Прізвище' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
```

Яка у свою чергу вмикає Meson-ціль `deb` (`custom_target`) що під капотом виконує `meson install` у staging-директорію і викликає `dpkg-deb --build` на ній.

Для генерації DEB-пакету необхідно побудувати ціль `deb`:

```
# всередині кореневої директорії проекту

meson compile -C build deb
```

Артефакт іменується за шаблоном `<проект>-<версія>_<арх>.deb` і потрапляє у директорію побудови. Опції `PROJECT_MAINTAINER` і `PROJECT_MAINTAINER_EMAIL` потрапляють у поле `Maintainer:` маніфесту `DEBIAN/control`. Деталі і параметри цілі можна переглянути або змінити у файлах `meson/template-project-deb-enabler/meson.build` чи у шаблоні `misc/deb-control.in`.

Інструмент `dpkg-deb` входить до системного пакету `dpkg`, який передвстановлено на Debian/Ubuntu системах.
