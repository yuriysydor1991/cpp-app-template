## Обов'язкові пакети PLplot

Для того щоб зробити бібліотеку PLplot доступною у системі, необхідно виконати команди котрі можуть виглядати як наступні:

```
sudo apt install -y libplplot-dev
```

Або ж скомпілювати бібліотеку з вихідного джерельного коду наступним чином:

```
# клонування проекту у поточну директорію
git clone https://git.code.sf.net/p/plplot/plplot plplot

# конфігурування проекту за допомогою CMake
cmake -B plplot-build -S plplot -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DENABLE_fortran=OFF

# побудова усіх цілей проекту
cmake --build plplot-build -j$(nproc)

# встановлення у систему
sudo cmake --install plplot-build --prefix /usr
```
