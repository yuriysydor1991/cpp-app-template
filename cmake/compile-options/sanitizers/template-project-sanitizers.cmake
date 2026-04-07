cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/sanitizers")

if (ENABLE_SANITIZERS)
  include(template-project-sanitizers-leak-and-address)
endif()

if (ENABLE_SANITIZERS_THREADS)
  include(template-project-sanitizers-threads)
endif()
