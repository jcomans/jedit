project(jedit)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_definitions(--std=c++11 -Wall)
add_definitions(-DGTK -DPLAT_GTK=1)

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs REQUIRED)

find_package(Boost 1.50 COMPONENTS program_options system python3)
find_package(Threads)
find_package(GTK2)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

include_directories(
  ${CMAKE_SOURCE_DIR}/external/scintilla/include
  ${GTK2_INCLUDE_DIRS}
  ${PYTHON_INCLUDE_DIRS}
  ${BOOST_INCLUDE_DIR} 
  ${CURSES_INCLUDE_DIR})

set(jedit_SRC
  src/jedit.cpp
  #src/main.cpp
  #src/ScintillaCore.cpp
  src/script_engine.cpp
  )

add_executable(jedit ${jedit_SRC})

target_link_libraries(jedit
  ${CMAKE_SOURCE_DIR}/lib/scintilla.a
  ${GTK2_LIBRARIES}
  ${PYTHON_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CURSES_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  )
