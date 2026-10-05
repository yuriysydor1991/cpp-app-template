## Обов'язкові інструменти для ОС на базі GNU/Лінукс

Для того щоб виконати побудову проекту-шаблону необхідно встановити компілятор GCC C++ разом з системою побудови проекту CMake і системою версіювання Git:

```
sudo apt install -y git g++ cmake
```

Гілка `appV8` додатково потребує заголовків і бібліотеки рушія JavaScript [V8](https://v8.dev/), які дистрибутиви на базі Debian постачають у складі пакету розробки спільної бібліотеки [Node.js](https://nodejs.org/):

```
sudo apt install -y libnode-dev
```

Скрипт `scripts/packages/install-ubuntu.sh` (або `scripts/packages/install-debian.sh`) встановлює його разом з рештою необхідних пакетів. Завантаження V8 з мережі не передбачене, оскільки він збирається лише власним набором інструментів Google, тому деталі власної збірки V8 шукай у розділі [Вмикання рушія JavaScript V8](/doc/sections/uk_UA/5-project-build/scripting/5-57-enabling-the-V8-JavaScript-engine.md).
