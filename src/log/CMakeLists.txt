cmake_minimum_required(VERSION 3.13)

# The LOG4CPP::log4cpp target comes from the log4cpp enabler.
target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE LOG4CPP::log4cpp
)

add_subdirectory(log4cpp5-init)

add_subdirectory(tests)
