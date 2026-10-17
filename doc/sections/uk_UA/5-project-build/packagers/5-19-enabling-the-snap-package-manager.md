## Вмикання пакувальника snap

Для того щоб увімкнути для побудови ціль `snap`, що призначена для генерування [SNAP](https://snapcraft.io/docs/) бінарного дистрибуційного пакунку проекту, необхідно сконфігурувати CMake проект з увімкненою змінною `ENABLE_SNAP`:

```
cmake -S . -B build -DENABLE_SNAP=ON
```

Детальніше у файлі [cmake/enablers/packagers/template-project-snap-enabler.cmake](/cmake/enablers/packagers/template-project-snap-enabler.cmake) про ціль `snap`.

Пакунок snap зчитує властивості hostname1 на системній шині через інтерфейс `system-observe`, який не під'єднується автоматично, тому після встановлення його необхідно один раз під'єднати:

```
sudo snap connect <назва пакунку>:system-observe
```
