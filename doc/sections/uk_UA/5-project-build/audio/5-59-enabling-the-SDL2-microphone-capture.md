## Вмикання захоплення мікрофона SDL2

Для того щоб захоплювати типовий мікрофон системи через аудіопідсистему бібліотеки [SDL2](https://www.libsdl.org/), необхідно встановити значення `ON` для CMake змінної `ENABLE_SDL2_AUDIO` (для гілки `appWhisperCPP` це значення за замовчуванням):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_SDL2_AUDIO=ON
cmake --build build --target all
```

Приклади whisper.cpp захоплюють мікрофон через цю саму бібліотеку. Модуль [cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake](/cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake) спершу шукає встановлену в системі SDL2 (пакет `libsdl2-dev`, який встановлюють скрипти `scripts/packages`), а інакше завантажує через мережу Інтернет тег `TEMPLATE_APP_SDL2_GIT_TAG` (за замовчуванням `release-2.32.10`) репозиторію `TEMPLATE_APP_SDL2_GIT`. Знайдена ціль потрапляє у змінну `TEMPLATE_APP_SDL2_AUDIO_TARGET`, тож прилінковуй її до своїх цільових об'єктів:

```
target_link_libraries(${PROJECT_BINARY_NAME} ${TEMPLATE_APP_SDL2_AUDIO_TARGET})
```

### Мікрофон

Клас `whisperi::Microphone` з файлу [src/WhisperCPP/Microphone.h](/src/WhisperCPP/Microphone.h) відкриває типовий пристрій захоплення без функції зворотного виклику, тож SDL2 ставить захоплене аудіо у чергу у власному потоці, перетворюючи його на монофонічні відліки з рухомою комою заданої частоти, а кожен виклик `read` забирає відліки, що надійшли у чергу після попереднього виклику:

```
whisperi::Microphone microphone;

if (microphone.open(16000)) {
  const auto samples = microphone.read();
}
```

Змінна оточення `SDL_AUDIODRIVER` обирає аудіодрайвер (`pipewire`, `pulseaudio`, `alsa` тощо). Лише нею обираються драйвери `dummy` і `disk`: перший захоплює тишу, а другий - сирі відліки файлу `SDL_DISKAUDIOFILEIN` саме у тому форматі, який запитує програма (тут це 32-бітні монофонічні відліки з рухомою комою з частотою 16 кГц), тож тести використовують їх замість справжнього пристрою:

```
SDL_AUDIODRIVER=disk SDL_DISKAUDIOFILEIN=speech.raw ./src/CppAppTemplate
```
