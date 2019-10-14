cmake_minimum_required(VERSION 3.2)

PROJECT(dmtemplate)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

SET(CTEMPLATE_VERSION_MAJOR "1")
SET(CTEMPLATE_VERSION_MINOR "0")
SET(CTEMPLATE_VERSION_PATCH "1")
SET(CTEMPLATE_VERSION "${CTEMPLATE_VERSION_MAJOR}.${CTEMPLATE_VERSION_MINOR}.${CTEMPLATE_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${CTEMPLATE_VERSION}")

ADD_DEFINITIONS(-DUSE_CTEMPLATE)
ADD_DEFINITIONS(-DCTEMPLATE_DLL_DECL=)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)

IF (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/windows)
ENDIF(WIN32)

FILE(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/base/arena.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/htmlparser/htmlparser.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/htmlparser/jsparser.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/htmlparser/statemachine.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/src/diff_tpl_auto_escape.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/make_tpl_varnames_h.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/per_expand_data.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/src/template.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/template_annotator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/template_cache.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/template_dictionary.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/template_modifiers.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/src/template_namelist.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/template_pathops.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/template_string.cc
)

IF (WIN32)
    LIST(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/windows/template_port.cc)
ENDIF(WIN32)

IF (WIN32)
    ADD_CUSTOM_TARGET(
        dmtemplate_config
        COMMAND echo "dmtemplate_config"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
ELSEIF (APPLE)
    ADD_CUSTOM_TARGET(
        dmtemplate_config
        COMMAND glibtoolize && aclocal && autoheader && autoconf && automake --add-missing && sh configure
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
ELSEIF (UNIX)
    ADD_CUSTOM_TARGET(
        dmtemplate_config
        COMMAND libtoolize && aclocal && autoheader && autoconf && automake --add-missing && sh configure
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
ENDIF()

ADD_LIBRARY(dmtemplate ${SOURCES})
ADD_DEPENDENCIES(dmtemplate dmtemplate_config)
