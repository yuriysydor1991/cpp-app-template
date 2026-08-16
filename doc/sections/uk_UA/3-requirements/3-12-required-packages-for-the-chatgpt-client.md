## Необхідні пакети для клієнта ChatGPT

OpenAI не постачає офіційного SDK для C++, тому ця гілка звертається до [OpenAI API](https://developers.openai.com/api/docs) звичайним HTTP за допомогою [libcurl](https://curl.se/libcurl/) і розбирає відповіді бібліотекою [nlohmann JSON](https://github.com/nlohmann/json). Обидві є обовʼязковими і встановлюються у системі командою:

```
sudo apt install -y libcurl4-openssl-dev nlohmann-json3-dev
```

Будь-яка з цих бібліотек завантажується зі свого git-репозиторію під час кроку конфігурування CMake, якщо у системі не знайдено встановленої, тож система без наведених вище пакетів все одно збереться, доки доступна мережа.

Для запуску згенерованого виконуваного файлу необхідний токен [OpenAI API](https://developers.openai.com/api/docs). Його можна створити у розділі [API keys](https://platform.openai.com/api-keys) налаштувань облікового запису OpenAI.

Деталі у секції [Підключення до серверів OpenAI](/doc/sections/uk_UA/5-project-build/ai/5-37-connecting-to-the-openai-servers.md).
