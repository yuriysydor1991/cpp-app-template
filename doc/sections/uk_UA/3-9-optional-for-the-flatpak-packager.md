## Необов'язковий програми для генерації пакету flatpak

Для того щоб мати змогу генерувати пакет flatpak з ресурсів проекту необхідно встановити інструменти `flatpak` і `flatpak-builder`:

```
sudo apt install -y flatpak flatpak-builder
```

Також знадобиться один з цільових SDK який може бути встановленим за допомогою команди подібної на наступну:

```
flatpak install runtime/org.kde.Sdk/x86_64/6.8
flatpak install runtime/org.kde.Platform/x86_64/6.8
```

Необіхдно замінити `runtime/org.kde.Sdk/x86_64/6.8` і `runtime/org.kde.Platform/x86_64/6.8` власним варіантом обраного SDK. У документації до flatpak можна визначити як переглянути усі доступні варіанти.

Деталі у секції [Вмикання підтримки генерації flatpak пакету](/doc/sections/uk_UA/5-11-enabling-the-flatpak-package-generation-support.md).
