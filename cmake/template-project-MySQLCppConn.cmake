cmake_minimum_required(VERSION 3.13)

set(MySQL_INCLUDE_DIRS "/usr/include/cppconn" CACHE STRING "The MySQLCppConn includes path")
set(MySQL_LIBRARIES "mysqlcppconn" CACHE STRING "The MySQLCppConn libraries")

# doesn't work
find_package(MySQL COMPONENTS ConnectorCpp)
