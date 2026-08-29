cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_MONGOCXX
    "Enables the MongoDB C++ driver for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_MONGOCXX)
    return()
endif()

set(TEMPLATE_APP_MONGOCXX_GIT "https://github.com/mongodb/mongo-cxx-driver.git" CACHE STRING "The MongoDB C++ driver git source repository")
set(TEMPLATE_APP_MONGOCXX_GIT_TAG "r4.1.0" CACHE STRING "The MongoDB C++ driver git repository tag of interest")

# The mongocxx package configuration file pulls the bsoncxx and the MongoDB C
# driver ones by find_dependency calls of it's own, so the single probe below
# covers them all.
find_package(mongocxx QUIET)

if (mongocxx_FOUND)
    message(STATUS "System already contains the mongocxx ${mongocxx_VERSION} library")
else()
    # The tests setting of the C driver reaches the C++ driver one as well,
    # whose test targets download a whole test framework of their own, which
    # the project has no use for.
    set(ENABLE_TESTS OFF CACHE BOOL "Build the MongoDB driver test targets")

    # The fetched sources download and build the MongoDB C driver themselves
    # when the system carries no bson and mongoc packages.
    template_project_default_3rdparty_enabler(
      NAME mongocxx
      GIT_REPOSITORY ${TEMPLATE_APP_MONGOCXX_GIT}
      GIT_TAG ${TEMPLATE_APP_MONGOCXX_GIT_TAG}
      DISABLE_SYSTEM_PROBE
    )

    # The fetched sources declare the plain library targets, since the
    # namespaced names are written by their install step alone.
    add_library(mongo::bsoncxx_shared ALIAS bsoncxx_shared)
    add_library(mongo::mongocxx_shared ALIAS mongocxx_shared)
endif()

# Both of the paths above provide the very same mongo::mongocxx_shared and
# mongo::bsoncxx_shared targets, so link them to your target(s) of interest
# (e.g. the ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} mongo::mongocxx_shared mongo::bsoncxx_shared)
