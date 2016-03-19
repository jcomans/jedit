add_definitions(-DGTK -DPLAT_GTK=1)

set(CMAKE_C_FLAGS_RELEASE   "-DNDEBUG -Os -Wall -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} --std=c++11")

set(CMAKE_C_FLAGS_DEBUG   "-g -pg -Wall -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --std=c++11")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -pg")

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs REQUIRED)

find_package(Boost 1.50 COMPONENTS program_options system python3)
find_package(Threads)
find_package(GTK2)

include_directories(
  ${CMAKE_SOURCE_DIR}/external/scintilla/include
  ${GTK2_INCLUDE_DIRS}
  ${PYTHON_INCLUDE_DIRS}
  ${BOOST_INCLUDE_DIR} 
)

set(jedit_SRC
  jedit.cpp
  app.cpp
  editor.cpp
  buffer.cpp
  key_handler.cpp
  script_engine.cpp
  minibuffer.cpp
  gtk_gui.cpp
  )

add_executable(jedit ${jedit_SRC})

target_link_libraries(jedit
  scintilla
  ${GTK2_LIBRARIES}
  ${PYTHON_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_custom_command(TARGET jedit
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:jedit> ${CMAKE_BINARY_DIR})