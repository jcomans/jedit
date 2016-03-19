#ifndef _GTK_GUI_H_
#define _GTK_GUI_H_

#include "../gui.hpp"
#include "../../util.hpp"

class GTKGui: public Gui
{
public:
  GTKGui(int argc, char** argv);
  ~GTKGui();

  void run();
  void exit();

  ScintillaSender scintillaSender();

  void setMinibufferMessage(const char* message);
  void clearMinibufferMessage();
  
  void setStatusBar(const char* text);

  bool registerKeyEventCallback(KeyEventCallback );
  bool registerSCNotificationCallback(SCNotificationCallback );

private:
  struct Pimpl;
  PimplHolder<Pimpl> pimpl_;
};

#endif /* _GTK_GUI_H_ */
