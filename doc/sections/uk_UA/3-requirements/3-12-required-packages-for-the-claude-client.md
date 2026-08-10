## Необхідні пакети для клієнта Claude

Anthropic не постачає офіційного SDK для C++, тому ця гілка звертається до [Claude API](https://platform.claude.com/docs/en/api/overview) звичайним HTTP за допомогою [libcurl](https://curl.se/libcurl/) і розбирає відповіді бібліотекою [nlohmann JSON](https://github.com/nlohmann/json). Обидві є обовʼязковими і встановлюються у системі командою:

```
sudo apt install -y libcurl4-openssl-dev nlohmann-json3-dev
```

Будь-яка з цих бібліотек завантажується зі свого git-репозиторію під час кроку конфігурування CMake, якщо у системі не знайдено встановленої, тож система без наведених вище пакетів все одно збереться, доки доступна мережа.

Для запуску згенерованого виконуваного файлу необхідний токен [Anthropic API](https://platform.claude.com/docs/en/api/overview). Його можна створити у налаштуваннях облікового запису [Anthropic Console](https://platform.claude.com/settings/keys).

Деталі у секції [Підключення до серверів Claude](/doc/sections/uk_UA/5-project-build/ai/5-37-connecting-to-the-claude-servers.md).
