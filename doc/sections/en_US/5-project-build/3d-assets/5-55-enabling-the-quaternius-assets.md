## Enabling the Quaternius assets

In order to fetch the [Quaternius](https://quaternius.com) low-poly packs (characters with their animations, nature, vehicles, weapons and modular kits) for the project set an `ON` value to the `ENABLE_QUATERNIUS_ASSETS` CMake variable:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_QUATERNIUS_ASSETS=ON
```

Quaternius hands the packs out as Google Drive folders, which a build has no way to download, so the packs come from [the Quaternius submissions at OpenGameArt](https://opengameart.org/users/quaternius) instead, where each one is an archive of its own.

| Variable | Default | Meaning |
| --- | --- | --- |
| `QUATERNIUS_PACKS` | `universal-animation-library` | the packs (the OpenGameArt submission names) to fetch |
| `TEMPLATE_APP_QUATERNIUS_ASSETS_URL` | the OpenGameArt submission pages | the submission pages address |

The pack name is the last part of the submission page address: [https://opengameart.org/content/universal-animation-library](https://opengameart.org/content/universal-animation-library) is the `universal-animation-library` pack - a mannequin with its animation clips as a binary glTF file (`Godot/AnimationLibrary_Godot_Standard.glb`), ready for the skeletal animation. The pack stays intact: most packs ship the FBX, OBJ and Blender files, the newer ones the glTF files as well.

**The license is read out of the submission page** and checked against the `ASSETS_ALLOWED_LICENSES` list (see the [Fetching the 3D assets](/doc/sections/en_US/5-project-build/3d-assets/5-52-fetching-the-3D-assets.md) section): most of the Quaternius submissions are CC0 ones, while a few are CC-BY-SA 3.0 ones and fail the configure unless allowed. A submission offering several licenses to choose from is fetched when one of them is allowed. Any other OpenGameArt submission shipping a ZIP or a 7z archive is fetched the very same way.

```
cmake -S . -B build -DENABLE_QUATERNIUS_ASSETS=ON \
  -DQUATERNIUS_PACKS="universal-animation-library;lowpoly-medieval-village-pack"
```

Or from the project CMake code, with the enabler on:

```cmake
template_project_add_asset(PROVIDER QUATERNIUS ID animated-fish NAME fish)
```
