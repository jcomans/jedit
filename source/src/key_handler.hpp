#ifndef _KEY_HANDLER_H_
#define _KEY_HANDLER_H_

#include <map>
#include <string>

#include "script_engine.hpp"

class KeyHandler
{
public:
  KeyHandler(ScriptEngine& se):script_engine_(se) 
  {
    state_map_[GDK_SHIFT_MASK]   = "S-";
    state_map_[GDK_LOCK_MASK]    = "L-";
    state_map_[GDK_CONTROL_MASK] = "C-";
    state_map_[GDK_MOD1_MASK]    = "M-";

    for(size_t i=65; i<=90; ++i)
      key_map_[i] = 'A' + (i-65);

    for(size_t i=97; i<=122; ++i)
      key_map_[i] = 'a' + (i-97);

    for(size_t i=48; i<=57; ++i)
      key_map_[i] = '0' + (i-48);

  }

  bool handle(unsigned int keyval, unsigned int state, bool is_modifier)
  {
    if(!is_modifier)
    {
      if(!state || state==GDK_SHIFT_MASK)
      {
        key_buffer_ = key_map_[keyval];
        return script_engine_.handle(key_map_[keyval].c_str());
      }
      else
      {
        auto cmd = state_map_[state] + key_map_[keyval];
        key_buffer_ = cmd;
        return script_engine_.handle(cmd.c_str());
      }
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
