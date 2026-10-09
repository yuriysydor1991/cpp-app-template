## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appGettext` додатково потребує інструментів [GNU gettext](https://www.gnu.org/software/gettext/), які компілюють переклади, тоді як бібліотека libintl, якою їх читають, є частиною бібліотеки GNU C:

```
sudo apt install -y gettext
```

Скрипт `scripts/packages/install-ubuntu.sh` (або `scripts/packages/install-debian.sh`) встановлює його разом з рештою необхідних пакетів. На дистрибутивах на базі RPM відповідний пакет називається `gettext`, а на FreeBSD це `devel/gettext-runtime` і `devel/gettext-tools` з `pkg`. Переклади з'являються лише під встановленою локаллю, дивись розділ [Вмикання перекладів GNU gettext](/doc/sections/uk_UA/5-project-build/i18n/5-62-enabling-the-gettext-translations.md).
