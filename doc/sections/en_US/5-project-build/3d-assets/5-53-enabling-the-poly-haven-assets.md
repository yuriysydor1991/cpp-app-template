## Enabling the Poly Haven assets

In order to fetch the [Poly Haven](https://polyhaven.com) assets (realistic models, PBR textures and HDRIs, every one of them [CC0](https://polyhaven.com/license)) for the project set an `ON` value to the `ENABLE_POLYHAVEN_ASSETS` CMake variable:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_POLYHAVEN_ASSETS=ON
```

The assets come through the free [Poly Haven API](https://api.polyhaven.com), which lists every file of an asset in every resolution together with its MD5 sum, so every downloaded file is verified and an intact one is never downloaded twice. The [API terms](https://github.com/Poly-Haven/Public-API/blob/master/ToS.md) demand every request to name the software making it, hence the requests carry the `<PROJECT_BINARY_NAME>/<PROJECT_VERSION>` user agent - [rename the project](/doc/sections/en_US/4-project-structure/4-2-changing-the-project-and-executable-name.md) to have your own one. The terms ask the software showing the Poly Haven content through the live API to credit Poly Haven, while the downloaded assets themselves need no attribution at all. See the [Fetching the 3D assets](/doc/sections/en_US/5-project-build/3d-assets/5-52-fetching-the-3D-assets.md) section for the assets directory, the licenses and the CMake interface.

| Variable | Default | Meaning |
| --- | --- | --- |
| `POLYHAVEN_MODELS` | `Barrel_01` | the models to fetch |
| `POLYHAVEN_TEXTURES` | empty | the textures to fetch |
| `POLYHAVEN_RESOLUTION` | `1k` | the resolution: `1k`, `2k`, `4k` or `8k` |
| `TEMPLATE_APP_POLYHAVEN_API_URL` | `https://api.polyhaven.com` | the API address |

The asset id is the last part of the asset page address: [https://polyhaven.com/a/Barrel_01](https://polyhaven.com/a/Barrel_01) is the `Barrel_01` model. A model or a texture comes as a glTF scene (e.g. `Barrel_01_1k.gltf`) with its buffer and its `textures` directory - the diffuse, the OpenGL normal (`nor_gl`) and the roughness or the ARM (the ambient occlusion, the roughness and the metalness) maps, ready for a PBR shader:

```
cmake -S . -B build -DENABLE_POLYHAVEN_ASSETS=ON \
  -DPOLYHAVEN_MODELS="Barrel_01;rock_07" -DPOLYHAVEN_TEXTURES=brown_planks_03 -DPOLYHAVEN_RESOLUTION=2k
```

### Picking other files (copy-paste example)

The `FILES` option of the `template_project_add_asset` function picks any other file the API lists by its `<map>/<extension>` pair, e.g. an HDRI environment map for the image based lighting or the single maps of a texture:

```cmake
template_project_add_asset(PROVIDER POLYHAVEN ID abandoned_bakery TYPE HDRI FILES hdri/hdr)

template_project_add_asset(
  PROVIDER POLYHAVEN ID brown_planks_03 TYPE TEXTURE NAME planks RESOLUTION 2k
  FILES Diffuse/jpg nor_gl/jpg arm/jpg Displacement/png
)
```

The [https://api.polyhaven.com/files/brown_planks_03](https://api.polyhaven.com/files/brown_planks_03) address lists what a texture offers - the `Diffuse`, `nor_gl`, `nor_dx`, `arm`, `AO`, `Rough`, `Displacement` and more maps, each in the `jpg`, `png` and `exr` formats - while a model offers the `gltf`, `fbx`, `usd` and `blend` scenes too and an HDRI the `hdri/hdr` and `hdri/exr` files.
