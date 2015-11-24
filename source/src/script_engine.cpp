#include "script_engine.hpp"

#include "app.hpp"
#include "buffer.hpp"
#include "editor.hpp"
#include "key_handler.hpp"
#include "minibuffer.hpp"

#include <iostream>
#include <string>

using namespace std;
namespace py = boost::python;

namespace
{
  App* the_app = 0;

  //App& getApp() { return *the_app; }
  SCEditor& getEditor() { return the_app->editor(); }
  KeyHandler& getKeyHandler() { return the_app->key_handler(); }
  BufferList& getBufferList() { return the_app->buffer_list(); }
  MiniBuffer& getMiniBuffer() { return the_app->mini_buffer(); }

}

BOOST_PYTHON_MODULE(jedit)
{
  using namespace boost::python;

  def("editor", &getEditor, return_value_policy<reference_existing_object>());
  def("key_handler", &getKeyHandler, return_value_policy<reference_existing_object>());
  def("buffer_list", &getBufferList, return_value_policy<reference_existing_object>());
  def("mini_buffer", &getMiniBuffer, return_value_policy<reference_existing_object>());

  class_<SCEditor>("Editor" , no_init).
    def("set_font"          , &SCEditor::setFont       ).
    def("set_caret_style"   , &SCEditor::setCaretStyle ).
    def("add_text"          , &SCEditor::addText       ).
    def("insert_char"       , &SCEditor::insertChar    ).

    def("next_line"         , &SCEditor::nextLine      ).
    def("previous_line"     , &SCEditor::previousLine  ).

    def("line_start"        , &SCEditor::lineStart     ).
    def("line_end"          , &SCEditor::lineEnd       ).

    def("char_left"         , &SCEditor::charLeft      ).
    def("char_right"        , &SCEditor::charRight     ).
    def("new_line"          , &SCEditor::newLine       ).

    def("backspace"         , &SCEditor::backSpace     ).
    def("delete"            , &SCEditor::deleteChar    ).

    def("undo"              , &SCEditor::undo          );
  
  class_<KeyHandler>("KeyHandler" , no_init ).
    def("key_buffer" , &KeyHandler::keyBuffer );

  class_<BufferList>("BufferList" , no_init).
    def("find_file"     , &BufferList::findFile     ).
    def("save_file"     , &BufferList::saveFile     ).
    def("switch_buffer" , &BufferList::switchBuffer ).
    def("kill_buffer"   , &BufferList::killBuffer   );

  class_<MiniBuffer>("MiniBuffer" , no_init).
    def("is_active"     , &MiniBuffer::isActive     ).
    def("set_message"   , &MiniBuffer::setMessage   ).
    def("clear_message" , &MiniBuffer::clearMessage ).
    def("cancel"        , &MiniBuffer::cancel       ).
    def("get_dynamic"   , &MiniBuffer::getDynamic   ).
    def("set_dynamic"   , &MiniBuffer::setDynamic   ).
    def("backspace"     , &MiniBuffer::backSpace    ).
    def("insert_char"   , &MiniBuffer::insertChar   ).
    def("start_capture" , &MiniBuffer::startCapture );
}

ScriptEngine::ScriptEngine():
  py_context_()
{
  py_context_.addModule("jedit", PyInit_jedit);
  py_context_.init();
  main_module_ = py::import("__main__");
  main_namespace_ = main_module_.attr("__dict__");

  main_namespace_["jedit"] = py::import("jedit");
}

void ScriptEngine::set_app(App* app)
{
  the_app = app;
}

bool ScriptEngine::load(const char* file)
{
  try
  {
    py::exec_file(file, main_namespace_, main_namespace_);
  }
  catch(py::error_already_set)
  {
    PyErr_Print();
    return false;
  }
  return true;
}

bool ScriptEngine::handle(const char* cmd)
{
  try
  {
    auto handle_key = main_namespace_["handle_key"];
    auto res = handle_key(cmd);
    return py::extract<bool>(res);
  }
  catch(py::error_already_set)
  {
    PyErr_Print();
    return false;
  }
  return true;
}


