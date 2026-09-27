## Enabling the Khronos glTF Sample Assets

In order to fetch the [Khronos glTF Sample Assets](https://github.com/KhronosGroup/glTF-Sample-Assets) for the project set an `ON` value to the `ENABLE_GLTF_SAMPLE_ASSETS` CMake variable:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_GLTF_SAMPLE_ASSETS=ON
```

These are not an art library but the glTF 2.0 test suite: models made to exercise a renderer feature by feature - the PBR metallic-roughness materials, the normal maps, the animations, the skins, the morph targets, the instancing, the material extensions (the transmission, the clearcoat, the sheen, the IOR, the iridescence), the Draco and the KTX compression. The pretty model tells the renderer works, the pathological one tells whether it really does.

| Variable | Default | Meaning |
| --- | --- | --- |
| `GLTF_SAMPLE_MODELS` | `WaterBottle` | the models to fetch |
| `GLTF_SAMPLE_VARIANT` | `glTF-Binary` | the model variant: `glTF-Binary` (a single `.glb` file), `glTF` (a `.gltf` file with its buffers and images), `glTF-Embedded`, `glTF-Draco` and more |
| `TEMPLATE_APP_GLTF_SAMPLE_ASSETS_URL` | the `main` branch files | the repository files address - put a commit in place of the `main` for the reproducible builds |

The model name is its directory in the [Models](https://github.com/KhronosGroup/glTF-Sample-Assets/tree/main/Models) listing, and the variants of a model are the `glTF*` subdirectories of its own directory.

**The models share no common license**: the `metadata.json` file of each model records a license per author and per part, and every one of them has to be on the `ASSETS_ALLOWED_LICENSES` list (see the [Fetching the 3D assets](/doc/sections/en_US/5-project-build/3d-assets/5-52-fetching-the-3D-assets.md) section), the record of the fetched model listing them all with the authors to credit. The famous `DamagedHelmet` is a CC-BY 4.0 and CC-BY-NC 4.0 (no commercial use) one and the animated `Fox` demands a CC-BY 4.0 credit, so the default CC0 list refuses both, while the `WaterBottle`, `Avocado`, `Lantern`, `ToyCar`, `AnimatedMorphCube`, `MetalRoughSpheresNoTextures` or `SimpleInstancing` models are CC0 ones.

```
cmake -S . -B build -DENABLE_GLTF_SAMPLE_ASSETS=ON -DGLTF_SAMPLE_MODELS="WaterBottle;AnimatedMorphCube;SimpleInstancing"
```

### Another variant of a model (copy-paste example)

Some models come in the `.gltf` variants alone (e.g. the CC0 `SimpleSkin`, `SimpleMorph` and `SciFiHelmet` ones), and the `VARIANT` option of the `template_project_add_asset` function picks one for a single model:

```cmake
template_project_add_asset(PROVIDER GLTF_SAMPLE ID SimpleSkin VARIANT glTF)
```

A `.gltf` model comes together with the buffers and the images it refers to, their names decoded as the glTF loaders decode them (the `Box With Spaces` test model).
