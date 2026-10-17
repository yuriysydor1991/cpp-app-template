cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectDBusServerObjectsObj OBJECT
  CurrentDateServerObject.cpp
  DBusServerObjectFactory.cpp
)

target_include_directories(
  TemplateProjectDBusServerObjectsObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectDBusServerObjectsObj
  ${SDBUSCPP_LINK_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectDBusServerObjectsObj
)

add_subdirectory(tests)

# The session bus starts the server on the first call of its name with this
# activation file installed. The name is the CurrentDateServerObject one.
set(TEMPLATE_PROJECT_DBUS_SERVICE_NAME "org.cppapptemplate.SimpleServer")

configure_file(
  ${CMAKE_SOURCE_DIR}/misc/packagers/dbus/dbus-session-service.in
  ${CMAKE_BINARY_DIR}/${TEMPLATE_PROJECT_DBUS_SERVICE_NAME}.service
  @ONLY
)

install(
  FILES ${CMAKE_BINARY_DIR}/${TEMPLATE_PROJECT_DBUS_SERVICE_NAME}.service
  DESTINATION ${CMAKE_INSTALL_DATADIR}/dbus-1/services
)

