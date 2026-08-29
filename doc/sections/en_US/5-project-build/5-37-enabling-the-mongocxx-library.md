## Enabling the MongoDB C++ driver

The [MongoDB C++ driver](https://www.mongodb.com/docs/languages/cpp/) carries the whole database access of the `appMongoDBCpp4` branch, so the `ENABLE_MONGOCXX` CMake variable is an `ON` one by default and the build needs no extra parameter for it:

```
# Inside the source root directory

cmake -S . -B build
cmake --build build --target all
```

The [cmake/enablers/template-project-mongocxx-enabler.cmake](/cmake/enablers/template-project-mongocxx-enabler.cmake) module probes the system installation with a single `find_package(mongocxx)` call, since the package configuration file of the driver pulls the bsoncxx and the MongoDB C driver ones by find_dependency calls of it's own. When no system installation is found the sources of the `TEMPLATE_APP_MONGOCXX_GIT_TAG` tag get fetched from the `TEMPLATE_APP_MONGOCXX_GIT` repository instead, and those sources download and build the MongoDB C driver as well when the system carries no `bson` and `mongoc` packages either, so a host with no [MongoDB development packages](/doc/sections/en_US/3-requirements/3-11-required-packages-for-the-MongoDB-connection.md) installed still configures and builds. Such a first configure and build takes the time of the whole driver stack, so keep the C driver packages installed to shorten it.

Both of the paths provide the very same `mongo::mongocxx_shared` and `mongo::bsoncxx_shared` targets, so link them to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} mongo::mongocxx_shared mongo::bsoncxx_shared)
```

The [src/mongodbcxx/CMakeLists.txt](/src/mongodbcxx/CMakeLists.txt) module links them to the project executable and to the `TemplateMongoDBCppConnObj` object library, the way the [helpers](/src/mongodbcxx/helpers/CMakeLists.txt) and the [converters](/src/mongodbcxx/converters/CMakeLists.txt) ones do for their own object libraries, so the sources of every component see the driver headers of both of the paths.

An `OFF` value leaves the branch with no driver to link at all, so set it only along with the replacement of the MongoDB component by an own one.
