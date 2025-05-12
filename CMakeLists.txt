cmake_minimum_required(VERSION 3.21)

PROJECT(dmorm)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

ModuleImport("dmflags" "thirdparty/dmflags")
ModuleImport("dmformat" "thirdparty/dmformat")
ModuleImport("dmprotobuf" "thirdparty/dmprotobuf")
ModuleImport2("mysql" "thirdparty/mysql")

IF (WIN32)

    ExeImport("test" "libmysql;libprotoc;libprotobuf-lite;dmflags")
    ADD_CUSTOM_COMMAND(
    TARGET dmormtest
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mysql/lib/libmysql.dll
    $<TARGET_FILE_DIR:dmormtest>
    )
ELSE(WIN32)
    #if (NOT Boost_FOUND)
        #find_package(Boost REQUIRED thread system date_time chrono regex)
        #if (Boost_FOUND)
        #    include_directories(${Boost_INCLUDE_DIRS})
        #    link_directories(${Boost_LIBRARY_DIRS})
        #endif()
    #endif()

    ExeImport("test" "${MYSQL_LIBRARIES};libprotoc;libprotobuf-lite;dmflags")
ENDIF(WIN32)
