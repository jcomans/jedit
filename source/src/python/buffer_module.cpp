#include "python_modules.hpp"

#include <boost/python.hpp>

#include "../buffer.hpp"

void exportBuffer()
{
  using namespace boost::python;

  object buffer_module(handle<>(borrowed(PyImport_AddModule("jedit.mod_buffer"))));
  scope().attr("mod_buffer") = buffer_module;
  scope io_scope = buffer_module;

  class_<BufferList>("BufferList" , no_init).
    def("find_file"     , &BufferList::findFile     ).
    def("save_file"     , &BufferList::saveFile     ).
    def("switch_buffer" , &BufferList::switchBuffer ).
    def("kill_buffer"   , &BufferList::killBuffer   );
}
