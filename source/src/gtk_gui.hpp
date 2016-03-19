#ifndef _GTK_GUI_H_
#define _GTK_GUI_H_

#include "gui.hpp"
#include "util.hpp"

class GTKGui: public Gui
{
public:
  GTKGui(int argc, char** argv);
  ~GTKGui();

  void run();
  void exit();

  sptr_t sendEditor(unsigned int message, uptr_t wParam=0, sptr_t lParam=0);

  void setMinibufferMessage(const char* message);
  void clearMinibufferMessage();
  

  bool registerKeyEventCallback(KeyEventCallback );
  bool registerSCNotificationCallback(SCNotificationCallback );

private:
  struct Pimpl;
  PimplHolder<Pimpl> pimpl_;
};

#endif /* _GTK_GUI_H_ */
