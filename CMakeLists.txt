cmake_minimum_required(VERSION 2.8)

PROJECT(dmorm)

IF (WIN32)  
    MESSAGE(STATUS "Now is windows")

    SET(DMOS_NAME "win")

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )    
ELSEIF (APPLE)  
    MESSAGE(STATUS "Now is Apple systems")  

    SET(DMOS_NAME "mac") 

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )
ELSEIF (UNIX)  
    MESSAGE(STATUS "Now is UNIX-like OS")  
 
    SET(DMOS_NAME "lin") 
    
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )    
ENDIF ()

ADD_SUBDIRECTORY(thirdparty/dmgen4pborm)

IF (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/dmgen4pborm/thirdparty/dmprotobuf/src/windows)
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/dmgen4pborm/thirdparty/dmprotobuf/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/dmgen4pborm/thirdparty/dmprotobuf)

IF (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mysql-win/include/mysql)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mysql-win/include)

    LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mysql-win/lib)
ELSE(WIN32)
    INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/FindMYSQL.cmake)
    INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIRS})
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

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
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mysql-win/lib/libmysql.dll
	$<TARGET_FILE_DIR:dmormtest>
    )
ELSE(WIN32)
    ADD_EXECUTABLE(dmormtest ${DMORMTEST_SOURCES})
    TARGET_LINK_LIBRARIES(dmormtest ${MYSQL_LIBRARIES} libprotoc libprotobuf-lite)
ENDIF(WIN32)
