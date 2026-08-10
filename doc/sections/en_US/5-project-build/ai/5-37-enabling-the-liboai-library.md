## Enabling the liboai library

The [liboai](https://github.com/d7ead/liboai) unofficial C++17 [OpenAI API](https://platform.openai.com/docs/api-reference/chat) library is enabled by default on this branch through the `ENABLE_LIBOAI` CMake variable. Set it to `OFF` to build the project without the ChatGPT integration:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_LIBOAI=OFF
```

The system wide installed library is used when it is found, and the one from the git repository is taken otherwise. Both the repository and it's tag are the `TEMPLATE_APP_LIBOAI_GIT` and the `TEMPLATE_APP_LIBOAI_GIT_TAG` CMake variables:

```
cmake -S . -B build -DTEMPLATE_APP_LIBOAI_GIT_TAG=main
```

The library asks for the libcurl and the nlohmann JSON packages with the `find_package` command, so both of them have to be installed system wide as the [Required packages for the liboai](/doc/sections/en_US/3-requirements/3-12-required-packages-for-the-liboai.md) section describes. The CMake configure step stops with a message naming them when any is absent.

### Asking the ChatGPT

The generated executable asks the [ChatGPT](https://openai.com/chatgpt/) the question given with the `--question` (or `-q`) command line parameter and prints the received answer:

```
./build/src/CppAppTemplate --token <your-openai-api-token> --question "What is the point of taxes?"
```

The token is taken from the `OPENAI_API_KEY` environment variable when the `--token` (or `-t`) parameter is omitted, which keeps it out of the process command line visible to every user of the machine:

```
export OPENAI_API_KEY=<your-openai-api-token>

./build/src/CppAppTemplate --question "What is the point of taxes?"
```

The `gpt-4o-mini` chat completion model is asked by default. Any other one available for the used token is requested with the `--model` (or `-m`) parameter:

```
./build/src/CppAppTemplate --model gpt-4o --question "What is the point of taxes?"
```

The executable exits with a non zero status and an error description when the token is rejected or no answer is received. Without a question it only prints the hint on how to provide one, so the component tests keep passing with no token available.

### The subsystem structure

The `liboaii::OAIController` class of the `src/liboai` directory wraps the library: it takes the token (the `set_token` and the `set_token_from_env` methods) and asks a single question with the `ask` one, turning the library exceptions into logged errors and an empty answer. The `app::Application` class drives it with the values the `app::CommandLineParser` places into the `app::ApplicationContext` instance.
