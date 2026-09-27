## Вмикання ресурсів Quaternius

Для того щоб завантажити low-poly набори [Quaternius](https://quaternius.com) (персонажі з їхніми анімаціями, природа, транспорт, зброя та модульні набори) для проекту, необхідно встановити значення `ON` для CMake змінної `ENABLE_QUATERNIUS_ASSETS`:

```
# Всередині кореневої директорії з вихідними кодами

cmake -S . -B build -DENABLE_QUATERNIUS_ASSETS=ON
```

Quaternius роздає набори як теки Google Drive, які збірка не має змоги завантажити, тож натомість набори надходять з [публікацій Quaternius на OpenGameArt](https://opengameart.org/users/quaternius), де кожен набір - це окремий архів.

| Змінна | Типове значення | Призначення |
| --- | --- | --- |
| `QUATERNIUS_PACKS` | `universal-animation-library` | набори (назви публікацій OpenGameArt), які слід завантажити |
| `TEMPLATE_APP_QUATERNIUS_ASSETS_URL` | сторінки публікацій OpenGameArt | адреса сторінок публікацій |

Назва набору - це остання частина адреси сторінки публікації: [https://opengameart.org/content/universal-animation-library](https://opengameart.org/content/universal-animation-library) - це набір `universal-animation-library`, манекен з його анімаційними кліпами у вигляді двійкового файлу glTF (`Godot/AnimationLibrary_Godot_Standard.glb`), готовий для скелетної анімації. Набір залишається недоторканим: більшість наборів містять файли FBX, OBJ та Blender, а новіші - ще й файли glTF.

**Ліцензія зчитується зі сторінки публікації** та перевіряється за списком `ASSETS_ALLOWED_LICENSES` (дивись розділ [Завантаження 3D ресурсів](/doc/sections/uk_UA/5-project-build/3d-assets/5-52-fetching-the-3D-assets.md)): більшість публікацій Quaternius поширюються під ліцензією CC0, тоді як декілька - під CC-BY-SA 3.0 і завершують налаштування помилкою, якщо цю ліцензію не дозволено. Публікація, що пропонує декілька ліцензій на вибір, завантажується, коли дозволено хоча б одну з них. Будь-яка інша публікація OpenGameArt з архівом ZIP чи 7z завантажується точно так само.

```
cmake -S . -B build -DENABLE_QUATERNIUS_ASSETS=ON \
  -DQUATERNIUS_PACKS="universal-animation-library;lowpoly-medieval-village-pack"
```

Або з коду CMake проекту, з увімкненим механізмом:

```cmake
template_project_add_asset(PROVIDER QUATERNIUS ID animated-fish NAME fish)
```
