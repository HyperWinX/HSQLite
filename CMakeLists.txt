cmake_minimum_required(VERSION 3.28)

project(HSQLite VERSION 1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(hsqlite INTERFACE)

find_package(SQLite3 REQUIRED)

target_include_directories(hsqlite
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(hsqlite INTERFACE SQLite::SQLite3)
