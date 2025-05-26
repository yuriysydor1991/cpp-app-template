cmake_minimum_required(VERSION 3.13)

include(template-project-MySQLCppConn)

target_sources(
  ${PROJECT_BINARY_NAME}
  PRIVATE ApplicationContext.cpp
  PRIVATE Application.cpp
  PRIVATE ApplicationFactory.cpp
  PRIVATE ApplicationHelpPrinter.cpp
  PRIVATE CommandLineParser.cpp
  PRIVATE ApplicationVersionPrinter.cpp
)

target_include_directories(
  ${PROJECT_BINARY_NAME} 
  PRIVATE ${MySQL_INCLUDE_DIRS}
)

add_subdirectory(tests)
