cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
  KeyDetection
  VERSION 0.1.0
  DESCRIPTION "Keyboard Detection Test"
  HOMEPAGE_URL "https://example.com/"
  LANGUAGES CXX)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)

# ---- Declare executable ----
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/key-detector/*.h*)
file(GLOB SRCS ${PROJECT_SOURCE_DIR}/source/key-detector/*.c*
     ${PROJECT_SOURCE_DIR}/source/main.cpp)

set(SOURCES ${HEADERS} ${SRCS})

add_executable(KeyDetection_exe ${SOURCES})
add_executable(KeyDetection::exe ALIAS KeyDetection_exe)
set_property(TARGET KeyDetection_exe PROPERTY OUTPUT_NAME KeyDetection)
target_compile_features(KeyDetection_exe PRIVATE cxx_std_17)

# ---- Install rules ----
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----
if(NOT KeyDetection_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING "Developer mode is intended for developers of KeyDetection")
endif()

include(cmake/dev-mode.cmake)
