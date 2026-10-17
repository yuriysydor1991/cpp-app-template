cmake_minimum_required(VERSION 3.13)

# The gettext is a hard requirement of this branch rather than an optional
# integration, since the whole src/gettext example is built around it.
if (NOT ENABLE_GETTEXT)
  message(
    FATAL_ERROR
    "The src/gettext sources require the gettext library which is turned off by "
    "the ENABLE_GETTEXT=OFF parameter. Drop the add_subdirectory(gettext) call from the "
    "src/CMakeLists.txt file together with the whole src/gettext subdirectory "
    "and its usage of the src/app/applications/Application.cpp file to build "
    "the project without it."
  )
endif()

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
