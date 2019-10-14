cmake_minimum_required(VERSION 2.8)

PROJECT(dmgen4pborm)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

ADD_DEFINITIONS(-DCTEMPLATE_DLL_DECL=)

ModuleInclude("dmprotobuf" "thirdparty/dmprotobuf")

ModuleImport("ctemplate" "thirdparty/ctemplate")
ModuleImport("dmprotobuf" "thirdparty/dmprotobuf")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/test)

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

IF (WIN32)
    ADD_CUSTOM_TARGET(
        dmgen4pborm_config
        COMMAND echo "dmgen4pborm_config"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
ELSEIF (APPLE)
    ADD_CUSTOM_TARGET(
        dmgen4pborm_config
        COMMAND glibtoolize && aclocal && autoheader && autoconf && automake --add-missing && sh configure
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
ELSEIF (UNIX)
    ADD_CUSTOM_TARGET(
        dmgen4pborm_config
        COMMAND libtoolize && aclocal && autoheader && autoconf && automake --add-missing && sh configure
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
ENDIF()

ADD_DEPENDENCIES(dmgen4pborm dmgen4pborm_config)
