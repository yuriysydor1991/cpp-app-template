## Connecting to the Claude servers

Anthropic publishes official SDKs for Python, TypeScript, Java, Go, Ruby, C# and PHP, but none for C++. This branch therefore talks to the [Claude API](https://platform.claude.com/docs/en/api/overview) directly: the `curli::CURLController` of the `src/CURL` directory performs the HTTPS request and the `claudei::ClaudeController` of the `src/claude` directory builds and reads the JSON around it. No third party API wrapper is involved, so the only dependencies are the [libcurl](https://curl.se/libcurl/) and the [nlohmann JSON](https://github.com/nlohmann/json) libraries, both enabled by default on this branch through the `ENABLE_LIBCURL` and the `ENABLE_NLOHMANN_JSON` CMake variables.

Both libraries are used from the system when they are installed, as the [Required packages for the Claude client](/doc/sections/en_US/3-requirements/3-12-required-packages-for-the-claude-client.md) section describes, and are taken from their git repositories otherwise. Every repository and it's tag is a CMake variable of it's own:

```
cmake -S . -B build -DTEMPLATE_APP_NLOHMANN_GIT_TAG=v3.11.3
```

### Asking the model

The generated executable asks [Claude](https://www.claude.com/) the question given with the `--question` (or `-q`) command line parameter and prints the received answer:

```
./build/src/CppAppTemplate --token <your-anthropic-api-token> --question "What is the point of taxes?"
```

The token is taken from the `ANTHROPIC_API_KEY` environment variable when the `--token` (or `-t`) parameter is omitted, which keeps it out of the process command line visible to every user of the machine:

```
export ANTHROPIC_API_KEY=<your-anthropic-api-token>

./build/src/CppAppTemplate --question "What is the point of taxes?"
```

The `claude-opus-5` model is asked by default. Any other one available for the used token is requested with the `--model` (or `-m`) parameter:

```
./build/src/CppAppTemplate --model claude-sonnet-5 --question "What is the point of taxes?"
```

The executable exits with a non zero status and an error description when the token is rejected or no answer is received. Without a question it only prints the hint on how to provide one, so the component tests keep passing with no token available.

### The request the controller builds

The `claudei::ClaudeController::ask` method sends a single user message to the `https://api.anthropic.com/v1/messages` endpoint:

```
{"model":"claude-opus-5","max_tokens":16000,"messages":[{"role":"user","content":"..."}]}
```

Three details of that endpoint are worth keeping in mind when extending the class:

- The `max_tokens` field is **required** and bounds the answer length. The `DEFAULT_MAX_TOKENS` field of the class holds the value used.
- The authorization header is `x-api-key`, not the `Authorization: Bearer` one, and the `anthropic-version` header is required next to it.
- The answer arrives as an array of the typed content blocks rather than as a single string, so the `extract_answer` method concatenates the text of every block of the `text` type and skips the rest. A response may also carry a `stop_reason` of `refusal`, which the method reports as an error instead of an answer.

### The subsystem structure

The `curli::CURLController` class gained a `post` method that sends a body with a set of headers, tells whether the answer carries a success status through the `last_response_successfull` method and keeps the code itself available through the `last_response_code` one. Asking the first of them keeps the HTTP statuses inside the transport, so the client class holds no status constant of it's own. Unlike it's `download` method, the `post` one applies no low speed abort and waits far longer, because a model composing an answer sends nothing over the connection meanwhile.

The `claudei::ClaudeController` class takes that controller as a constructor argument, which lets the `UTEST_ClaudeController` unit test verify the built request and the parsed answer against a mocked transport with no network access at all. The `app::Application` class drives the controller with the values the `app::CommandLineParser` places into the `app::ApplicationContext` instance.
