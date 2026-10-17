cmake_minimum_required(VERSION 3.13)

# The WinUI 3 initialization/orchestration object. It is WinUI free (it only
# talks to the run_winui_application() seam), so it builds and is tested on every
# platform; the actual Windows App SDK dependent code lives in the app and
# main-window subdirectories and only compiles on Windows.
add_library(
  ${WINUI3_OBJECT_NAME} OBJECT
  WinUI3Controller.cpp
)

target_include_directories(
  ${WINUI3_OBJECT_NAME}
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${WINUI3_OBJECT_NAME}
)

add_subdirectory(helpers)
add_subdirectory(app)

# The native WinUI 3 main window only exists on Windows (and only when the
# Windows App SDK is available); off Windows the app subdirectory builds a stub
# launch seam instead.
if(WIN32 AND TARGET winui3::sdk)
  add_subdirectory(main-window)

  # The Windows App SDK bootstrapper DLL is loaded from the executable directory.
  add_custom_command(
    TARGET ${PROJECT_BINARY_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${WINUI3_BOOTSTRAP_DLL}"
            "$<TARGET_FILE_DIR:${PROJECT_BINARY_NAME}>"
  )

  install(
    FILES "${WINUI3_BOOTSTRAP_DLL}"
    DESTINATION ${PROJECT_BINARY_INSTALLATION_DIR}
  )
endif()

add_subdirectory(tests)
