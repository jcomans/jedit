add_definitions(-DGTK -DPLAT_GTK=1)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS_RELEASE   "-DNDEBUG -Os -Wall -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

set(CMAKE_C_FLAGS_DEBUG   "-g -pg -Wall -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -pg")

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs REQUIRED)

set(BOOST_LIBRARYDIR /usr/lib/x86_64-linux-gnu)
find_package(Boost 1.50 REQUIRED COMPONENTS program_options system python3 log log_setup)
find_package(Threads)
find_package(GTK2)

add_definitions(-DBOOST_LOG_DYN_LINK)

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
  gui/gtk/gtk_gui.cpp
  python/buffer_module.cpp
  python/editor_module.cpp
  python/key_handler_module.cpp
  python/minibuffer_module.cpp
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

add_executable(asiotest asiotest.cpp)

target_link_libraries(asiotest
  scintilla
  ${GTK2_LIBRARIES}
  ${PYTHON_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_custom_command(TARGET asiotest
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:asiotest> ${CMAKE_BINARY_DIR})