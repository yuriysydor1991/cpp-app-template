cmake_minimum_required(VERSION 3.13)

# The Boost::* targets are looked up by the parent src/log/CMakeLists.txt.

add_library(
  TemplateBoostLogControllerObj OBJECT
  BoostLogController.cpp
)

target_include_directories(
  TemplateBoostLogControllerObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_compile_definitions(TemplateBoostLogControllerObj PRIVATE BOOST_LOG_DYN_LINK)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateBoostLogControllerObj
  Boost::log
  Boost::log_setup
  Boost::thread
  Boost::filesystem
  pthread
)
