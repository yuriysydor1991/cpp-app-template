## Вмикання підтримки генерації AppImage-збірки

Для того щоб увімкнути ціль генерації переносної [AppImage](https://appimage.org/)-збірки для шаблонного проекту необхідно встановити значення `true` для Meson-опції `ENABLE_APPIMAGE`:

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_APPIMAGE=true
```

Яка у свою чергу вмикає Meson-ціль `AppImage` (`custom_target`). Вона виконує `meson install` у staging-дерево `AppDir`, копіює згенеровані файли `AppRun`-запускача і `*.desktop` у відповідні місця, і формує переносну збірку.

Для генерації AppImage-збірки необхідно побудувати ціль `AppImage`:

```
# всередині кореневої директорії проекту

meson compile -C build AppImage
```

Артефакт іменується за шаблоном `<проект>-<версія>-<арх>.AppImage` і потрапляє у директорію побудови. Деталі і параметри цілі можна переглянути або змінити у файлах `meson/template-project-AppImage-enabler/meson.build`, `misc/AppRun.meson.in` або у шаблоні `misc/template-project.desktop.meson.in`.

Дана ціль не вимагає окремого AppImage-інструментарію - збірка формується вбудованою у систему командою `tar`.
