#include "python_modules.hpp"

#include <boost/python.hpp>

#include "../editor.hpp"

void exportEditor()
{
  using namespace boost::python;

  object editor_module(handle<>(borrowed(PyImport_AddModule("jedit.mod_editor"))));
  scope().attr("mod_editor") = editor_module;
  scope io_scope = editor_module;

  class_<SCEditor>("Editor" , no_init).
    def("set_font"        , &SCEditor::setFont       ).
    def("set_caret_style" , &SCEditor::setCaretStyle ).
    def("add_text"        , &SCEditor::addText       ).
    def("insert_char"     , &SCEditor::insertChar    ).

    def("next_line"       , &SCEditor::nextLine      ).
    def("previous_line"   , &SCEditor::previousLine  ).

    def("line_start"      , &SCEditor::lineStart     ).
    def("line_end"        , &SCEditor::lineEnd       ).

    def("char_left"       , &SCEditor::charLeft      ).
    def("char_right"      , &SCEditor::charRight     ).
    def("new_line"        , &SCEditor::newLine       ).

    def("backspace"       , &SCEditor::backSpace     ).
    def("delete"          , &SCEditor::deleteChar    ).

    def("get_text"        , &SCEditor::getText       ).
    def("insert_text"     , &SCEditor::insertText    ).
    def("delete_range"    , &SCEditor::deleteRange   ).
    def("current_pos"     , &SCEditor::currentPos    ).

    def("undo"            , &SCEditor::undo          );
}
