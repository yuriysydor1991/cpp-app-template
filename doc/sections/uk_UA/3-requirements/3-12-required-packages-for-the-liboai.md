## Необхідні пакети для liboai

Бібліотека [liboai](https://github.com/d7ead/liboai) запитує обидві свої залежності командою CMake `find_package`, тому завантажена з мережі копія будь-якої з них залишається невидимою для неї і обидві мають бути встановлені у системі:

```
sudo apt install -y libcurl4-openssl-dev nlohmann-json3-dev
```

Сама бібліотека завантажується зі свого git-репозиторію під час кроку конфігурування CMake, якщо у системі не знайдено встановленої, тому додаткового пакету для неї не потрібно.

Для запуску згенерованого виконуваного файлу необхідний токен [OpenAI API](https://platform.openai.com/docs/api-reference/chat). Його можна створити у налаштуваннях облікового запису [платформи OpenAI](https://platform.openai.com/api-keys).

Деталі у секції [Вмикання інтеграції бібліотеки liboai](/doc/sections/uk_UA/5-project-build/ai/5-37-enabling-the-liboai-library.md).
