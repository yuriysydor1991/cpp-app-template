cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectGettextControllerObj OBJECT
  CatalogsLocator.cpp
  GettextController.cpp
)

target_include_directories(
  TemplateProjectGettextControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The libintl is made available by the gettext enabler. The PUBLIC keyword
# hands its headers over to the sources above and to the executable ones which
# include the tr.h header, and its library over to the executable which links
# this object library.
target_link_libraries(
  TemplateProjectGettextControllerObj
  PUBLIC Intl::Intl
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectGettextControllerObj
)

# The executable started from the build tree translates with the catalogs the
# enabler compiles there, so they are built together with it.
add_dependencies(${PROJECT_BINARY_NAME} gettext-catalogs)

add_subdirectory(tests)
