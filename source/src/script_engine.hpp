#ifndef _SCRIPT_ENGINE_H_
#define _SCRIPT_ENGINE_H_

#include <string>

#include <boost/python.hpp>

class App;

class PythonContext
{
public:
  PythonContext() {}
  template<class T>
  void addModule(const char* name, T init_func) { PyImport_AppendInittab(name, init_func); }
  void init()      
  { 
    Py_Initialize();
    std::wstring path(Py_GetPath());
    path += L":../data";
    PySys_SetPath(path.c_str());
  }
  ~PythonContext() { Py_Finalize();   }
};

class ScriptEngine
{
public:
  ScriptEngine();

  ~ScriptEngine() {}

  void set_app(App* app);
  bool load(const char* file);
  bool handle(const char* cmd);

private:
  PythonContext py_context_;

  boost::python::object main_module_;
  boost::python::object main_namespace_;

};

#endif /* _SCRIPT_ENGINE_H_ */
