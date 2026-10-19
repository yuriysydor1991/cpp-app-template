## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appLlamaCPP` додатково потребує git і доступу до мережі Інтернет, оскільки конфігурування завантажує і збирає бібліотеку [llama.cpp](https://github.com/ggml-org/llama.cpp), якщо система не пакує достатньо нової, і завантажує мовну модель розміром у кілька гігабайтів. Скрипт `scripts/packages/install-ubuntu.sh` (або `scripts/packages/install-debian.sh`) збирає і встановлює llama.cpp `v0.7.0` з вихідних кодів в Ubuntu 24.04 і Debian 13, які її не пакують, тоді як в Ubuntu 26.04 конфігурування завантажує власну, оскільки пакет `libllama-dev` цього випуску застарий для моделей Gemma 4. Debian forky пакує достатньо нову llama.cpp як `libllama-dev`, а FreeBSD - як `misc/llama-cpp`, тоді як пакет `llama-cpp-devel` у Fedora застарий, тож там конфігурування завантажує llama.cpp. Моделі та потрібну їм оперативну пам'ять описує розділ [Вмикання мовних моделей llama.cpp](/doc/sections/uk_UA/5-project-build/ai/5-73-enabling-the-llama-cpp-language-models.md).

Каталог [scripts/packages](/scripts/packages) містить скрипти, які встановлюють усі необхідні проекту пакунки за один раз. Скрипти [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) та [install-debian.sh](/scripts/packages/install-debian.sh) запускають скрипт поточного випуску системи - [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) чи [install-debian-13.sh](/scripts/packages/install-debian-13.sh) - оскільки кожен випуск по-своєму називає та версіонує свої пакунки, а на будь-якому іншому випуску завершуються з помилкою та переліком підтримуваних випусків. Залежність, придатної версії якої випуск не пакує, його скрипт будує з вихідних кодів закріпленого тегу її випуску. Скрипт [install-redhat.sh](/scripts/packages/install-redhat.sh) охоплює Fedora, RHEL та його перезбірки, а скрипт [install-freebsd.sh](/scripts/packages/install-freebsd.sh) - FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
