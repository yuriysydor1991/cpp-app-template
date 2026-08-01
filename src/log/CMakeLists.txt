cmake_minimum_required(VERSION 3.13)

# The FindBoost module is removed since the CMake 3.30.
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

# Looked up here and not in boost-log: the Boost::* imported targets are
# directory scoped and the tests subdirectory needs them too. The system
# component is gone since the Boost 1.90 (header only since the 1.69).
find_package(Boost REQUIRED COMPONENTS
  log
  log_setup
  thread
  filesystem
)

add_subdirectory(boost-log)

add_subdirectory(tests)
