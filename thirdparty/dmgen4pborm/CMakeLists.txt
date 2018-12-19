cmake_minimum_required(VERSION 2.8)

PROJECT(dmgen4pborm)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

IF (WIN32)
    MESSAGE(STATUS "Now is windows")

    SET(DMOS_NAME "win")

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
    IF(MSVC)
        ADD_DEFINITIONS(/bigobj)
        ADD_COMPILE_OPTIONS(/W3 /wd4005 /wd4068 /wd4244 /wd4267 /wd4800)
        ADD_DEFINITIONS(/DNOMINMAX /DWIN32_LEAN_AND_MEAN=1 /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS)
        IF (MSVC_VERSION GREATER_EQUAL 1900)
            INCLUDE(CheckCXXCompilerFlag)
            CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
            IF (_cpp_latest_flag_supported)
                ADD_COMPILE_OPTIONS("/std:c++latest")
            ENDIF()
    	ENDIF()
    ENDIF()
ELSEIF (APPLE)
    MESSAGE(STATUS "Now is Apple systems")  

    SET(DMOS_NAME "mac") 

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS")  
 
    SET(DMOS_NAME "lin") 
    
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O2" )    
ENDIF ()

ADD_DEFINITIONS(-DCTEMPLATE_DLL_DECL=)

ADD_SUBDIRECTORY(thirdparty/ctemplate)
ADD_SUBDIRECTORY(thirdparty/dmprotobuf/cmake)

IF (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/ctemplate/src/windows)
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/ctemplate/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/ctemplate)

INCLUDE_DIRECTORIES(
  ${ZLIB_INCLUDE_DIRECTORIES}
  ${protobuf_BINARY_DIR}
  ${protobuf_source_dir}/src)

IF (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/dmprotobuf/src/windows)
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/dmprotobuf/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/dmprotobuf)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/test)

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

FILE(GLOB SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/tpl/*.h)

ADD_EXECUTABLE(dmgen4pborm ${SOURCES})
TARGET_LINK_LIBRARIES(dmgen4pborm ctemplate libprotoc libprotobuf-lite)

ADD_CUSTOM_COMMAND(
    TARGET dmgen4pborm
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/test/person.proto
    $<TARGET_FILE_DIR:dmgen4pborm>
)

ADD_CUSTOM_COMMAND(
    TARGET dmgen4pborm
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/test/build_person.sh
    $<TARGET_FILE_DIR:dmgen4pborm>
)

ADD_CUSTOM_COMMAND(
    TARGET dmgen4pborm
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/test/build_person.bat
    $<TARGET_FILE_DIR:dmgen4pborm>
)
