#include "app.hpp"

#include <thread>

#include <boost/log/trivial.hpp>

#include "gui/gui_factory.hpp"

Core::Core(GuiPtr gui):
  script_engine_(),

  editor_(gui->scintillaSender()),
  mini_buffer_(gui),

  key_handler_(script_engine_),

  buffers_(editor_)
{
}

App::App(int argc, char** argv):

  io_service_(),

  gui_(GUIFactory::Create(argc, argv, io_service_)),
  core_(new Core(gui_))
  
{
  gui_->registerKeyEventCallback( 
    [this](KeyEvent evt){ return this->core_->key_handler_.handle(evt.val, evt.state, evt.is_mod); } );

  core_->script_engine_.set_app(this);
  core_->script_engine_.load("../data/init.py");
}

void App::run()
{
  // Start the gui thread
  auto gui_thread = std::thread(std::bind(&Gui::run, gui_));
  BOOST_LOG_TRIVIAL(debug) << "Started GUI thread";
  // Start processing work
  io_service_.run();
  // After all work is done (on exit) we delete the core before stopping the 
  // gui thread. Cleanup will still call the gui, so this needs to happen before
  // stopping the gui thread
  core_.reset();
  // Request gui shutdown
  gui_->exit();
  // Wait for completion
  gui_thread.join();
}

void App::exit()
{
  gui_->stop();
}

SCEditor& App::editor() 
{
  return core_->editor_; 
}

KeyHandler& App::key_handler() 
{
  return core_->key_handler_; 
}

BufferList& App::buffer_list() 
{
  return core_->buffers_; 
}

MiniBuffer& App::mini_buffer() 
{
  return core_->mini_buffer_; 
}
