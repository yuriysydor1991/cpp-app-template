## Required packages for the Claude client

Anthropic ships no official C++ SDK, so this branch talks to the [Claude API](https://platform.claude.com/docs/en/api/overview) over the plain HTTP with the [libcurl](https://curl.se/libcurl/) and parses the answers with the [nlohmann JSON](https://github.com/nlohmann/json) library. Both are required and are installed system wide with:

```
sudo apt install -y libcurl4-openssl-dev nlohmann-json3-dev
```

Either library is taken from it's git repository during the CMake configure step when no system wide installed one is found, so a system without the packages above still builds as long as the network is reachable.

An [Anthropic API](https://platform.claude.com/docs/en/api/overview) token is required to run the generated executable. Create it in the [Anthropic Console](https://platform.claude.com/settings/keys) account settings.

Look for the details at the [Connecting to the Claude servers](/doc/sections/en_US/5-project-build/ai/5-37-connecting-to-the-claude-servers.md).
