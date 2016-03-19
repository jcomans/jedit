#ifndef _MINIBUFFER_H_
#define _MINIBUFFER_H_

#include <string>

#include "gui/gui.hpp"

class MiniBuffer
{
public:
  MiniBuffer(GuiPtr gui);

  bool isActive() const;

  void setMessage(const char* message);

  void clearMessage();

  void cancel();

  const char* getDynamic() const;

  void setDynamic(const char* dyn);

  void backSpace();

  void insertChar(char character);

  void startCapture(const char* read_only, const char* callback);

private:
  GuiPtr gui_;
  bool is_active_;

  std::string read_only_;
  std::string dynamic_;

  std::string callback_;
};

#endif /* _MINIBUFFER_H_ */
