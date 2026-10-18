### Запуск згенерованого виконуваного файлу

Якщо виконуваний бінарний файл скомпільований і наявний у директорії побудови проекту його можна запустити з терміналу використовуючи шлях знайдений з попередньої секції командою:

```
# наприклад, з директорії побудови

./src/CppAppTemplate
```

Виконуваний файл гілки `appSherpaONNX` промовляє привітання `Hello, sherpa-onnx! Insert your text here!` першим мовцем моделі Kokoro, яку конфігурування завантажує у директорію `models` дерева побудови, через типовий аудіопристрій системи і завершується, щойно мовлення відтворено (або його зупинять клавіші Ctrl+C). Параметр `--text` (або `-t`) задає інший текст, параметр `--voice` (або `-s`) - іншу директорію моделі sherpa-onnx, за якою може йти ідентифікатор мовця `:<id>`, а параметр `--output` (або `-o`) записує мовлення у 16-бітний монофонічний WAV-файл PCM замість відтворення:

```
# з директорії побудови
./src/CppAppTemplate --text "Hello, world!" --voice models/kokoro-int8-multi-lang-v1_0:3 --output hello.wav
./src/CppAppTemplate -t "它也支持英文, and English too." -s ~/models/vits-melo-tts-zh_en
```

```
2026-10-18 13:19:51.055968 DBG 140640821018752 SherpaONNXController.cpp:99 : The sherpa-onnx model of the models/kokoro-int8-multi-lang-v1_0 directory is loaded
2026-10-18 13:19:52.096190 DBG 140640821018752 SherpaONNXController.cpp:121 : Synthesized 25128 samples with the models/kokoro-int8-multi-lang-v1_0:3 sherpa-onnx voice
2026-10-18 13:19:52.097106 DBG 140640821018752 WavWriter.cpp:87 : The 1047 ms speech is written into hello.wav
```

І ще раз, ім'я `CppAppTemplate` являється ім'ям головного виконуваного бінарного файлу за замовчуванням. Його необхідно замінити у разі заміни ім'я за умовчанням у кореневому файлі `CMakeLists.txt` (змінні `CMAKE_PROJECT_NAME` або `PROJECT_BINARY_NAME`).
