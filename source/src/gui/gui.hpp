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

  KeyEvent(size_t v, size_t s, bool m): val(v), state(s), is_mod(m) {}
};


class Gui
{
public:
  virtual ~Gui() {};

  virtual void run()  =0;
  virtual void stop() =0;
  virtual void exit() =0;

  // Editor communication
  using ScintillaSender = std::function<sptr_t(unsigned int, uptr_t, sptr_t)>;
  virtual ScintillaSender scintillaSender() =0;


  // Mini-buffer management
  virtual void setMinibufferMessage(const char* message) =0;
  virtual void clearMinibufferMessage() =0;

  // Status bar
  virtual void setStatusBar(const char* text) =0;

  // Callback system
  using NoArgCallback          = std::function<int()>;
  using KeyEventCallback       = std::function<int(KeyEvent)>;
  using SCNotificationCallback = std::function<int(SCNotification*)>;

  virtual bool registerKeyEventCallback(KeyEventCallback )             = 0;
  virtual bool registerSCNotificationCallback(SCNotificationCallback ) = 0;
  
};

using GuiPtr = std::shared_ptr<Gui>;

#endif /* _GUI_H_ */
