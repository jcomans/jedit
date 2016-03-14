#include "key_handler.hpp"

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <boost/lexical_cast.hpp>

#include "script_engine.hpp"

KeyHandler::KeyHandler(ScriptEngine& se):
  script_engine_(se),
  state_mask_(0)
{
  // The mapping of control characters to their string prefix
  state_map_[0]                = "";
  state_map_[GDK_SHIFT_MASK]   = "";
  state_map_[GDK_LOCK_MASK]    = "L-";
  state_map_[GDK_CONTROL_MASK] = "C-";
  state_map_[GDK_MOD1_MASK]    = "M-";

  state_map_[GDK_CONTROL_MASK|GDK_MOD1_MASK]  = "C-M-";
  state_map_[GDK_CONTROL_MASK|GDK_SHIFT_MASK] = "C-S-";

  // Create the state mask used to mask out any control keys not mapped
  for(auto keyval: state_map_)
    state_mask_ |= keyval.first;

  // Create the mapping of ordinary keys to their string representation
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
  key_map_[GDK_KEY_Tab]       = "TAB";

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

bool KeyHandler::handle(unsigned int keyval, unsigned int state, bool is_modifier)
{
  if(!is_modifier)
  {
    // First add the state prefix. We need to mask the state with the state mask to get rid
    // of unmapped control keys (NumLock for example)
    key_buffer_ += state_map_[state & state_mask_];
    // Convert the key to it's string representation. If we don't have a mapping, output the 
    // numerical value of the key
    key_buffer_ += key_map_.count(keyval) ? key_map_[keyval] : boost::lexical_cast<std::string>(keyval);
    // If the key was handled, we reset the buffer to read a new chord, otherwise the next
    // call will append
    if(script_engine_.handle(key_buffer_.c_str()))
    {
      key_buffer_ = "";
    }
    else
    {
      key_buffer_ += " ";
    }
  }

  return true;
}

const char* KeyHandler::keyBuffer() const 
{ 
  return key_buffer_.c_str(); 
}
