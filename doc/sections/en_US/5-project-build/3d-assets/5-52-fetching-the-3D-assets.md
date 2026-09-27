## Fetching the 3D assets

The project fetches free 3D assets at the configure time: models, PBR textures and HDRIs to render instead of yet another hand made cube, together with the models made to test a renderer. Four providers are available, each enabled by a CMake variable of its own, all of them `OFF` by default:

| Variable | Provider | Assets |
| --- | --- | --- |
| `ENABLE_POLYHAVEN_ASSETS` | [Poly Haven](/doc/sections/en_US/5-project-build/3d-assets/5-53-enabling-the-poly-haven-assets.md) | realistic models, PBR textures and HDRIs |
| `ENABLE_KENNEY_ASSETS` | [Kenney](/doc/sections/en_US/5-project-build/3d-assets/5-54-enabling-the-kenney-assets.md) | low-poly game kits |
| `ENABLE_QUATERNIUS_ASSETS` | [Quaternius](/doc/sections/en_US/5-project-build/3d-assets/5-55-enabling-the-quaternius-assets.md) | low-poly characters, animations and worlds |
| `ENABLE_GLTF_SAMPLE_ASSETS` | [Khronos glTF Sample Assets](/doc/sections/en_US/5-project-build/3d-assets/5-56-enabling-the-gltf-sample-assets.md) | the renderer test models |

```
# Inside the source root directory

cmake -S . -B build -DENABLE_POLYHAVEN_ASSETS=ON -DENABLE_GLTF_SAMPLE_ASSETS=ON
```

The assets demand the CMake 3.19 or newer (the `string(JSON)` command), while the rest of the project keeps building with the 3.13 one. **The assets are never committed into the repository**: they are fetched into the build tree, and the glTF 2.0 format (the `.gltf` and the binary `.glb` files) is the one to prefer, since it carries the geometry, the materials, the textures, the skeletons and the animations alike.

### The assets directory

Every asset gets a directory of its own under the `TEMPLATE_APP_ASSETS_DIR` directory (the `assets` one of the build tree by default), grouped by the asset type, and a record of its source and license:

```
build/assets/
├── models/
│   ├── Barrel_01/                    # Poly Haven: the glTF scene, its buffer and textures
│   ├── castle-kit/                   # Kenney: the pack as published
│   ├── universal-animation-library/  # Quaternius: the pack as published
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

An already present asset directory is reused as is, so a reconfigure downloads nothing - delete the directory to fetch the asset anew (e.g. after changing its resolution). Point the `TEMPLATE_APP_ASSETS_DIR` variable at a directory outside the build tree to share the assets between several build trees or to configure with no network at all (an offline host, a sandboxed flatpak build).

### The licenses

The record of an asset (`licenses/<type>s/<name>.txt`) tells where it came from and what it is licensed under:

```
Source: https://kenney.nl/assets/castle-kit
License: Creative Commons CC0 (https://creativecommons.org/publicdomain/zero/1.0/)
```

**The license a provider states for an asset is checked before the asset is downloaded**: it has to match the `ASSETS_ALLOWED_LICENSES` list of the license URLs (or their parts), or the configure fails. The list holds the [CC0](https://creativecommons.org/publicdomain/zero/1.0/) alone by default - the license which demands no attribution and permits any use, the commercial one included. Extend it deliberately, e.g. with the CC-BY 4.0 for the assets whose authors you are ready to credit:

```
cmake -S . -B build -DENABLE_GLTF_SAMPLE_ASSETS=ON -DGLTF_SAMPLE_MODELS="WaterBottle;Fox" \
  -DASSETS_ALLOWED_LICENSES="creativecommons.org/publicdomain/zero/1.0;creativecommons.org/licenses/by/4.0"
```

### Requesting the assets from CMake

Every provider fetches the assets its list variable names, while the `template_project_add_asset` function of the `cmake/enablers/3d-assets/template-project-3d-assets.cmake` module requests any other one from the project CMake code (e.g. the `src/CMakeLists.txt` file), provided the provider is enabled:

```cmake
template_project_add_asset(
  PROVIDER POLYHAVEN   # POLYHAVEN, KENNEY, QUATERNIUS or GLTF_SAMPLE
  ID brown_planks_03   # the asset id at the provider
  TYPE TEXTURE         # MODEL (by default), TEXTURE or HDRI - the <type>s subdirectory
  NAME planks          # the asset subdirectory, the ID by default
  RESOLUTION 2k        # the options of the provider
)
```

### Reaching the assets from the C++ code

Hand the directory over to the code and load the files relative to it, e.g. with a glTF loader like [cgltf](https://github.com/jkuhlmann/cgltf), [tinygltf](https://github.com/syoyo/tinygltf) or [fastgltf](https://github.com/spnda/fastgltf):

```cmake
target_compile_definitions(${PROJECT_BINARY_NAME} PRIVATE TEMPLATE_APP_ASSETS_DIR="${TEMPLATE_APP_ASSETS_DIR}")
```

```cpp
const std::string bottle = TEMPLATE_APP_ASSETS_DIR "/models/WaterBottle/WaterBottle.glb";
```

An installed application carries its assets with it: install the directory, e.g. `install(DIRECTORY "${TEMPLATE_APP_ASSETS_DIR}/" DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_BINARY_NAME}/assets")`, and resolve the path at the run time accordingly.
