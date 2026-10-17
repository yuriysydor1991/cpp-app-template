cmake_minimum_required(VERSION 3.13)

# Boost.System is header only since the 1.69 release, so the modern Boost
# packages ship no CMake target of it's own for it, while the older ones
# still need it linked. Hence the optional request and the guarded link
# below.
# The Beast and the Asio are header only, while their threads need the OS
# threads library linked (the FreeBSD one isn't part of its libc).
find_package(Boost REQUIRED OPTIONAL_COMPONENTS system)
find_package(Threads REQUIRED)

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

# The PUBLIC keyword hands the Boost headers over to the sources above and the
# Boost libraries over to the executable which links this object library. The
# FreeBSD compiler doesn't search the /usr/local/include the packages install
# the headers into on its own.
target_link_libraries(
  TemplateBoostBeastObj
  PUBLIC Boost::boost Threads::Threads
)

if (TARGET Boost::system)
  target_link_libraries(TemplateBoostBeastObj PUBLIC Boost::system)
endif()

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateBoostBeastObj
)

add_subdirectory(rhandlers)
add_subdirectory(pages)
add_subdirectory(tests)
