project(jedit)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.50 COMPONENTS program_options)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

include_directories(${BOOST_INCLUDE_DIR} ${CURSES_INCLUDE_DIR})

set(jedit_SRC
  main.cpp
  )

add_executable(jedit ${jedit_SRC})

target_link_libraries(jedit
  ${Boost_LIBRARIES}
  ${CURSES_LIBRARIES}
  )
