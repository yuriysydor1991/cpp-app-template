## Необов'язковий програми для генерації пакету flatpak

Для того щоб мати змогу генерувати пакет flatpak з ресурсів проекту необхідно встановити інструменти `flatpak` і `flatpak-builder`:

```
sudo apt install -y flatpak flatpak-builder
```

Також знадобиться один з цільових SDK який може бути встановленим за допомогою команди подібної на наступну:

```
flatpak install org.freedesktop.Sdk/x86_64/24.08 org.freedesktop.Platform/x86_64/24.08
```

Необіхдно замінити `org.freedesktop.Sdk/x86_64/24.08 org.freedesktop.Platform/x86_64/24.08` власним варіантом обраного середовища і SDK. У документації до flatpak можна визначити як переглянути усі доступні варіанти.

Деталі у секції [Вмикання підтримки генерації flatpak пакету](/doc/sections/uk_UA/5-11-enabling-the-flatpak-package-generation-support.md).
