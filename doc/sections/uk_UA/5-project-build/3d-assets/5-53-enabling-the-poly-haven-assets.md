## Вмикання ресурсів Poly Haven

Для того щоб завантажити ресурси [Poly Haven](https://polyhaven.com) (реалістичні моделі, PBR текстури та HDRI, кожен з яких поширюється під ліцензією [CC0](https://polyhaven.com/license)) для проекту, необхідно встановити значення `ON` для CMake змінної `ENABLE_POLYHAVEN_ASSETS`:

```
# Всередині кореневої директорії з вихідними кодами

cmake -S . -B build -DENABLE_POLYHAVEN_ASSETS=ON
```

Ресурси надходять через безкоштовний [Poly Haven API](https://api.polyhaven.com), який перелічує кожен файл ресурсу в кожній роздільній здатності разом з його сумою MD5, тож кожен завантажений файл перевіряється, а неушкоджений ніколи не завантажується вдруге. [Умови використання API](https://github.com/Poly-Haven/Public-API/blob/master/ToS.md) вимагають, щоб кожен запит називав програму, яка його робить, тому запити несуть user agent `<PROJECT_BINARY_NAME>/<PROJECT_VERSION>` - [перейменуй проект](/doc/sections/uk_UA/4-project-structure/4-2-changing-the-project-and-executable-name.md), щоб мати власний. Умови просять програму, яка показує вміст Poly Haven через живий API, зазначати Poly Haven, тоді як самі завантажені ресурси зовсім не потребують зазначення авторства. Дивись розділ [Завантаження 3D ресурсів](/doc/sections/uk_UA/5-project-build/3d-assets/5-52-fetching-the-3D-assets.md) щодо директорії ресурсів, ліцензій та інтерфейсу CMake.

| Змінна | Типове значення | Призначення |
| --- | --- | --- |
| `POLYHAVEN_MODELS` | `Barrel_01` | моделі, які слід завантажити |
| `POLYHAVEN_TEXTURES` | порожнє | текстури, які слід завантажити |
| `POLYHAVEN_RESOLUTION` | `1k` | роздільна здатність: `1k`, `2k`, `4k` або `8k` |
| `TEMPLATE_APP_POLYHAVEN_API_URL` | `https://api.polyhaven.com` | адреса API |

Ідентифікатор ресурсу - це остання частина адреси сторінки ресурсу: [https://polyhaven.com/a/Barrel_01](https://polyhaven.com/a/Barrel_01) - це модель `Barrel_01`. Модель чи текстура надходить як сцена glTF (наприклад, `Barrel_01_1k.gltf`) з її буфером та директорією `textures` - дифузною картою, картою нормалей OpenGL (`nor_gl`) та картою шорсткості або ARM (фонове затінення, шорсткість та металевість), готовими для PBR шейдера:

```
cmake -S . -B build -DENABLE_POLYHAVEN_ASSETS=ON \
  -DPOLYHAVEN_MODELS="Barrel_01;rock_07" -DPOLYHAVEN_TEXTURES=brown_planks_03 -DPOLYHAVEN_RESOLUTION=2k
```

### Вибір інших файлів (приклад для копіювання)

Параметр `FILES` функції `template_project_add_asset` обирає будь-який інший файл, який перелічує API, за його парою `<map>/<extension>`, наприклад карту оточення HDRI для освітлення на основі зображень чи окремі карти текстури:

```cmake
template_project_add_asset(PROVIDER POLYHAVEN ID abandoned_bakery TYPE HDRI FILES hdri/hdr)

template_project_add_asset(
  PROVIDER POLYHAVEN ID brown_planks_03 TYPE TEXTURE NAME planks RESOLUTION 2k
  FILES Diffuse/jpg nor_gl/jpg arm/jpg Displacement/png
)
```

Адреса [https://api.polyhaven.com/files/brown_planks_03](https://api.polyhaven.com/files/brown_planks_03) перелічує те, що пропонує текстура - карти `Diffuse`, `nor_gl`, `nor_dx`, `arm`, `AO`, `Rough`, `Displacement` та інші, кожну у форматах `jpg`, `png` та `exr`, - тоді як модель пропонує ще й сцени `gltf`, `fbx`, `usd` та `blend`, а HDRI - файли `hdri/hdr` та `hdri/exr`.
