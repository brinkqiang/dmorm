cmake_minimum_required(VERSION 2.8)

PROJECT(dmorm)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

ModuleImport("dmformat" "thirdparty/dmformat")
ModuleImport("dmgen4pborm" "thirdparty/dmgen4pborm")
ModuleImport2("mysql" "thirdparty/mysql")

FILE(GLOB DMORMTEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/person.pb.cc)

IF (WIN32)
    ADD_EXECUTABLE(dmormtest ${DMORMTEST_SOURCES})

    TARGET_LINK_LIBRARIES(dmormtest libmysql libprotoc libprotobuf-lite)

    ADD_CUSTOM_COMMAND(
    TARGET dmormtest
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mysql/lib/libmysql.dll
    $<TARGET_FILE_DIR:dmormtest>
    )
ELSE(WIN32)
    ADD_EXECUTABLE(dmormtest ${DMORMTEST_SOURCES})
    TARGET_LINK_LIBRARIES(dmormtest ${MYSQL_LIBRARIES} libprotoc libprotobuf-lite)
ENDIF(WIN32)
