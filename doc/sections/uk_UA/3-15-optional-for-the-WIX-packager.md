## Необов'язкові пакети для пакувальника WIX

Для того щоб генерувати MSI-інсталятор проекту необхідно встановити [WiX Toolset](https://wixtoolset.org/) (тільки на MS Windows-хостах). До набору входять програми командного рядка `candle.exe` і `light.exe`, які викликає Meson-ціль `wix`.

Рекомендований спосіб встановлення на MS Windows - через глобальний `dotnet`-інструмент:

```
# у командному рядку Windows або PowerShell
dotnet tool install --global wix
```

Як альтернатива - встановлення WiX Toolset v3 через MSI-інсталятор зі сторінки [випусків WiX Toolset](https://github.com/wixtoolset/wix3/releases). Переконайся, що виконувані файли `candle.exe` і `light.exe` доступні у системній змінній `PATH`, щоб Meson зміг знайти їх через `find_program`.

Деталі у секції [Вмикання підтримки генерації WIX MSI-інсталятора](/doc/sections/uk_UA/5-27-enabling-the-WIX-MSI-installer-generation.md).
