cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_BOX2D
    "Enables the Box2D (2D rigid body physics simulation) library for the project usage through system installed one or FetchContent by internet"
    OFF
)

if (NOT ENABLE_BOX2D)
    return()
endif()

set(TEMPLATE_APP_BOX2D_GIT "https://github.com/erincatto/box2d.git" CACHE STRING "The Box2D library git source repository")
set(TEMPLATE_APP_BOX2D_GIT_TAG "v3.1.1" CACHE STRING "The Box2D project git repository tag of interest")

template_project_default_3rdparty_enabler(
  NAME box2d
  GIT_REPOSITORY ${TEMPLATE_APP_BOX2D_GIT}
  GIT_TAG ${TEMPLATE_APP_BOX2D_GIT_TAG}
)

# Link the following Box2D target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - system install, via find_package(box2d): box2d::box2d
#   - FetchContent source build:               box2d::box2d
# For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} box2d::box2d)
