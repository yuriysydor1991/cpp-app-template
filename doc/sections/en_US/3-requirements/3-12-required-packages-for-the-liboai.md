## Required packages for the liboai

The [liboai](https://github.com/d7ead/liboai) library depends on the libcurl and the nlohmann JSON libraries. The system wide installed ones are used when they are found, so install them to keep the configure step short:

```
sudo apt install -y libcurl4-openssl-dev nlohmann-json3-dev
```

Every absent one is taken from it's git repository during the CMake configure step, which needs the CMake 3.24 or newer: only since that version the CMake hands a fetched copy over to the `find_package` calls of the liboai. The library itself is taken from it's git repository the same way when no system wide installed one is found, so no additional package is needed for it.

An [OpenAI API](https://platform.openai.com/docs/api-reference/chat) token is required to run the generated executable. Create it in the [OpenAI platform](https://platform.openai.com/api-keys) account settings.

Look for the details at the [Enabling the liboai library](/doc/sections/en_US/5-project-build/ai/5-37-enabling-the-liboai-library.md).
