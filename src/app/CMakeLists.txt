cmake_minimum_required(VERSION 3.22.1)

target_sources(
  ${PROJECT_NAME}
  PRIVATE ApplicationContext.cpp
  PRIVATE Application.cpp
  PRIVATE ApplicationFactory.cpp
  PRIVATE ApplicationHelpPrinter.cpp
  PRIVATE CommandLineParser.cpp
  PRIVATE ApplicationVersionPrinter.cpp
)
