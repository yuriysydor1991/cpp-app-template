## Enabling the llama.cpp language models

In order to enable the [llama.cpp](https://github.com/ggml-org/llama.cpp) library (the C/C++ inference of the large language models of the GGUF format on the CPU and the GPU) for the project set an `ON` value to the `ENABLE_LLAMACPP` CMake variable (it is the default one for the `appLlamaCPP` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_LLAMACPP=ON
cmake --build build --target all
```

The application of this branch is built around the llama.cpp, so the option is a hard requirement here: the CMake configure step fails with an explanatory message when the option is turned `OFF`.

The [cmake/enablers/ai/template-project-llamacpp-enabler.cmake](/cmake/enablers/ai/template-project-llamacpp-enabler.cmake) module probes the system installed llama.cpp of the `TEMPLATE_APP_LLAMACPP_MIN_VERSION` version or a newer one first (the `0.0.8751` one, the oldest loading the default Gemma 4 E4B model), the `libllama-dev` package of the Debian forky or the `misc/llama-cpp` one of the FreeBSD for example:

```
sudo apt install -y libllama-dev
```

The older llama.cpp gives way to the fetched one, and so do the builds older than the v0.x releases of the llama.cpp, since their version file is no one the CMake reads: the `llama-cpp-devel` package of the Fedora 44 and the `libllama-dev` one of the Ubuntu 26.04 among them. The `TEMPLATE_APP_LLAMACPP_ARCHIVE` release sources archive (the one of the `v0.7.0` llama.cpp by default) gets fetched through the Internet then, checked against the `TEMPLATE_APP_LLAMACPP_ARCHIVE_SHA256` checksum and built. Both ways provide the very same `llama` target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} llama)
```

The fetched sources build the [ggml](https://github.com/ggml-org/ggml) tensor library for the CPU of the building machine, so pass the `-DGGML_NATIVE=OFF` option to the build meant to run on the other machines too (the flatpak and the snap packagers of the branch do it). The tensor kernels of a Debug build take minutes for a single answer, so the fetched llama.cpp gets the `TEMPLATE_APP_LLAMACPP_BUILD_TYPE` build type (the `Release` one by default), while the project keeps it's own one.

### The model

The llama.cpp runs a language model of the [GGUF](https://huggingface.co/docs/hub/gguf) format, which is no part of the build, so the configure downloads the `TEMPLATE_APP_LLAMACPP_MODEL` one, checking it's SHA256 checksum. Both models are the multilingual [Gemma 4](https://deepmind.google/models/gemma/) instruction tuned ones of the Google of the Apache 2.0 license, quantized to the 4 bits with the quantization aware training, so they answer in the English, the Ukrainian and the other languages:

| Model | The GGUF file | Fits |
| --- | --- | --- |
| `gemma-4-E4B` (the default one) | the [gemma-4-E4B_q4_0-it.gguf](https://huggingface.co/google/gemma-4-E4B-it-qat-q4_0-gguf) one of 5.2 GB | the machines of 8 GB of RAM, taking some 5 GB of it while answering |
| `gemma-4-12B` | the [gemma-4-12b-it-qat-q4_0.gguf](https://huggingface.co/google/gemma-4-12B-it-qat-q4_0-gguf) one of 7 GB | the machines of 16 GB of RAM, taking some 8 GB of it while answering, which it does better while more than twice as slow |

Pick the bigger model with the `TEMPLATE_APP_LLAMACPP_MODEL` variable:

```
cmake -S . -B build -DTEMPLATE_APP_LLAMACPP_MODEL=gemma-4-12B
```

| Variable | What it holds |
| --- | --- |
| `TEMPLATE_APP_LLAMACPP_MODEL` | the model to download, the `gemma-4-E4B` or the `gemma-4-12B` one |
| `ENABLE_LLAMACPP_MODEL_DOWNLOAD` | downloads the model while configuring, `ON` by default |
| `TEMPLATE_APP_LLAMACPP_MODELS_DIR` | the directory the model is downloaded into, the `build/models` one of the source tree by default |
| `PROJECT_LLAMACPP_MODEL_PATH` | the model the application loads while the `--model` (or `-m`) command line parameter gives none, the downloaded one if empty, so nothing gets downloaded once it is given |

The download of gigabytes takes a while, so the models directory stays out of the build directories, which the `scripts/build` scripts erase on every configure: all the build directories of the source tree share a single download, while the other source trees share it with the `TEMPLATE_APP_LLAMACPP_MODELS_DIR` variable pointing at the same directory. The download goes into a `.part` file first, so an interrupted one is never taken for the model, while a failed one only warns, leaving the `--model` parameter the way to give the model. Any other GGUF model of a chat template the controller knows runs as well (the Qwen, the Llama, the Mistral, the Phi and the rest of the [llama.cpp built in templates](https://github.com/ggml-org/llama.cpp/wiki/Templates-supported-by-llama_chat_apply_template)), so download one by hand and point at it:

```
./src/CppAppTemplate --model /path/to/Qwen3-8B-Q4_K_M.gguf
```

### The components

The [src/LlamaCPP](/src/LlamaCPP) directory holds the classes of the `llamacppi` namespace:

| Class | What it does |
| --- | --- |
| `LlamaCPPController` | loads the GGUF model and answers the questions of the conversation piece by piece |
| `ChatTemplate` | the interface of the chat templates, which turn the conversation into the prompt of the model, the `create` call picks the one of the model |
| `BuiltinChatTemplate` | formats the conversation with the built in templates of the llama.cpp, which tells the one of the model by the markers of it's Jinja template |
| `Gemma4ChatTemplate` | formats the turns of the Gemma 4 models, which no built in template of the llama.cpp knows, closing the thought channel of the answer in advance for the bigger models the way their own template does |

The `init` call of the `llamacppi::LlamaCPPController` class of the [src/LlamaCPP/LlamaCPPController.h](/src/LlamaCPP/LlamaCPPController.h) file loads the model, while the `ask` one answers the next question of the conversation, handing every piece of the answer over to the given handler as soon as the model generates it. The handler stops the answer by returning `false`:

```
bool print(const std::string& piece)
{
  std::cout << piece << std::flush;
  return true;
}

auto llama = llamacppi::LlamaCPPController::create();

if (llama->init("build/models/gemma-4-E4B_q4_0-it.gguf")) {
  llama->ask("What is the capital of Ukraine?", print);
}
```

The model answers every question in the context of the previous questions and answers, while the context of the model keeps their evaluated tokens, so a question evaluates the tokens of it's own alone. The context holds up to 8192 tokens (the `CONTEXT_SIZE` constant of the controller), the quarter of which stays free for the answer, so the oldest questions with their answers get forgotten once the conversation outgrows it. The answer is generated by the half of the hardware threads, which the memory bandwidth limits to the pace of all of them, while the evaluation of the prompt takes all of them. The `TOP_K`, `TOP_P`, `MIN_P` and `TEMPERATURE` constants tune the sampling of the next token. The llama.cpp and the ggml messages go into the project log: the errors and the warnings at their own levels, the info ones at the debug level and the rest at the trace one, so raise the `MAX_LOG_LEVEL` CMake variable to see them.

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file prints the answer to the question of the `--question` (or `-q`) command line parameter, or answers the questions typed line by line into the standard input till it's end (the Ctrl+D keys), while the Ctrl+C keys stop the answer being printed, so replace them with your own questions.

### The tests

The `UTEST_LlamaCPPController` test, the ones of the chat templates and the `CTEST_LlamaCPPController` one run the real llama.cpp with the tiny model of the [TinyStories](https://huggingface.co/datasets/roneneldan/TinyStories) of a megabyte (the one of the llama.cpp own tests), which the configure of the tests downloads, so they prove the whole chain with no model of gigabytes. The `CTEST_LlamaCPPController` test also asks the downloaded `PROJECT_LLAMACPP_MODEL_PATH` model the English and the Ukrainian questions and checks it remembers the conversation. The test cases needing an unavailable model skip themselves. The `valgrind` and the `callgrind` targets run the executable with no parameters, so it loads the model under the tool for minutes and chats over the standard input afterwards: type a question or press the Ctrl+D keys.

### Packaging

The DEB package depends on the system llama.cpp and ggml packages the executable links against through the `dpkg-shlibdeps` tool, while the fetched llama.cpp gets linked into the executable statically and installs nothing, so the packages built without the system one carry the executable alone, with no files to clash with the ggml packages of the distribution. The flatpak builds the llama.cpp out of it's sources first, while the snap fetches it through the enabler. No package carries a model and the flatpak and the snap builds download none, so pass one with the `--model` parameter: the flatpak reads it from the home directory.
