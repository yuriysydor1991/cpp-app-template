cmake_minimum_required(VERSION 3.13)

include(template-project-compile-options)
add_compile_options(${EXTRA_COMPILE_OPTIONS})
add_link_options(${EXTRA_LINK_OPTIONS})

add_executable(
  ${PROJECT_BINARY_NAME}
  main.cpp
)

# On macOS the executable is produced as a .app bundle so it behaves as a proper
# Cocoa GUI application and can be packaged as a .dmg / .pkg.
if(APPLE)
  set_target_properties(
    ${PROJECT_BINARY_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}"
    MACOSX_BUNDLE_GUI_IDENTIFIER "ua.org.kytok.template.${PROJECT_BINARY_NAME_lower}"
    MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
  )
endif()

target_include_directories(
  ${PROJECT_BINARY_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

install(
  TARGETS ${PROJECT_BINARY_NAME}
  RUNTIME DESTINATION ${PROJECT_BINARY_INSTALLATION_DIR}
  BUNDLE DESTINATION ${PROJECT_BINARY_INSTALLATION_DIR}
)

configure_file(
  project-global-decls.h.in
  ${CMAKE_BINARY_DIR}/project-global-decls.h
)

add_subdirectory(app)
add_subdirectory(log)
add_subdirectory(cocoa)
