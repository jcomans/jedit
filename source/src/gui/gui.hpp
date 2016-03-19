#ifndef _GUI_H_
#define _GUI_H_

#include <functional>
#include <memory>

#include <Scintilla.h>

struct KeyEvent
{
  size_t val;
  size_t state;
  bool   is_mod;
};


class Gui
{
public:
  virtual ~Gui() {};

  virtual void run()  =0;
  virtual void exit() =0;

  // Editor communication
  virtual sptr_t sendEditor(unsigned int message, uptr_t wParam=0, sptr_t lParam=0) =0;

  template <typename T>
  sptr_t sendEditor(unsigned int message, uptr_t wParam=0, T* lParam=0);

  virtual void setMinibufferMessage(const char* message) =0;
  virtual void clearMinibufferMessage() =0;

  // Callback system
  using NoArgCallback          = std::function<int()>;
  using KeyEventCallback       = std::function<int(KeyEvent)>;
  using SCNotificationCallback = std::function<int(SCNotification*)>;

  virtual bool registerKeyEventCallback(KeyEventCallback )             = 0;
  virtual bool registerSCNotificationCallback(SCNotificationCallback ) = 0;
  
};

template <typename T>
sptr_t Gui::sendEditor(unsigned int message, uptr_t wParam, T* lParam)
{
  return sendEditor(message, wParam, reinterpret_cast<sptr_t>(lParam));
}

using GuiPtr = std::shared_ptr<Gui>;

#endif /* _GUI_H_ */
