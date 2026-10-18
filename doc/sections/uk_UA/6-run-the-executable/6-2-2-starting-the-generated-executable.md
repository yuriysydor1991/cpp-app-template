### Запуск згенерованого виконуваного файлу

Якщо виконуваний бінарний файл скомпільований і наявний у директорії побудови проекту його можна запустити з терміналу використовуючи шлях знайдений з попередньої секції командою:

```
# наприклад, з директорії побудови

./src/CppAppTemplate
```

Виконуваний файл гілки `appPiperTTS` промовляє привітання `Hello, Piper! Insert your text here!` англійським голосом `en_US-lessac-medium`, який завантажує конфігурування, через типовий аудіопристрій системи і завершується, щойно мовлення відтворено (або його зупинять клавіші Ctrl+C). Параметр `--text` (або `-t`) задає інший текст, параметр `--voice` (або `-s`) - іншу модель голосу Piper (наприклад, українську, яку завантажує конфігурування з `-DTEMPLATE_APP_PIPER_VOICE=uk_UA-ukrainian_tts-medium`), а параметр `--output` (або `-o`) записує мовлення у 16-бітний монофонічний WAV-файл PCM замість відтворення:

```
# з директорії побудови
./src/CppAppTemplate -t "Hello, world!" -s voices/en_US-lessac-medium.onnx
./src/CppAppTemplate -t "Привіт, світе!" -s voices/uk_UA-ukrainian_tts-medium.onnx -o hello.wav
```

```
2026-10-18 12:59:11 DBG 140558553168896 PiperController.cpp:80 : The voices/en_US-lessac-medium.onnx Piper voice is loaded
2026-10-18 12:59:12 DBG 140558553168896 PiperController.cpp:120 : Synthesized 22272 samples with the voices/en_US-lessac-medium.onnx Piper voice
```

І ще раз, ім'я `CppAppTemplate` являється ім'ям головного виконуваного бінарного файлу за замовчуванням. Його необхідно замінити у разі заміни ім'я за умовчанням у кореневому файлі `CMakeLists.txt` (змінні `CMAKE_PROJECT_NAME` або `PROJECT_BINARY_NAME`).
