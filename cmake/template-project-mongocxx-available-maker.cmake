cmake_minimum_required(VERSION 3.13)

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

if (NOT mongocxx_FOUND)
  set(TEMPLATE_APP_MONGOCXX_GIT "https://github.com/mongodb/mongo-cxx-driver.git")
  set(TEMPLATE_APP_MONGOCXX_GIT_TAG "r4.1.0")

  FetchContent_Declare(
    mongocxx
    GIT_REPOSITORY ${TEMPLATE_APP_MONGOCXX_GIT}
    GIT_TAG        ${TEMPLATE_APP_MONGOCXX_GIT_TAG}
  )

  FetchContent_MakeAvailable(mongocxx)
endif()

get_target_property(MONGOCXX_INCLUDE_DIRS mongo::mongocxx_shared INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(BSONCXX_INCLUDE_DIRS mongo::bsoncxx_shared INTERFACE_INCLUDE_DIRECTORIES)

message(STATUS "mongocxx include dirs: ${MONGOCXX_INCLUDE_DIRS}")
message(STATUS "bsoncxx include dirs: ${BSONCXX_INCLUDE_DIRS}")
