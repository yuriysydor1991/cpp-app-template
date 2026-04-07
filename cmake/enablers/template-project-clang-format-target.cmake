cmake_minimum_required(VERSION 3.13)

find_program(
  CLANG_FORMAT_EXEC
  clang-format
)

message(STATUS "clang-format command found: " ${CLANG_FORMAT_EXEC})

if (NOT CLANG_FORMAT_EXEC)
  message(
    WARNING
    "No clang-format executable or style file found. No code formatting target defined."
  )
  return()
endif()

add_custom_target (
  clang-format
  COMMAND ${CLANG_FORMAT_EXEC} -style=file:'./misc/.clang-format' --verbose -i ${ALLSOURCES}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
