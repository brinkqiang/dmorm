cmake_minimum_required(VERSION 2.8)

PROJECT(ctemplate)

ADD_DEFINITIONS(-DCTEMPLATE_DLL_DECL=)

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

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
    LIST(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/windows/port.cc)
ENDIF(WIN32)

ADD_LIBRARY(ctemplate ${SOURCES})
