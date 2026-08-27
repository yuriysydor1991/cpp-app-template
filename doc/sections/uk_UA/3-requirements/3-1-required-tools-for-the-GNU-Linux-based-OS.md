## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appCFITSIO` додатково шукає системні файли розробки [CFITSIO](https://heasarc.gsfc.nasa.gov/fitsio/) за допомогою `pkg-config`, тому їх варто також встановити:

```
sudo apt install -y pkg-config libcfitsio-dev
```

На дистрибутивах на базі RPM відповідні пакети називаються `pkgconf-pkg-config` і `cfitsio-devel`; на FreeBSD це `devel/pkgconf` і `astro/cfitsio` з `pkg`. Без них вихідні коди CFITSIO натомість завантажуються і збираються з мережі, для чого додатково потрібні файли розробки zlib (`zlib1g-dev`).
