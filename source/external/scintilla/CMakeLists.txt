project(scintilla)
cmake_minimum_required(VERSION 2.8.0)

find_package(GTK2)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/gtk/
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/src/
  ${CMAKE_CURRENT_SOURCE_DIR}/lexlib/
  ${GTK2_INCLUDE_DIRS}
)

add_definitions(-DGTK -DSCI_LEXER)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS_RELEASE   "-DNDEBUG -Os -Wall -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

set(CMAKE_C_FLAGS_DEBUG   "-g -pg -Wall -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE}")

set(scintilla_SRC
  gtk/ScintillaGTK.cxx
  gtk/PlatGTK.cxx
  gtk/ScintillaGTKAccessible.cxx
  gtk/scintilla-marshal.c

  lexlib/LexerModule.cxx
  lexlib/LexerSimple.cxx
  lexlib/CharacterCategory.cxx
  lexlib/PropSetSimple.cxx
  lexlib/CharacterSet.cxx
  lexlib/LexerNoExceptions.cxx
  lexlib/Accessor.cxx
  lexlib/WordList.cxx
  lexlib/StyleContext.cxx
  lexlib/LexerBase.cxx

  src/CharClassify.cxx
  src/MarginView.cxx
  src/CaseConvert.cxx
  src/AutoComplete.cxx
  src/Catalogue.cxx
  src/PositionCache.cxx
  src/Decoration.cxx
  src/ViewStyle.cxx
  src/CaseFolder.cxx
  src/EditView.cxx
  src/UniConversion.cxx
  src/Style.cxx
  src/Selection.cxx
  src/CallTip.cxx
  src/RunStyles.cxx
  src/Document.cxx
  src/ContractionState.cxx
  src/PerLine.cxx
  src/LineMarker.cxx
  src/ScintillaBase.cxx
  src/XPM.cxx
  src/Indicator.cxx
  src/Editor.cxx
  src/RESearch.cxx
  src/ExternalLexer.cxx
  src/KeyMap.cxx
  src/EditModel.cxx
  src/CellBuffer.cxx
  )

file(GLOB lexer_SRC lexers/*.cxx)

add_library(scintilla STATIC ${scintilla_SRC} ${lexer_SRC})

target_link_libraries(scintilla
  ${GTK2_LIBRARIES}
  )
