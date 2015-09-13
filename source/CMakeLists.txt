project(jedit)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_definitions(--std=c++11 -Wall)

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs REQUIRED)

find_package(Boost 1.50 COMPONENTS program_options system python3)
find_package(Threads)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

include_directories(
  ${PYTHON_INCLUDE_DIRS}
  ${BOOST_INCLUDE_DIR} 
  ${CURSES_INCLUDE_DIR})

set(jedit_SRC
  src/main.cpp
  src/script_engine.cpp
  )

add_executable(jedit ${jedit_SRC})

target_link_libraries(jedit
  ${PYTHON_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CURSES_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  )
