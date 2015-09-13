#include <boost/python.hpp>

namespace jedit
{

  class PythonContext
  {
  public:
    PythonContext() {}
    template<class T>
    void addModule(const char* name, T init_func) { PyImport_AppendInittab(name, init_func); }
    void init()      { Py_Initialize(); }
    ~PythonContext() { Py_Finalize();   }
  };

  class ScriptEngine
  {
  public:
    ScriptEngine();

    ~ScriptEngine() {}

    bool load(const char* file);
    bool run(char key);
  private:
    PythonContext py_context_;

    boost::python::object main_module_;
    boost::python::object main_namespace_;
  };
}
