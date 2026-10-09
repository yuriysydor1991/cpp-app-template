cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_GETTEXT
    "Enables the GNU gettext translations: links the libintl (a part of the glibc or the gettext-runtime package) and compiles the po directory translations with the gettext tools"
    ON
)

if (NOT ENABLE_GETTEXT)
    return()
endif()

find_package(Intl REQUIRED)
find_package(Gettext REQUIRED)
find_program(GETTEXT_XGETTEXT_EXECUTABLE xgettext)

# The Intl::Intl target comes with the FindIntl module of the CMake 3.20 and
# newer only, so the older ones get it out of the module variables. Its include
# directory matters on FreeBSD, whose base compiler searches no
# /usr/local/include directory the gettext-runtime package puts the libintl.h
# header into.
if (NOT TARGET Intl::Intl)
    add_library(Intl::Intl INTERFACE IMPORTED)
    set_target_properties(
        Intl::Intl PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${Intl_INCLUDE_DIRS}"
        INTERFACE_LINK_LIBRARIES "${Intl_LIBRARIES}"
    )
endif()

# The catalogs directories the gettexti::CatalogsLocator class looks into: the
# one relative to the installed executable, which the relocatable packages
# (e.g. the AppImage and the snap ones) keep wherever they are mounted to, the
# build tree one and the installation one.
get_filename_component(gettextBinDir "${PROJECT_BINARY_INSTALLATION_DIR}" ABSOLUTE BASE_DIR "${CMAKE_INSTALL_PREFIX}")
file(RELATIVE_PATH PROJECT_RELATIVE_LOCALE_DIR "${gettextBinDir}" "${CMAKE_INSTALL_FULL_LOCALEDIR}")
set(PROJECT_BUILD_LOCALE_DIR "${CMAKE_BINARY_DIR}/locale")
set(PROJECT_LOCALE_DIR "${CMAKE_INSTALL_FULL_LOCALEDIR}")

# Every po/<language>.po translation compiles into the
# <language>/LC_MESSAGES/<binary name>.mo catalog, so a new language needs a
# new po file alone.
file(GLOB TEMPLATE_PROJECT_GETTEXT_PO_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/po/*.po")

set(gettextPotFile "${CMAKE_BINARY_DIR}/po/${PROJECT_BINARY_NAME}.pot")
set(gettextCatalogs "")
set(gettextMergeCommands "")

foreach(poFile ${TEMPLATE_PROJECT_GETTEXT_PO_FILES})
    get_filename_component(language "${poFile}" NAME_WE)
    set(catalog "${PROJECT_BUILD_LOCALE_DIR}/${language}/LC_MESSAGES/${PROJECT_BINARY_NAME}.mo")

    add_custom_command(
        OUTPUT "${catalog}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BUILD_LOCALE_DIR}/${language}/LC_MESSAGES"
        COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} --check -o "${catalog}" "${poFile}"
        DEPENDS "${poFile}"
        COMMENT "Compiling the ${language} message catalog"
        VERBATIM
    )

    install(FILES "${catalog}" DESTINATION "${CMAKE_INSTALL_LOCALEDIR}/${language}/LC_MESSAGES")

    list(APPEND gettextCatalogs "${catalog}")
    list(APPEND gettextMergeCommands
        COMMAND ${GETTEXT_MSGMERGE_EXECUTABLE} --quiet --update --backup=none --previous "${poFile}" "${gettextPotFile}")
endforeach()

add_custom_target(gettext-catalogs ALL DEPENDS ${gettextCatalogs})

# The gettext-pot target extracts the messages of the gettexti::tr and the
# gettexti::trn calls of the sources (the tests aside) into the template a new
# translation starts with, while the gettext-update-po one merges the template
# into the po directory translations.
file(GLOB_RECURSE gettextSources CONFIGURE_DEPENDS RELATIVE "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.h")
list(FILTER gettextSources EXCLUDE REGEX "/tests/")

add_custom_target(
    gettext-pot
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/po"
    COMMAND ${GETTEXT_XGETTEXT_EXECUTABLE} --from-code=UTF-8 --language=C++
        --keyword=tr --keyword=trn:1,2 --add-comments=TRANSLATORS: --add-location=file
        --package-name=${CMAKE_PROJECT_NAME} --package-version=${PROJECT_VERSION}
        --msgid-bugs-address=${PROJECT_MAINTAINER_EMAIL} --output=${gettextPotFile}
        ${gettextSources}
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMENT "Extracting the translatable messages into the ${gettextPotFile} template"
    VERBATIM
)

add_custom_target(gettext-update-po ${gettextMergeCommands} VERBATIM)
add_dependencies(gettext-update-po gettext-pot)

message(STATUS "The gettext message catalogs: ${TEMPLATE_PROJECT_GETTEXT_PO_FILES}")

# Translate with the gettexti::tr and the gettexti::trn functions of the
# src/gettext/tr.h header and link the Intl::Intl target to your target(s) of
# interest, e.g.:
#   target_link_libraries(${PROJECT_BINARY_NAME} Intl::Intl)
