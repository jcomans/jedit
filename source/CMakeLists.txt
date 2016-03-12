project(jedit)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


add_subdirectory(${CMAKE_SOURCE_DIR}/external/scintilla)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

