#ifndef _MINIBUFFER_H_
#define _MINIBUFFER_H_

#include <gtk/gtk.h>

#include <functional>
#include <string>

#include "script_engine.hpp"

#include <iostream>
using namespace std;


class MiniBuffer
{
public:
  MiniBuffer(ScriptEngine& se): script_engine_(se), status_bar_widget_(nullptr), is_active_(false) {};

  void init(GtkWidget* status_bar_widget) { status_bar_widget_ = status_bar_widget; }

  bool isActive() const { return is_active_; };

  void setMessage(const char* message)
  {
    clearMessage();
    gtk_statusbar_push((GtkStatusbar*)status_bar_widget_, 0, message);
  }

  void clearMessage()
  {
    gtk_statusbar_remove_all((GtkStatusbar*)status_bar_widget_, 0);
  }

  void cancel()
  {
    read_only_ = "";
    dynamic_   = "";
    clearMessage();
    is_active_ = false;
  }

  void startCapture(const char* read_only, const char* callback)
  {
    is_active_ = true;
    read_only_ = read_only;
    callback_  = callback;
    setMessage((read_only_ + dynamic_).c_str());
  }

  int handle(unsigned int keyval, unsigned int state, bool is_modifier)
  {
    if(!is_modifier)
    {
      if(state == GDK_CONTROL_MASK && keyval == 103)
      {
        cancel();
      }
      else if(keyval == GDK_KEY_Return)
      {
        script_engine_.call(callback_.c_str(), dynamic_.c_str());
        cancel();
      }
      else if(state == 0 && keyval == GDK_KEY_BackSpace)
      {
        dynamic_.pop_back();
        setMessage((read_only_ + dynamic_).c_str());
      }
      else if((state == 0 || state == GDK_SHIFT_MASK) && keyval)
      {
        dynamic_ += (char)keyval;
        setMessage((read_only_ + dynamic_).c_str());
      }
    }

    return true;
  }

private:
  ScriptEngine& script_engine_;
  GtkWidget* status_bar_widget_;
  bool is_active_;

  std::string read_only_;
  std::string dynamic_;

  std::string callback_;
};

#endif /* _MINIBUFFER_H_ */
