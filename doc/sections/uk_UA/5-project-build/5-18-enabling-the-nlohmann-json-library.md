## Вмикання інтеграції бібліотеки nlohmann JSON

Для того щоб увімкнути підтримку бібліотеки [nlohmann JSON](https://github.com/nlohmann/json.git) для проекту, використовуючи встановлену версію або через завантаження з мережі, необхідно встановити значення `ON` для CMake змінної `ENABLE_NLOHMANN_JSON`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_NLOHMANN_JSON=ON
```

На цій гілці опція має значення `ON` за замовчуванням, бо [клієнт ChatGPT](/doc/sections/uk_UA/5-project-build/ai/5-37-connecting-to-the-openai-servers.md) розбирає відповіді API саме цією бібліотекою, і крок конфігурування CMake завершується з пояснювальним повідомленням, якщо опцію вимкнути.
