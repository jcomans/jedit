#ifndef _APP_H_
#define _APP_H_

#include "script_engine.hpp"

#include "editor.hpp"
#include "buffer.hpp"
#include "minibuffer.hpp"

#include "key_handler.hpp"

#include "gui/gui.hpp"

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

  GuiPtr gui_;

  ScriptEngine script_engine_;

  SCEditor   editor_;
  MiniBuffer mini_buffer_;

  KeyHandler key_handler_;

  BufferList buffers_;
  
};

#endif /* _APP_H_ */
