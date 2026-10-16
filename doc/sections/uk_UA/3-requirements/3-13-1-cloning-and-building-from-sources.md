### Клонування і будування з вихідного джерельного коду

Для того щоб встановити [Wt C++ фреймворк](https://www.webtoolkit.eu/wt) у систему з вихідного джерельного коду, розміщеного у репозиторії [https://github.com/emweb/wt](https://github.com/emweb/wt), необхідно склонувати реліз, з яким перевірено проект, і побудувати його наступними командами:

```
git clone --branch 4.11.4 --depth 1 https://github.com/emweb/wt.git
cmake -S wt -B wt/build -DCMAKE_BUILD_TYPE=Release -DENABLE_LIBWTDBO=OFF -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
cmake --build wt/build -j$(nproc)
sudo cmake --install wt/build
```

Після цього конфігурування проекту знайде встановлений Wt (див. параметр `WT4_TRY_SYSTEM_PROBE`). Файл [Dockerfile.in](/misc/Dockerfiles/Dockerfile.in) будує Wt так само, з повним переліком вимкнених можливостей. Інші параметри побудови описані у файлах README.md та INSTALL фреймворку Wt.
