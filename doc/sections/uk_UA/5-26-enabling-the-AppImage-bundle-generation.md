## Вмикання підтримки генерації AppImage-збірки

Для того щоб увімкнути ціль генерації переносної [AppImage](https://appimage.org/)-збірки для шаблонного проекту необхідно встановити значення `true` для Meson-опції `ENABLE_APPIMAGE`:

```
# всередині кореневої директорії проекту

meson setup build --prefix=/usr -DENABLE_APPIMAGE=true
```

Яка у свою чергу вмикає Meson-ціль `AppImage` (`custom_target`). Вона виконує `meson install` у staging-дерево `AppDir`, копіює згенеровані `AppRun`-запускач, файл `*.desktop` і вказану ним піктограму у корінь `AppDir` і пакує це дерево у переносну збірку програмою `appimagetool`. Параметр `--prefix=/usr` надає збірці стандартну структуру `AppDir/usr/bin` (запускач `AppRun` знаходить виконуваний файл і з типовим префіксом `/usr/local`).

Для генерації AppImage-збірки необхідно побудувати ціль `AppImage`:

```
# всередині кореневої директорії проекту

meson compile -C build AppImage
```

Артефакт іменується за шаблоном `<проект>-<версія>-<арх>-<ОС>.AppImage` і потрапляє у директорію побудови, де `<ОС>` - цільова ОС, яку містить опція `PACKAGE_OS` (типово: поля `ID` і `VERSION_ID` файлу `/etc/os-release` хоста збирання, наприклад `ubuntu-24.04`). Деталі і параметри цілі можна переглянути або змінити у файлах `meson/enablers/packagers/template-project-AppImage-enabler/meson.build`, `misc/AppRun.meson.in` або у шаблонах `misc/template-project.desktop.meson.in` і `misc/template-project.icon.svg.meson.in`.

Згенерована збірка запускається як будь-який інший виконуваний файл (наприклад, `./build/CppAppTemplate-0.11.0-x86_64-ubuntu-24.04.AppImage --version`). Скрипт `scripts/build/build-appimage.sh` виконує всю послідовність конфігурування і побудови, а його прапорець `--install` копіює збірку у директорію `${HOME}/.local/bin`.

Команди встановлення `appimagetool`: [Необов'язкові програми для генерації AppImage-збірки](/doc/sections/uk_UA/3-18-optional-for-the-AppImage-packager.md).
