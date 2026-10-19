### Starting the generated executable

If executable compiles and is present in the build directory start it in the terminal with path found from a previous subsection by a command:

```
# from the build dir
./src/CppAppTemplate
```

The `appLlamaCPP` branch executable loads the language model the configure has downloaded (the Gemma 4 E4B one by default) and prints the answer to the question of the `--question` (or `-q`) parameter, or answers the questions typed line by line into the standard input till the end of it (the Ctrl+D keys), printing every answer piece by piece as the model generates it. Point it at another GGUF model with the `--model` (or `-m`) parameter:

```
# from the build dir
./src/CppAppTemplate -q "What is the capital of Ukraine? Answer with a single word."
./src/CppAppTemplate --model models/gemma-4-12b-it-qat-q4_0.gguf
```

```
Kyiv
```

Once again, the `CppAppTemplate` is the **default** name of the project. Replace it with our own custom one if it was changed in the project's root `CMakeLists.txt` file (the `CMAKE_PROJECT_NAME` and/or `PROJECT_BINARY_NAME` variable).
