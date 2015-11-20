#ifndef _KEY_HANDLER_H_
#define _KEY_HANDLER_H_

#include <map>
#include <string>

#include <gdk/gdkkeysyms.h>

#include <boost/lexical_cast.hpp>

#include "script_engine.hpp"

class KeyHandler
{
  
public:
  KeyHandler(ScriptEngine& se):script_engine_(se) 
  {
    state_map_[0]                = "";
    state_map_[GDK_SHIFT_MASK]   = "";
    state_map_[GDK_LOCK_MASK]    = "L-";
    state_map_[GDK_CONTROL_MASK] = "C-";
    state_map_[GDK_MOD1_MASK]    = "M-";

    state_map_[GDK_CONTROL_MASK|GDK_MOD1_MASK] = "C-M-";


    // Printable characters
    for(size_t i=32; i<=127; ++i)
      key_map_[i] = (char)i;

    key_map_[GDK_KEY_Return]    = "RET";
    key_map_[GDK_KEY_Escape]    = "ESC";
    key_map_[GDK_KEY_Insert]    = "INS";
    key_map_[GDK_KEY_Delete]    = "DEL";
    key_map_[GDK_KEY_BackSpace] = "BS";
    key_map_[GDK_KEY_Home]      = "HOME";
    key_map_[GDK_KEY_End]       = "END";
    key_map_[GDK_KEY_Page_Up]   = "PGUP";
    key_map_[GDK_KEY_Page_Down] = "PGDN";

    key_map_[GDK_KEY_Up]    = "UP";
    key_map_[GDK_KEY_Down]  = "DOWN";
    key_map_[GDK_KEY_Right] = "RIGHT";
    key_map_[GDK_KEY_Left]  = "LEFT";

    // Function keys
    key_map_[GDK_KEY_F1]  = "F1";
    key_map_[GDK_KEY_F2]  = "F2";
    key_map_[GDK_KEY_F3]  = "F3";
    key_map_[GDK_KEY_F4]  = "F4";
    key_map_[GDK_KEY_F5]  = "F5";
    key_map_[GDK_KEY_F6]  = "F6";
    key_map_[GDK_KEY_F7]  = "F7";
    key_map_[GDK_KEY_F8]  = "F8";
    key_map_[GDK_KEY_F9]  = "F9";
    key_map_[GDK_KEY_F10] = "F10";
    key_map_[GDK_KEY_F11] = "F11";
    key_map_[GDK_KEY_F12] = "F12";

  }

  bool handle(unsigned int keyval, unsigned int state, bool is_modifier)
  {
    if(!is_modifier)
    {

      key_buffer_ += state_map_[state];
      key_buffer_ += key_map_.count(keyval) ? key_map_[keyval] : boost::lexical_cast<std::string>(keyval);

      // If the key was handled, we reset the buffer to read a new chord, otherwise the next
      // call will append
      if(script_engine_.handle(key_buffer_.c_str()))
         key_buffer_ = "";
      else
        key_buffer_ += " ";
    }
      
      
    return true;
  }

  std::string keyBuffer() const { return key_buffer_; }

private:
  typedef std::map<unsigned int, std::string> Mapping;

  ScriptEngine& script_engine_;

  Mapping state_map_;
  Mapping key_map_;

  std::string key_buffer_;
};

#endif /* _KEY_HANDLER_H_ */
