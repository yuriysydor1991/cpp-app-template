## Вмикання ресурсів Kenney

Для того щоб завантажити 3D ігрові набори [Kenney](https://kenney.nl/assets) (low-poly будівлі, природа, транспорт, меблі, персонажі та інше, усі під ліцензією CC0) для проекту, необхідно встановити значення `ON` для CMake змінної `ENABLE_KENNEY_ASSETS`:

```
# Всередині кореневої директорії з вихідними кодами

cmake -S . -B build -DENABLE_KENNEY_ASSETS=ON
```

| Змінна | Типове значення | Призначення |
| --- | --- | --- |
| `KENNEY_PACKS` | `castle-kit` | набори, які слід завантажити |
| `TEMPLATE_APP_KENNEY_ASSETS_URL` | `https://kenney.nl/assets` | адреса сторінок наборів |

Назва набору - це остання частина адреси сторінки набору: [https://kenney.nl/assets/castle-kit](https://kenney.nl/assets/castle-kit) - це набір `castle-kit`. **Адреса архіву та ліцензія зчитуються зі сторінки набору**, а не записуються вручну: адреса містить хеш вмісту, який сайт перегенеровує з кожним оновленням набору, а ліцензія перевіряється за списком `ASSETS_ALLOWED_LICENSES` (дивись розділ [Завантаження 3D ресурсів](/doc/sections/uk_UA/5-project-build/3d-assets/5-52-fetching-the-3D-assets.md)).

Набір залишається недоторканим, у тому вигляді, в якому його публікує Kenney: його директорія `Models` містить моделі у вигляді двійкових файлів glTF (`.glb`), FBX та OBJ, а моделі `.glb` новіших наборів посилаються на текстуру поруч з ними (`Textures/colormap.png`, спільну для всього набору) замість того, щоб вбудовувати її.

```
cmake -S . -B build -DENABLE_KENNEY_ASSETS=ON -DKENNEY_PACKS="castle-kit;car-kit;nature-kit"
```

Або з коду CMake проекту, з увімкненим механізмом:

```cmake
template_project_add_asset(PROVIDER KENNEY ID blocky-characters)
```
