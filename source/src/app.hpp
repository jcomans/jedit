#ifndef _APP_H_
#define _APP_H_

#include <boost/asio.hpp>

#include "script_engine.hpp"

#include "editor.hpp"
#include "buffer.hpp"
#include "minibuffer.hpp"

#include "key_handler.hpp"

#include "gui/gui.hpp"

class Core
{
public:
  Core(GuiPtr gui);

  ScriptEngine script_engine_;

  SCEditor   editor_;
  MiniBuffer mini_buffer_;

  KeyHandler key_handler_;

  BufferList buffers_;
};

using CorePtr = std::unique_ptr<Core>;

class App
{
public:
  App(int argc=0, char** argv=0);

  void run();

  void exit();

  SCEditor&   editor();
  KeyHandler& key_handler();
  BufferList& buffer_list();
  MiniBuffer& mini_buffer();
private:

  boost::asio::io_service io_service_;

  GuiPtr gui_;
  CorePtr core_;

  
};

#endif /* _APP_H_ */
