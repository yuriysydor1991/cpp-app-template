cmake_minimum_required(VERSION 3.13)

target_sources(
  ${PROJECT_BINARY_NAME}
  PRIVATE ContinueSignalsHandler.cpp
  PRIVATE IgnoredSignalsHandler.cpp
  PRIVATE PauseSignalsHandler.cpp
  PRIVATE PosixSignalsHandler.cpp
  PRIVATE ReloadSignalsHandler.cpp
  PRIVATE StopSignalsHandler.cpp
  PRIVATE UserSignalsHandler.cpp
)

add_subdirectory(tests)
