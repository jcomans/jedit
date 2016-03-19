#include "python_modules.hpp"

#include <boost/python.hpp>

#include "../minibuffer.hpp"

void exportMiniBuffer()
{
  using namespace boost::python;

  object mini_buffer_module(handle<>(borrowed(PyImport_AddModule("jedit.mod_mini_buffer"))));
  scope().attr("mod_mini_buffer") = mini_buffer_module;
  scope io_scope = mini_buffer_module;

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
