## Необов'язковий програми для генерації пакету flatpak

Для того щоб мати змогу генерувати пакет flatpak з ресурсів проекту необхідно встановити інструменти `flatpak` і `flatpak-builder`:

```
sudo apt install -y flatpak flatpak-builder
```

Також знадобиться один з цільових SDK який може бути встановленим за допомогою команди подібної на наступну:

```
flatpak install runtime/org.kde.Sdk/x86_64/6.8
flatpak install runtime/org.kde.Platform/x86_64/6.8
flatpak install app/io.qt.qtwebengine.BaseApp/x86_64/6.8
```

Середовище `org.kde.Platform` не містить QtWebEngine, тож його для компонента мапи Qt6 надає базова програма `io.qt.qtwebengine.BaseApp`.

Необіхдно замінити `runtime/org.kde.Sdk/x86_64/6.8` і `runtime/org.kde.Platform/x86_64/6.8` власним варіантом обраного SDK. У документації до flatpak можна визначити як переглянути усі доступні варіанти.

Ціль `flatpak` самостійно встановлює необхідні їй середовище і SDK з віддаленого сховища `flathub`, тож наведена команда лише виконує їх попереднє встановлення.

Деталі у секції [Вмикання підтримки генерації flatpak пакету](/doc/sections/uk_UA/5-project-build/packagers/5-11-enabling-the-flatpak-package-generation-support.md).
