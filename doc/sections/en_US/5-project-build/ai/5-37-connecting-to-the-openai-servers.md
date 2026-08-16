## Connecting to the OpenAI servers

OpenAI publishes official SDKs for Python, TypeScript, .NET, Java, Go and Ruby, but none for C++. This branch therefore talks to the [OpenAI API](https://developers.openai.com/api/docs) directly: the `curli::CURLController` of the `src/CURL` directory performs the HTTPS request and the `chatgpti::ChatGPTController` of the `src/chatgpt` directory builds and reads the JSON around it. No third party API wrapper is involved, so the only dependencies are the [libcurl](https://curl.se/libcurl/) and the [nlohmann JSON](https://github.com/nlohmann/json) libraries, both enabled by default on this branch through the `ENABLE_LIBCURL` and the `ENABLE_NLOHMANN_JSON` CMake variables.

Both libraries are used from the system when they are installed, as the [Required packages for the ChatGPT client](/doc/sections/en_US/3-requirements/3-12-required-packages-for-the-chatgpt-client.md) section describes, and are taken from their git repositories otherwise. Every repository and it's tag is a CMake variable of it's own:

```
cmake -S . -B build -DTEMPLATE_APP_NLOHMANN_GIT_TAG=v3.11.3
```

### Asking the model

The generated executable asks [ChatGPT](https://chatgpt.com/) the question given with the `--question` (or `-q`) command line parameter and prints the received answer:

```
./build/src/CppAppTemplate --token <your-openai-api-token> --question "What is the point of taxes?"
```

The token is taken from the `OPENAI_API_KEY` environment variable when the `--token` (or `-t`) parameter is omitted, which keeps it out of the process command line visible to every user of the machine:

```
export OPENAI_API_KEY=<your-openai-api-token>

./build/src/CppAppTemplate --question "What is the point of taxes?"
```

The `gpt-5.6` model is asked by default, which is the alias of the flagship model of the family. Any other one available for the used token is requested with the `--model` (or `-m`) parameter:

```
./build/src/CppAppTemplate --model gpt-5.6-terra --question "What is the point of taxes?"
```

The executable exits with a non zero status and an error description when the token is rejected or no answer is received. Without a question it only prints the hint on how to provide one, so the component tests keep passing with no token available.

### The request the controller builds

The `chatgpti::ChatGPTController::ask` method sends the question to the [responses](https://developers.openai.com/api/docs/api-reference/responses/create) endpoint at `https://api.openai.com/v1/responses`:

```
{"model":"gpt-5.6","input":"..."}
```

Three details of that endpoint are worth keeping in mind when extending the class:

- The authorization header is the usual `Authorization: Bearer <token>` one, and no API version header is required next to it.
- The answer arrives as an array of the typed output items rather than as a single string, and a reasoning item commonly precedes the answering message one, so the `extract_answer` method walks every `message` item and concatenates the text of it's every `output_text` block. The endpoint documentation explicitly warns against reading the answer out of the first item. A model may also decline the question with a `refusal` block instead of a text one, which the method reports as an error rather than as an answer.
- No `max_output_tokens` field is sent, unlike the required `max_tokens` one of some other vendors. The limit counts the invisible reasoning tokens as well, so a modest value makes the endpoint answer with a `status` of `incomplete`, spend the whole budget on the reasoning and carry no message item at all. Set the field only together with a generous value.

### The subsystem structure

The `curli::CURLController` class performs the request with it's `post` method, which sends a body with a set of headers, tells whether the answer carries a success status through the `last_response_successfull` method and keeps the code itself available through the `last_response_code` one. Asking the first of them keeps the HTTP statuses inside the transport, so the client class holds no status constant of it's own. Unlike it's `download` method, the `post` one applies no low speed abort and waits far longer, because a model composing an answer sends nothing over the connection meanwhile. See the [Enabling the libcurl](/doc/sections/en_US/5-project-build/5-14-enabling-libcurl.md) section for the rest of that class.

The `chatgpti::ChatGPTController` class takes that controller as a constructor argument, which lets the `UTEST_ChatGPTController` unit test verify the built request and the parsed answer against a mocked transport with no network access at all. The `app::Application` class drives the controller with the values the `app::CommandLineParser` places into the `app::ApplicationContext` instance.
