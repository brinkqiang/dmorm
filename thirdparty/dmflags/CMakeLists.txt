cmake_minimum_required(VERSION 3.2)

PROJECT(dmflags)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

ADD_DEFINITIONS(-DGFLAGS_DLL_DECL=)

include (CheckTypeSize)
include (CheckIncludeFileCXX)
include (CheckCXXSymbolExists)

macro (bool_to_int VAR)
  if (${VAR})
    set (${VAR} 1)
  else ()
    set (${VAR} 0)
  endif ()
endmacro ()

set(NAMESPACE "google")
set(ns "${NAMESPACE}")
set(GFLAGS_NAMESPACE "${NAMESPACE}")
set(GFLAGS_IS_A_DLL "0")
set (GFLAGS_INTTYPES_FORMAT "${INTTYPES_FORMAT}")
set (GFLAGS_INTTYPES_FORMAT_C99 0)
set (GFLAGS_INTTYPES_FORMAT_BSD 0)
set (GFLAGS_INTTYPES_FORMAT_VC7 0)
set ("GFLAGS_INTTYPES_FORMAT_${INTTYPES_FORMAT}" 1)

if (WIN32 AND NOT CYGWIN)
  set (OS_WINDOWS 1)
else ()
  set (OS_WINDOWS 0)
  set (HAVE_PTHREAD 1)
endif ()

if (OS_WINDOWS)
  set (SLASH "\\\\")
else ()
  set (SLASH "/")
endif ()

if (MSVC)
  set (HAVE_SYS_TYPES_H 1)
  set (HAVE_STDDEF_H    1) # used by CheckTypeSize module
  set (HAVE_UNISTD_H    0)
  set (HAVE_SYS_STAT_H  1)
  set (HAVE_SHLWAPI_H   1)
  if (MSVC_VERSION VERSION_LESS 1600)
    check_include_file_cxx ("stdint.h" HAVE_STDINT_H)
    bool_to_int (HAVE_STDINT_H)  # used in #if directive
  else ()
    set (HAVE_STDINT_H 1)
  endif ()
  if (MSVC_VERSION VERSION_LESS 1800)
    check_include_file_cxx ("inttypes.h" HAVE_INTTYPES_H)
    bool_to_int (HAVE_INTTYPES_H)  # used in #if directive
  else ()
    set (HAVE_INTTYPES_H 1)
  endif ()
else ()
  foreach (fname IN ITEMS unistd stdint inttypes sys/types sys/stat fnmatch)
    string (TOUPPER "${fname}" FNAME)
    string (REPLACE "/" "_" FNAME "${FNAME}")
    if (NOT HAVE_${FNAME}_H)
      check_include_file_cxx ("${fname}.h" HAVE_${FNAME}_H)
    endif ()
  endforeach ()
  if (NOT HAVE_FNMATCH_H AND OS_WINDOWS)
    check_include_file_cxx ("shlwapi.h" HAVE_SHLWAPI_H)
  endif ()
  # the following are used in #if directives not #ifdef
  bool_to_int (HAVE_STDINT_H)
  bool_to_int (HAVE_SYS_TYPES_H)
  bool_to_int (HAVE_INTTYPES_H)
endif ()

if (GFLAGS_NAMESPACE_SECONDARY)
  set (INCLUDE_GFLAGS_NS_H "// Import gflags library symbols into alternative/deprecated namespace(s)")
  foreach (ns IN LISTS GFLAGS_NAMESPACE_SECONDARY)
    string (TOUPPER "${ns}" NS)
    set (gflags_ns_h "${PROJECT_BINARY_DIR}/include/${GFLAGS_INCLUDE_DIR}/gflags_${ns}.h")
    configure_file ("${PROJECT_SOURCE_DIR}/src/gflags_ns.h.in" "${gflags_ns_h}" @ONLY)
    list (APPEND PUBLIC_HDRS "${gflags_ns_h}")
    set (INCLUDE_GFLAGS_NS_H "${INCLUDE_GFLAGS_NS_H}\n#include \"gflags_${ns}.h\"")
  endforeach ()
else ()
  set (INCLUDE_GFLAGS_NS_H)
endif ()

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/src/defines.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/defines.h")
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/src/gflags_completions.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/gflags_completions.h")
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/src/gflags_declare.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/gflags_declare.h")
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/src/gflags_ns.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/gflags_gflags.h")
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/src/gflags.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/gflags.h")

IF (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/windows)
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)

FILE(GLOB_RECURSE SOURCES 
${CMAKE_CURRENT_SOURCE_DIR}/src/gflags.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/gflags_reporting.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/gflags_completions.cc)

IF (WIN32)
    LIST(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/windows_port.cc)
ENDIF(WIN32)

ADD_LIBRARY(dmflags ${SOURCES})

FILE(GLOB_RECURSE SOURCES 
${CMAKE_CURRENT_SOURCE_DIR}/test/main.cc)

ADD_EXECUTABLE(dmflagstest ${SOURCES})
TARGET_LINK_LIBRARIES(dmflagstest dmflags)
