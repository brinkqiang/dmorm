cmake_minimum_required(VERSION 2.8)

PROJECT(dmorm)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

ModuleImport("dmformat" "thirdparty/dmformat")
ModuleImport("dmgen4pborm" "thirdparty/dmgen4pborm")
ModuleImport("dmlibgo" "thirdparty/dmlibgo")
ModuleImport2("mysql" "thirdparty/mysql")

IF (WIN32)

    ExeImport("test" "libmysql;libprotoc;libprotobuf-lite;libgo_static")
    ADD_CUSTOM_COMMAND(
    TARGET dmormtest
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mysql/lib/libmysql.dll
    $<TARGET_FILE_DIR:dmormtest>
    )
ELSE(WIN32)
    set(Boost_USE_STATIC_LIBS ON)
    find_package(Boost REQUIRED COMPONENTS context)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})

    ExeImport("test" "${MYSQL_LIBRARIES};libprotoc;libprotobuf-lite;libgo_static")
ENDIF(WIN32)
