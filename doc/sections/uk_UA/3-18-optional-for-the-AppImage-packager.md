## Необов'язкові програми для генерації AppImage-збірки

Ціль `AppImage` викликає команду `appimagetool`, яку дистрибутиви GNU/Linux рідко пакують. Її необхідно звантажити зі сторінки [випусків appimagetool](https://github.com/AppImage/appimagetool/releases) і розмістити у одному з каталогів змінної `PATH` під назвою `appimagetool`:

```
# необхідно замінити x86_64 архітектурою цільової системи
curl -L -o appimagetool \
  https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage

chmod +x appimagetool

sudo mv appimagetool /usr/local/bin/
```

Сам `appimagetool` є збіркою [AppImage](https://appimage.org/), тож для його запуску необхідна бібліотека `libfuse`, так само як і для запуску згенерованої збірки:

```
sudo apt install -y libfuse2t64
```

Без цієї бібліотеки і інструмент, і згенеровану збірку все ще можливо запустити з опцією `--appimage-extract-and-run` або зі встановленою змінною середовища `APPIMAGE_EXTRACT_AND_RUN=1`.

Деталі у секції [Вмикання підтримки генерації AppImage-збірки](/doc/sections/uk_UA/5-26-enabling-the-AppImage-bundle-generation.md).
