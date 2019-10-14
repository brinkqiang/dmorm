cmake_minimum_required(VERSION 2.8)

PROJECT(dmgen4pborm)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

ADD_DEFINITIONS(-DCTEMPLATE_DLL_DECL=)

ModuleInclude("dmprotobuf" "thirdparty/dmprotobuf")

ModuleImport("dmtemplate" "thirdparty/dmtemplate")
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
TARGET_LINK_LIBRARIES(dmgen4pborm dmtemplate libprotoc libprotobuf-lite)

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
