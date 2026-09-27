## Завантаження 3D ресурсів

Проект завантажує вільні 3D ресурси під час налаштування: моделі, PBR текстури та HDRI, щоб рендерити їх замість ще одного написаного вручну куба, а також моделі, створені для перевірки рендерера. Доступні чотири постачальники, кожен вмикається власною змінною CMake, і всі вони типово мають значення `OFF`:

| Змінна | Постачальник | Ресурси |
| --- | --- | --- |
| `ENABLE_POLYHAVEN_ASSETS` | [Poly Haven](/doc/sections/uk_UA/5-project-build/3d-assets/5-53-enabling-the-poly-haven-assets.md) | реалістичні моделі, PBR текстури та HDRI |
| `ENABLE_KENNEY_ASSETS` | [Kenney](/doc/sections/uk_UA/5-project-build/3d-assets/5-54-enabling-the-kenney-assets.md) | low-poly ігрові набори |
| `ENABLE_QUATERNIUS_ASSETS` | [Quaternius](/doc/sections/uk_UA/5-project-build/3d-assets/5-55-enabling-the-quaternius-assets.md) | low-poly персонажі, анімації та світи |
| `ENABLE_GLTF_SAMPLE_ASSETS` | [Khronos glTF Sample Assets](/doc/sections/uk_UA/5-project-build/3d-assets/5-56-enabling-the-gltf-sample-assets.md) | тестові моделі для рендерера |

```
# Всередині кореневої директорії з вихідними кодами

cmake -S . -B build -DENABLE_POLYHAVEN_ASSETS=ON -DENABLE_GLTF_SAMPLE_ASSETS=ON
```

Ресурси потребують CMake 3.19 або новішого (команда `string(JSON)`), тоді як решта проекту й надалі збирається з версією 3.13. **Ресурси ніколи не потрапляють до даного репозиторію**: вони завантажуються до дерева побудови, а перевагу варто надавати формату glTF 2.0 (файли `.gltf` та двійкові `.glb`), оскільки він однаково несе геометрію, матеріали, текстури, скелети та анімації.

### Директорія ресурсів

Кожен ресурс отримує власну директорію всередині директорії `TEMPLATE_APP_ASSETS_DIR` (типово це директорія `assets` дерева побудови), згруповану за типом ресурсу, та запис про своє джерело і ліцензію:

```
build/assets/
├── models/
│   ├── Barrel_01/                    # Poly Haven: сцена glTF, її буфер та текстури
│   ├── castle-kit/                   # Kenney: набір у тому вигляді, в якому його опубліковано
│   ├── universal-animation-library/  # Quaternius: набір у тому вигляді, в якому його опубліковано
│   └── WaterBottle/                  # Khronos: WaterBottle.glb
├── textures/
├── hdris/
└── licenses/
    └── models/
        ├── Barrel_01.txt
        ├── castle-kit.txt
        ├── universal-animation-library.txt
        └── WaterBottle.txt
```

Вже наявна директорія ресурсу використовується як є, тож повторне налаштування нічого не завантажує - видали директорію, щоб завантажити ресурс наново (наприклад, після зміни його роздільної здатності). Вкажи у змінній `TEMPLATE_APP_ASSETS_DIR` директорію поза деревом побудови, щоб ділити ресурси між декількома деревами побудови або налаштовувати проект взагалі без мережі (хост без доступу до мережі, ізольована збірка flatpak).

### Ліцензії

Запис ресурсу (`licenses/<type>s/<name>.txt`) повідомляє, звідки ресурс походить і під якою ліцензією він поширюється:

```
Source: https://kenney.nl/assets/castle-kit
License: Creative Commons CC0 (https://creativecommons.org/publicdomain/zero/1.0/)
```

**Ліцензія, яку постачальник вказує для ресурсу, перевіряється до завантаження ресурсу**: вона має відповідати списку `ASSETS_ALLOWED_LICENSES` з адрес ліцензій (або їхніх частин), інакше налаштування завершується помилкою. Типово список містить лише [CC0](https://creativecommons.org/publicdomain/zero/1.0/) - ліцензію, яка не вимагає зазначення авторства та дозволяє будь-яке використання, зокрема комерційне. Розширюй його свідомо, наприклад ліцензією CC-BY 4.0 для ресурсів, авторів яких ти готовий зазначати:

```
cmake -S . -B build -DENABLE_GLTF_SAMPLE_ASSETS=ON -DGLTF_SAMPLE_MODELS="WaterBottle;Fox" \
  -DASSETS_ALLOWED_LICENSES="creativecommons.org/publicdomain/zero/1.0;creativecommons.org/licenses/by/4.0"
```

### Запит ресурсів з CMake

Кожен постачальник завантажує ресурси, які називає його змінна-список, тоді як функція `template_project_add_asset` модуля `cmake/enablers/3d-assets/template-project-3d-assets.cmake` запитує будь-який інший ресурс з коду CMake проекту (наприклад, з файлу `src/CMakeLists.txt`), за умови, що постачальника увімкнено:

```cmake
template_project_add_asset(
  PROVIDER POLYHAVEN   # POLYHAVEN, KENNEY, QUATERNIUS або GLTF_SAMPLE
  ID brown_planks_03   # ідентифікатор ресурсу у постачальника
  TYPE TEXTURE         # MODEL (типово), TEXTURE або HDRI - піддиректорія <type>s
  NAME planks          # піддиректорія ресурсу, типово це ID
  RESOLUTION 2k        # параметри постачальника
)
```

### Доступ до ресурсів з коду C++

Передай директорію коду та завантажуй файли відносно неї, наприклад завантажувачем glTF на кшталт [cgltf](https://github.com/jkuhlmann/cgltf), [tinygltf](https://github.com/syoyo/tinygltf) чи [fastgltf](https://github.com/spnda/fastgltf):

```cmake
target_compile_definitions(${PROJECT_BINARY_NAME} PRIVATE TEMPLATE_APP_ASSETS_DIR="${TEMPLATE_APP_ASSETS_DIR}")
```

```cpp
const std::string bottle = TEMPLATE_APP_ASSETS_DIR "/models/WaterBottle/WaterBottle.glb";
```

Встановлена програма несе свої ресурси з собою: встанови директорію, наприклад `install(DIRECTORY "${TEMPLATE_APP_ASSETS_DIR}/" DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_BINARY_NAME}/assets")`, та визначай шлях під час роботи програми відповідно.
