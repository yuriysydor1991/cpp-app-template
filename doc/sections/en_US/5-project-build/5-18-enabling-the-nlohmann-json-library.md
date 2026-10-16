## Enabling the nlohmann JSON library

In order to enable [nlohmann](https://github.com/nlohmann/json.git) JSON library for the project by using the installed system one or by fetching it by the available connection set an `ON` value to the `ENABLE_NLOHMANN_JSON` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_NLOHMANN_JSON=ON
```

The option is `ON` by default on this branch, because the [Claude client](/doc/sections/en_US/5-project-build/ai/5-37-connecting-to-the-claude-servers.md) reads the API answers with that library and the CMake configure step fails with an explanatory message when the option is turned off.

A system without the installed library gets the sources of the `TEMPLATE_APP_NLOHMANN_GIT_TAG` release (`v3.12.0` by default) fetched and built, while the flatpak package builds the very same `v3.12.0` release from it's checksum verified archive.
