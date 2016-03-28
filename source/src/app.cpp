#include "app.hpp"

#include <thread>

#include "gui/gui_factory.hpp"


App::App(int argc, char** argv):

  io_service_(),

  gui_(GUIFactory::Create(argc, argv, io_service_)),

  script_engine_(),

  editor_(gui_->scintillaSender()),
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
  auto gui_thread = std::thread(std::bind(&Gui::run, gui_));
  io_service_.run();
  gui_thread.join();
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
