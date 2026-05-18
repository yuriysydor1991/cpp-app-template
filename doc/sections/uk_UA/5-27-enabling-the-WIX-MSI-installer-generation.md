## Вмикання підтримки генерації WIX MSI-інсталятора

Для того щоб увімкнути ціль генерації Windows `.msi`-інсталятора для шаблонного проекту необхідно встановити значення `true` для Meson-опції `ENABLE_WIX` (тільки для MS Windows хостів):

```
# всередині кореневої директорії проекту

meson setup build -DENABLE_WIX=true \
  -DPROJECT_MAINTAINER='Імʼя Прізвище'
```

Яка у свою чергу вмикає Meson-ціль `wix` (`custom_target`) що використовує програми командного рядка [WiX Toolset](https://wixtoolset.org/) `candle.exe` і `light.exe`. На не-Windows хості `.wxs`-файл буде сконфігуровано у директорію побудови, але саму генерацію MSI буде пропущено.

Для генерації MSI-інсталятора необхідно побудувати ціль `wix`:

```
# всередині кореневої директорії проекту

meson compile -C build wix
```

Артефакт іменується за шаблоном `<проект>-<версія>-win-<арх>.msi` і потрапляє у директорію побудови. Опція `PROJECT_MAINTAINER` потрапляє у поле `Manufacturer` WiX-джерела. Деталі і параметри цілі можна переглянути або змінити у файлах `meson/template-project-wix-enabler/meson.build` чи у шаблоні `misc/wix.wxs.in`.

Деталі встановлення WiX Toolset: [Необов'язкові пакети для пакувальника WIX](/doc/sections/uk_UA/3-15-optional-for-the-WIX-packager.md).
