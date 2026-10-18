cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_INJA
    "Enables the inja (Jinja2 like HTML templates) library for the web pages builders through system installed one or FetchContent by internet"
    OFF
)

if (NOT ENABLE_INJA)
    return()
endif()

set(TEMPLATE_APP_INJA_GIT "https://github.com/pantor/inja.git" CACHE STRING "The inja library git source repository")
set(TEMPLATE_APP_INJA_GIT_TAG "v3.5.0" CACHE STRING "The inja project git repository release tag of interest")

# The fetched inja builds no tests of it's own, installs nothing into the
# project packages and writes no user package registry entry. It takes the
# nlohmann JSON the ENABLE_NLOHMANN_JSON fetched, since the embedded copy of
# the inja would clash with that target name.
set(INJA_BUILD_TESTS OFF)
set(INJA_INSTALL OFF)
set(INJA_EXPORT OFF)

if (TARGET nlohmann_json)
  set(INJA_USE_EMBEDDED_JSON OFF)
endif()

template_project_default_3rdparty_enabler(
  NAME inja
  GIT_REPOSITORY ${TEMPLATE_APP_INJA_GIT}
  GIT_TAG ${TEMPLATE_APP_INJA_GIT_TAG}
)

# The fetched headers are marked as the system ones, so the strict project
# compile options raise no warnings of the inja (the imported ones already are).
if (TARGET inja)
  get_target_property(INJA_INCLUDE_DIRS inja INTERFACE_INCLUDE_DIRECTORIES)
  set_target_properties(inja PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${INJA_INCLUDE_DIRS}")
endif()

# The pages builders render the HTML templates, so they and their component
# tests get the inja (the executable gets it through the object library).
target_link_libraries(TemplatePagesBuildersObj PUBLIC pantor::inja)

if (TARGET CTEST_beasthttp)
  target_link_libraries(CTEST_beasthttp pantor::inja)
endif()
