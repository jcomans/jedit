#include "minibuffer.hpp"

MiniBuffer::MiniBuffer(GuiPtr gui): 
  gui_(gui),
  is_active_(false) 
{
}

bool MiniBuffer::isActive() const 
{ 
  return is_active_; 
}

void MiniBuffer::setMessage(const char* message)
{
  gui_->setMinibufferMessage(message);
}

void MiniBuffer::clearMessage()
{
  gui_->clearMinibufferMessage();
}

void MiniBuffer::cancel()
{
  read_only_ = "";
  dynamic_   = "";
  clearMessage();
  is_active_ = false;
}

const char* MiniBuffer::getDynamic() const
{
  return dynamic_.c_str();
}

void MiniBuffer::setDynamic(const char* dyn)
{
  dynamic_ = dyn;
  setMessage((read_only_ + dynamic_).c_str());
}

void MiniBuffer::backSpace()
{
  dynamic_.pop_back();
  setMessage((read_only_ + dynamic_).c_str());
}

void MiniBuffer::insertChar(char character)
{
  dynamic_ += character;
  setMessage((read_only_ + dynamic_).c_str());
}

void MiniBuffer::startCapture(const char* read_only)
{
  is_active_ = true;
  read_only_ = read_only;
  setMessage((read_only_ + dynamic_).c_str());
}
