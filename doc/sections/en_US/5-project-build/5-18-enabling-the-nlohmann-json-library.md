## Enabling the nlohmann JSON library

In order to enable [nlohmann](https://github.com/nlohmann/json.git) JSON library for the project by using the installed system one or by fetching it by the available connection set an `ON` value to the `ENABLE_NLOHMANN_JSON` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_NLOHMANN_JSON=ON
```

The option is `ON` by default on this branch, because the [ChatGPT client](/doc/sections/en_US/5-project-build/ai/5-37-connecting-to-the-openai-servers.md) reads the API answers with that library and the CMake configure step fails with an explanatory message when the option is turned off.
