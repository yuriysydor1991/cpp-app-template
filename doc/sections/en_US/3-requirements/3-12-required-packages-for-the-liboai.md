## Required packages for the liboai

The [liboai](https://github.com/d7ead/liboai) library asks for both of it's dependencies with the CMake `find_package` command, so a fetched copy of any of them stays invisible to it and both have to be installed system wide:

```
sudo apt install -y libcurl4-openssl-dev nlohmann-json3-dev
```

The library itself is taken from it's git repository during the CMake configure step when no system wide installed one is found, so no additional package is needed for it.

An [OpenAI API](https://platform.openai.com/docs/api-reference/chat) token is required to run the generated executable. Create it in the [OpenAI platform](https://platform.openai.com/api-keys) account settings.

Look for the details at the [Enabling the liboai library](/doc/sections/en_US/5-project-build/ai/5-37-enabling-the-liboai-library.md).
