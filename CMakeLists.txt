cmake_minimum_required(VERSION 2.6)
project(Space_invador)
add_definitions(-Wall -Wextra)
SET(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

if(${MINGW})
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
        SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DWINFOIREU")
    endif()
endif(${MINGW})

if(${CMAKE_COMPILER_IS_GNUCXX})
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
endif(${CMAKE_COMPILER_IS_GNUCXX})

if(${MSVC})
    message(FATAL_ERROR "Compilateur non supporté")
endif(${MSVC})

SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDB")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Os -s")

set(HEADERS pugixml/src/pugixml.hpp pugixml/src/pugiconfig.hpp)
set(SOURCES ${HEADERS} pugixml/src/pugixml.cpp)

add_library(pugixml STATIC ${SOURCES})
set_target_properties(pugixml PROPERTIES VERSION 1.2 SOVERSION 1.2)

find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)
if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML non trouvée")
endif(NOT SFML_FOUND)

include_directories(${SFML_INCLUDE_DIR})

file(
    GLOB_RECURSE
    client_files
    src/client/*.cpp
    include/client/*.hpp
    include/pugixml.hpp
    include/config.hpp
    include/fonctionsUtiles.hpp
    src/fonctionsUtiles.cpp
)

file(
    GLOB_RECURSE
    server_file
    src/serveur/*.cpp
    include/serveur/*.hpp
    include/pugixml.hpp
    include/config.hpp
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    message(STATUS "Doxygen found")
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} doxygen.conf)
endif(DOXYGEN_FOUND)

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${client_files})
else(WIN32)
    add_executable(${PROJECT_NAME} ${client_files})
endif(WIN32)
add_dependencies(${PROJECT_NAME} pugixml)

target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/libpugixml.a  ${SFML_LIBRARIES})

add_executable(serveur ${server_file})
target_link_libraries(serveur ${CMAKE_BINARY_DIR}/libpugixml.a ${SFML_LIBRARIES})


