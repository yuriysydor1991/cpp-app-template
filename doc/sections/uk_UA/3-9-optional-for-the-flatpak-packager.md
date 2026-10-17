## Необов'язковий програми для генерації пакету flatpak

Для того щоб мати змогу генерувати пакет flatpak з ресурсів проекту необхідно встановити інструменти `flatpak` і `flatpak-builder`:

```
sudo apt install -y flatpak flatpak-builder
```

Також знадобиться один з цільових SDK який може бути встановленим за допомогою команди подібної на наступну:

```
flatpak install --user flathub runtime/org.freedesktop.Platform/x86_64/24.08 runtime/org.freedesktop.Sdk/x86_64/24.08
```

Версія `24.08` - це `runtime-version`, з якою будується маніфест [misc/flatpak.conf.json.meson.in](/misc/flatpak.conf.json.meson.in): змінюй їх разом, щоб використати інше середовище. У документації до flatpak можна визначити як переглянути усі доступні варіанти.

Ціль `flatpak` самостійно встановлює необхідні їй середовище і SDK з віддаленого сховища `flathub`, тож наведена команда лише виконує їх попереднє встановлення.

Деталі у секції [Вмикання підтримки генерації flatpak пакету](/doc/sections/uk_UA/5-11-enabling-the-flatpak-package-generation-support.md).
