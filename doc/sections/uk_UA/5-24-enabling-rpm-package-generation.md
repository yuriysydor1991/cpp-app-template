## Вмикання підтримки генерації RPM-пакету

Для того щоб увімкнути ціль генерації Fedora/RHEL/openSUSE `.rpm`-пакету для шаблонного проекту необхідно встановити значення `true` для Meson-опції `ENABLE_RPM`:

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_RPM=true \
  -DPROJECT_MAINTAINER='Імʼя Прізвище' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
```

Яка у свою чергу вмикає Meson-ціль `rpm` (`custom_target`) що під капотом виконує `meson install` у staging-директорію і викликає `rpmbuild -bb` на згенерованому `.spec`-файлі. `.spec`-файл копіює підготовлене дерево у свій buildroot і пакує перелік файлів, складений з того дерева, тож пакет слідує налаштованому `--prefix` (типовому `/usr/local` або `/usr` для пакету у стилі дистрибутиву, налаштованого параметром `--prefix=/usr`).

Для генерації RPM-пакету необхідно побудувати ціль `rpm`:

```
# всередині кореневої директорії проекту

meson compile -C build rpm
```

Артефакт іменується за шаблоном `<проект>-<версія>-<арх>-<ОС>.rpm` і потрапляє у директорію побудови, де `<ОС>` - цільова ОС, яку містить опція `PACKAGE_OS` (типово: поля `ID` і `VERSION_ID` файлу `/etc/os-release` хоста збирання, наприклад `fedora-44`). Опції `PROJECT_MAINTAINER` і `PROJECT_MAINTAINER_EMAIL` потрапляють у поле `Packager:` `.spec`-файлу. Деталі і параметри цілі можна переглянути або змінити у файлах `meson/template-project-rpm-enabler/meson.build` чи у шаблоні `misc/rpm.spec.in`.

Деталі встановлення `rpmbuild`: [Необов'язкові пакети для пакувальника rpm](/doc/sections/uk_UA/3-14-optional-for-the-rpm-packager.md).
