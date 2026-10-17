## Обов'язкові пакети PLplot

Для того щоб зробити бібліотеку PLplot доступною у системі, необхідно виконати команди котрі можуть виглядати як наступні:

```
sudo apt install -y libplplot-dev
```

Приклад графіка показує інтерактивний пристрій PLplot: `qtwidget` з пакунка `plplot-driver-qt` або, за його відсутності, `xcairo` з пакунка `plplot-driver-cairo` чи `xwin` з пакунка `plplot-driver-xwin`. Пакунок бібліотеки не містить драйверів пристроїв, тож встановіть і один з них, інакше виконуваний файл повідомить про відсутній драйвер і завершиться зі статусом помилки:

```
sudo apt install -y plplot-driver-qt
```

Або ж скомпілювати бібліотеку з вихідного джерельного коду наступним чином:

```
# клонування проекту у поточну директорію
git clone https://git.code.sf.net/p/plplot/plplot plplot

# перехід до коміту, який закріплює проект (змінна TEMPLATE_APP_PLPLOT_GIT_TAG)
git -C plplot checkout df0c00e11f2c289bb186e20b44651aa0184beb8b

# конфігурування проекту за допомогою CMake (діалект gnu17 дозволяє сучасним
# компіляторам мови C зібрати перевірки конфігурації PLplot, написані до
# стандарту C23)
cmake -B plplot-build -S plplot -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DENABLE_fortran=OFF -DCMAKE_C_FLAGS=-std=gnu17

# побудова усіх цілей проекту, разом з драйверами пристроїв, чиї пакунки
# розробника знайдено (наприклад libx11-dev для пристрою xwin)
cmake --build plplot-build -j$(nproc)

# встановлення у систему
sudo cmake --install plplot-build --prefix /usr
```
