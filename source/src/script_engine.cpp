#include "script_engine.hpp"

#include "app.hpp"

#include "python/python_modules.hpp"

namespace py = boost::python;

namespace
{
  App* the_app = 0;

  void do_exit() { the_app->exit(); }

  SCEditor&   getEditor()     { return the_app->editor(); }
  KeyHandler& getKeyHandler() { return the_app->key_handler(); }
  BufferList& getBufferList() { return the_app->buffer_list(); }
  MiniBuffer& getMiniBuffer() { return the_app->mini_buffer(); }

}


BOOST_PYTHON_MODULE(jedit)
{
  using namespace boost::python;

  scope().attr("__path__") = "jedit";

  def("exit", &do_exit);

  def("editor",      &getEditor,     return_value_policy<reference_existing_object>());
  def("key_handler", &getKeyHandler, return_value_policy<reference_existing_object>());
  def("buffer_list", &getBufferList, return_value_policy<reference_existing_object>());
  def("mini_buffer", &getMiniBuffer, return_value_policy<reference_existing_object>());

  exportEditor();
  exportKeyHandler();
  exportBuffer();
  exportMiniBuffer();
}

ScriptEngine::ScriptEngine():
  py_context_()
{
  py_context_.addModule("jedit", PyInit_jedit);
  py_context_.init();

  main_module_    = py::import("__main__");
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


