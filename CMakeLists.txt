# The minimum version required to use Qt5 is CMake 2.8.3, but 2.8.11 is recommended.
cmake_minimum_required(VERSION 2.8.11)

project(KeyDetection)
set(AppName KeyDetection)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
message(STATUS "Output path: ${EXECUTABLE_OUTPUT_PATH}")

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/include)
		
file(GLOB app_header "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

file(GLOB app_src "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*")

set(SRC ${app_src} ${app_header})

add_executable(${AppName} ${SRC})
