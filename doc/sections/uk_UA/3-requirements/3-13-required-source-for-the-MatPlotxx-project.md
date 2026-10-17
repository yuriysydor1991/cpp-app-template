## Необхідні пакунки для проекту MatPlot++

Для того щоб використовувати бібліотеку MatPlot++ з програмою gnuplot у якості бекенду, необхідно встановити gnuplot командою подібною на наступну:

```
sudo apt install -y gnuplot
```

Тепер можна перейти до клонування і побудови з вихідного джерельного коду самого проекту MatPlot++ за допомогою команд подібних на наступні:

```
# клонування проекту MatPlot++ у локальну директорію
git clone --branch v1.2.2 https://github.com/alandefreitas/matplotplusplus.git

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

Параметр CMake `ENABLE_MATPLOTCXX` (типово `ON`) змушує крок конфігурації використати встановлену в системі бібліотеку Matplot++ або самостійно завантажити і зібрати випуск `TEMPLATE_APP_MATPLOTCXX_GIT_TAG` (`v1.2.2`). Оскільки приклад `src/matplotxx` потребує бібліотеки, значення `OFF` зупиняє конфігурацію з поясненням, доки з файлу `src/CMakeLists.txt` не буде вилучено виклик `add_subdirectory(matplotxx)` разом з підкаталогом `src/matplotxx` і прикладом Matplot++ у файлі `src/app/applications/Application.cpp`.
