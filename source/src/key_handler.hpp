#ifndef _KEY_HANDLER_H_
#define _KEY_HANDLER_H_

#include <map>
#include <string>

#include "gui/gui.hpp"

class ScriptEngine;

class KeyHandler
{
  
public:
  KeyHandler(ScriptEngine& se);
  
  bool handle(unsigned int keyval, unsigned int state, bool is_modifier);

  const char* keyBuffer() const;

private:
  typedef std::map<unsigned int, std::string> Mapping;

  ScriptEngine& script_engine_;

  unsigned int state_mask_;

  Mapping state_map_;
  Mapping key_map_;

  std::string key_buffer_;
};

#endif /* _KEY_HANDLER_H_ */
