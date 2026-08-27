## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appCFITSIO` додатково шукає системні файли розробки [CFITSIO](https://heasarc.gsfc.nasa.gov/fitsio/) та [WCSLIB](https://www.atnf.csiro.au/people/mcalabre/WCS/) за допомогою `pkg-config`, тому їх варто також встановити:

```
sudo apt install -y pkg-config libcfitsio-dev wcslib-dev
```

На дистрибутивах на базі RPM відповідні пакети називаються `pkgconf-pkg-config`, `cfitsio-devel` і `wcslib-devel`; на FreeBSD це `devel/pkgconf`, `astro/cfitsio` і `astro/wcslib` з `pkg`. Без пакету CFITSIO його вихідні коди натомість завантажуються і збираються з мережі, для чого додатково потрібні файли розробки zlib (`zlib1g-dev`). Пакет WCSLIB є обов'язковим: ця бібліотека постачається лише зі збіркою autotools, тому `FetchContent` не має що збирати.
