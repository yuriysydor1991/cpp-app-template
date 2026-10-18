## Вмикання відтворення звуку SDL2

Для того щоб відтворювати синтезоване мовлення типовим пристроєм відтворення звуку системи через аудіопідсистему бібліотеки [SDL2](https://www.libsdl.org/), необхідно встановити значення `ON` для CMake змінної `ENABLE_SDL2_AUDIO` (для гілок синтезу мовлення це значення за замовчуванням):

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_SDL2_AUDIO=ON
cmake --build build --target all
```

Модуль [cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake](/cmake/enablers/audio/template-project-sdl2-audio-enabler.cmake) спершу шукає встановлену в системі SDL2 (пакет `libsdl2-dev`, який встановлюють скрипти `scripts/packages`), а інакше завантажує через мережу Інтернет тег `TEMPLATE_APP_SDL2_GIT_TAG` (за замовчуванням `release-2.32.10`) репозиторію `TEMPLATE_APP_SDL2_GIT`. Знайдена ціль потрапляє у змінну `TEMPLATE_APP_SDL2_AUDIO_TARGET`, тож прилінковуй її до своїх цільових об'єктів:

```
target_link_libraries(${PROJECT_BINARY_NAME} ${TEMPLATE_APP_SDL2_AUDIO_TARGET})
```

### Програвач

Клас `tts::AudioPlayer` з файлу [src/TTS/AudioPlayer.h](/src/TTS/AudioPlayer.h) відкриває типовий пристрій відтворення для монофонічних 16-бітних відліків з частотою мовлення без функції зворотного виклику, тож SDL2 відтворює поставлене у чергу мовлення у власному потоці, перетворюючи його на формат, який відтворює пристрій. Виклик `play` чекає, доки пристрій не відтворить мовлення до кінця або доки задана перевірка не попросить зупинитися, а клас Application пов'язує її з клавішами Ctrl+C:

```
const tts::Speech speech{samples, 22050};

tts::AudioPlayer::create()->play(speech, [] { return false; });
```

Мовлення проходить через той самий програвач, хоч би який рушій його синтезував, тож гілки синтезу мовлення мають цей клас спільним.

Змінна оточення `SDL_AUDIODRIVER` обирає аудіодрайвер (`pipewire`, `pulseaudio`, `alsa` тощо). Лише нею обираються драйвери `dummy` і `disk`: перший відтворює мовлення в нікуди у темпі реального часу, а другий записує відтворені відліки у файл `SDL_DISKAUDIOFILE` (за замовчуванням `sdlaudio.raw`) з паузою `SDL_DISKAUDIODELAY` мілісекунд між буферами пристрою, тож тести використовують їх замість справжнього пристрою:

```
SDL_AUDIODRIVER=dummy ./src/CppAppTemplate
SDL_AUDIODRIVER=disk SDL_DISKAUDIOFILE=speech.raw ./src/CppAppTemplate
```

Бібліотека [sdl2-compat](https://github.com/libsdl-org/sdl2-compat) на основі SDL3, яка замінює SDL2 у деяких новіших дистрибутивах, натомість записує файл `SDL_AUDIO_DISK_OUTPUT_FILE` у темпі множника `SDL_AUDIO_DISK_TIMESCALE` і перетворює для нього мовлення на формат власного пристрою.
