#include "minibuffer.hpp"

#include <gtk/gtk.h>

MiniBuffer::MiniBuffer(): 
  status_bar_widget_(nullptr), 
  is_active_(false) 
{
}

void MiniBuffer::init(GtkWidget* status_bar_widget) 
{ 
  status_bar_widget_ = status_bar_widget; 
}

bool MiniBuffer::isActive() const 
{ 
  return is_active_; 
}

void MiniBuffer::setMessage(const char* message)
{
  clearMessage();
  gtk_statusbar_push((GtkStatusbar*)status_bar_widget_, 0, message);
}

void MiniBuffer::clearMessage()
{
  gtk_statusbar_remove_all((GtkStatusbar*)status_bar_widget_, 0);
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

void MiniBuffer::startCapture(const char* read_only, const char* callback)
{
  is_active_ = true;
  read_only_ = read_only;
  callback_  = callback;
  setMessage((read_only_ + dynamic_).c_str());
}

// int MiniBuffer::handle(unsigned int keyval, unsigned int state, bool is_modifier)
// {
//   if(!is_modifier)
//   {
//     if(state == GDK_CONTROL_MASK && keyval == 103)
//     {
//       cancel();
//     }
//     else if(keyval == GDK_KEY_Return)
//     {
//       script_engine_.call(callback_.c_str(), dynamic_.c_str());
//       cancel();
//     }
//     else if(state == 0 && keyval == GDK_KEY_BackSpace)
//     {
//       dynamic_.pop_back();
//       setMessage((read_only_ + dynamic_).c_str());
//     }
//     else if((state == 0 || state == GDK_SHIFT_MASK) && keyval)
//     {
//       dynamic_ += (char)keyval;
//       setMessage((read_only_ + dynamic_).c_str());
//     }
//   }

//   return true;
// }
