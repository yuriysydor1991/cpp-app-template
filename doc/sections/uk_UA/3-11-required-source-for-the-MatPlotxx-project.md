## Необхідні пакенки для проекту MatPlot++

Для того щоб використовувати бібліотеку MatPlot++ з програмою gnuplot у якості бекенду, необхідно встановити gnuplot командою подібною на насутпну:

```
sudo apt install -y gnuplot
```

Тепер можна перейти до клонування і побудови з вихідного джерельного коду самого проекту MatPlot++ за допомогою команд подібних на наступні:

```
# клонування проекту MatPlot++ у локальну директорію
git clone https://github.com/alandefreitas/matplotplusplus.git

# конфігурування проекту
cmake -B matplotplusplus-build -S matplotplusplus \
    -DMATPLOTPP_BUILD_EXAMPLES=OFF \
    -DMATPLOTPP_BUILD_SHARED_LIBS=ON \
    -DMATPLOTPP_BUILD_TESTS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON \
    -DCMAKE_INSTALL_PREFIX=/usr

# побудова проекту за допомогою усіх наявних процесорів у системі
cmake --build matplotplusplus-build -j$(nproc)

# встановлення бібліотеки MatPlot++ у систему
sudo cmake --install matplotplusplus-build --prefix /usr
```
