cmake_minimum_required(VERSION 3.13)

# The darknetxx is made of this very template project, so it's headers include
# the headers of the project paths (src/log/log.h and the like). The adaptor
# sources take the darknetxx include directories before the project ones then,
# while the project sources never include the darknetxx headers. They are the
# 3rd-party headers, so the SYSTEM keyword keeps them out of the project
# warnings.
add_library(
  TemplateProjectDarknetXXObj OBJECT
  DarknetImage.cpp
  DarknetXXController.cpp
  Detection.cpp
  log/DefaultLogger.cpp
  weights/Dxxwjz1Weights.cpp
  weights/NetworkWeights.cpp
  weights/OrigWeights.cpp
)

target_include_directories(
  TemplateProjectDarknetXXObj
  SYSTEM PRIVATE ${DARKNETXX_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}
)

target_compile_definitions(
  TemplateProjectDarknetXXObj
  PRIVATE ${DARKNETXX_COMPILE_DEFINITIONS}
)

# The darknetxx core itself is made available by it's enabler. The PUBLIC
# keyword hands it's libraries over to the executable which links this object
# library.
target_link_libraries(
  TemplateProjectDarknetXXObj
  PUBLIC darknetxx
)

# The sink of the darknetxx log messages reaches the project logger, so it
# compiles with the project include directories alone.
add_library(
  TemplateProjectDarknetXXLogObj OBJECT
  log/DarknetXXLog.cpp
)

target_include_directories(
  TemplateProjectDarknetXXLogObj
  PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectDarknetXXObj
  TemplateProjectDarknetXXLogObj
)

add_subdirectory(tests)
