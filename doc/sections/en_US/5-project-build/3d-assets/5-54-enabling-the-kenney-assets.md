## Enabling the Kenney assets

In order to fetch the [Kenney](https://kenney.nl/assets) 3D game kits (low-poly buildings, nature, vehicles, furniture, characters and more, all of them CC0) for the project set an `ON` value to the `ENABLE_KENNEY_ASSETS` CMake variable:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_KENNEY_ASSETS=ON
```

| Variable | Default | Meaning |
| --- | --- | --- |
| `KENNEY_PACKS` | `castle-kit` | the packs to fetch |
| `TEMPLATE_APP_KENNEY_ASSETS_URL` | `https://kenney.nl/assets` | the pack pages address |

The pack name is the last part of the pack page address: [https://kenney.nl/assets/castle-kit](https://kenney.nl/assets/castle-kit) is the `castle-kit` pack. **The archive address and the license are read out of the pack page** rather than written down: the address carries a content hash the site regenerates on every pack update, and the license is checked against the `ASSETS_ALLOWED_LICENSES` list (see the [Fetching the 3D assets](/doc/sections/en_US/5-project-build/3d-assets/5-52-fetching-the-3D-assets.md) section).

The pack stays intact, the way Kenney publishes it: its `Models` directory carries the models as the binary glTF (`.glb`), the FBX and the OBJ files, and the `.glb` models of the newer packs refer to a texture lying next to them (`Textures/colormap.png`, shared by the whole kit) instead of embedding it.

```
cmake -S . -B build -DENABLE_KENNEY_ASSETS=ON -DKENNEY_PACKS="castle-kit;car-kit;nature-kit"
```

Or from the project CMake code, with the enabler on:

```cmake
template_project_add_asset(PROVIDER KENNEY ID blocky-characters)
```
