#include "app.hpp"
#include "gui/gui_factory.hpp"


App::App(int argc, char** argv):

  gui_(GUIFactory::Create(argc, argv)),

  script_engine_(),

  editor_(gui_),
  mini_buffer_(gui_),

  key_handler_(script_engine_),

  buffers_(editor_)
{
  gui_->registerKeyEventCallback( [this](KeyEvent evt){ return this->key_handler_.handle(evt.val, evt.state, evt.is_mod); } );

  script_engine_.set_app(this);
  script_engine_.load("../data/init.py");
}

void App::run()
{
  gui_->run();
}

void App::exit()
{
  gui_->exit();
}

SCEditor& App::editor() 
{
  return editor_; 
}

KeyHandler& App::key_handler() 
{
  return key_handler_; 
}

BufferList& App::buffer_list() 
{
  return buffers_; 
}

MiniBuffer& App::mini_buffer() 
{
  return mini_buffer_; 
}
