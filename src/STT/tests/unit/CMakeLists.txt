cmake_minimum_required(VERSION 3.13)

# disabling the asserts for the tests
add_compile_options(-DNDEBUG=1)

add_subdirectory(Microphone)
add_subdirectory(SpeechListener)
add_subdirectory(UtteranceDetector)
