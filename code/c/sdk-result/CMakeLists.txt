cmake_minimum_required(VERSION 3.4)

project(sdk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -g -std=gnu++11")

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-DMSVC_VMG_ENABLED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /vmg")
endif(MSVC)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory("src")

if(ENABLE_TEST)
    add_subdirectory(test)
endif()
