#include "script_engine.hpp"
#include "backend/backend.hpp"

#include <iostream>
#include <string>

#include <ncurses.h>

using namespace std;
namespace py = boost::python;

using ScriptEngine = jedit::ScriptEngine;




BOOST_PYTHON_MODULE(buffer)
{
  using namespace boost::python;

  def<void(std::string)>("write", &write);
  def("say_hello", &say_hello);
  
}

ScriptEngine::ScriptEngine():
  py_context_()
{
  py_context_.addModule("hello", PyInit_hello);
  py_context_.init();
  main_module_ = py::import("__main__");
  main_namespace_ = main_module_.attr("__dict__");

  main_namespace_["hello"] = py::import("hello");
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

bool ScriptEngine::run(char key)
{
  try
  {
    auto handle_key = main_namespace_["handle_key"];
    handle_key(key);
  }
  catch(py::error_already_set)
  {
    PyErr_Print();
    return false;
  }
  return true;
}

