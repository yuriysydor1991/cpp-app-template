## Вмикання підтримки генерації RPM-пакету

Для того щоб увімкнути ціль генерації Fedora/RHEL/openSUSE `.rpm`-пакету для шаблонного проекту необхідно встановити значення `true` для Meson-опції `ENABLE_RPM`:

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_RPM=true \
  -DPROJECT_MAINTAINER='Імʼя Прізвище' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
```

Яка у свою чергу вмикає Meson-ціль `rpm` (`custom_target`) що під капотом виконує `meson install` у staging-директорію `BUILDROOT` і викликає `rpmbuild -bb` на згенерованому `.spec`-файлі.

Для генерації RPM-пакету необхідно побудувати ціль `rpm`:

```
# всередині кореневої директорії проекту

meson compile -C build rpm
```

Артефакт іменується за шаблоном `<проект>-<версія>-1.<арх>.rpm` і потрапляє у директорію побудови. Опції `PROJECT_MAINTAINER` і `PROJECT_MAINTAINER_EMAIL` потрапляють у поле `Packager:` `.spec`-файлу. Деталі і параметри цілі можна переглянути або змінити у файлах `meson/template-project-rpm-enabler/meson.build` чи у шаблоні `misc/rpm.spec.in`.

Деталі встановлення `rpmbuild`: [Необов'язкові пакети для пакувальника rpm](/doc/sections/uk_UA/3-14-optional-for-the-rpm-packager.md).
