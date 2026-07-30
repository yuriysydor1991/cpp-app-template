## Обов'язкові пакети PGPLOT

Проект використовує інтерфейс мови C (заголовковий файл `cpgplot.h` і бібліотеку `cpgplot`) бібліотеки графіків [PGPLOT](https://sites.astro.caltech.edu/~tjp/pgplot/). Для того щоб зробити файли розробки PGPLOT доступними у системі, необхідно виконати команди котрі можуть виглядати як наступні:

```
sudo apt install -y pgplot5-dev
```

Слід мати на увазі, що оригінальна бібліотека PGPLOT розповсюджується під невільною ліцензією, тому вона розміщена у компоненті `multiverse` репозиторіїв Ubuntu (і у компоненті `non-free` репозиторіїв Debian) і може бути взагалі відсутньою у вашому дистрибутиві GNU/Лінукс.

Бібліотека [giza](https://danieljprice.github.io/giza/) надає вільну заміну того самого інтерфейсу PGPLOT/`cpgplot` (на основі cairo) і також приймається CMake перевіркою проекту:

```
sudo apt install -y giza-dev
```

Або ж скомпілювати заміну giza з вихідного джерельного коду наступним чином:

```
# клонування проекту у поточну директорію
git clone https://github.com/danieljprice/giza.git giza

# конфігурування проекту
cd giza && ./configure --prefix=/usr

# побудова усіх цілей проекту
make -j$(nproc)

# встановлення у систему
sudo make install
```

У випадку, коли бібліотека встановлена у нетипову (власну) директорію, необхідно вказати шлях до неї за допомогою змінної `TEMPLATE_APP_PGPLOT_ROOT`:

```
cmake -S . -B build -DTEMPLATE_APP_PGPLOT_ROOT=/your/pgplot/prefix
```

Усю інтеграцію можливо вимкнути за допомогою параметра CMake `-DENABLE_PGPLOT=OFF`, але у такому випадку необхідно також прибрати піддиректорію `src/pgplot` з файлу `src/CMakeLists.txt`, оскільки реалізація класу `pgploti::PGPLOTController` потребує цю бібліотеку.
