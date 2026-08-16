cmake_minimum_required(VERSION 3.13)

# Boost.System is header only since the 1.69 release, so the modern Boost
# packages ship no CMake target of it's own for it, while the older ones
# still need it linked. Hence the optional request and the guarded link
# below.
find_package(Boost REQUIRED COMPONENTS thread OPTIONAL_COMPONENTS system)

add_library(
  TemplateBoostBeastObj OBJECT
  HttpController.cpp
  HttpContext.cpp
)

target_include_directories(
  TemplateBoostBeastObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateBoostBeastObj
  Boost::thread
)

if (TARGET Boost::system)
  target_link_libraries(${PROJECT_BINARY_NAME} Boost::system)
endif()

add_subdirectory(rhandlers)
add_subdirectory(pages)
add_subdirectory(tests)
