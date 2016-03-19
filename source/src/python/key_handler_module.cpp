#include "python_modules.hpp"

#include <boost/python.hpp>

#include "../key_handler.hpp"

void exportKeyHandler()
{
  using namespace boost::python;

  object key_handler_module(handle<>(borrowed(PyImport_AddModule("jedit.mod_key_handler"))));
  scope().attr("mod_key_handler") = key_handler_module;
  scope io_scope = key_handler_module;

  class_<KeyHandler>("KeyHandler" , no_init ).
    def("key_buffer" , &KeyHandler::keyBuffer );
}
