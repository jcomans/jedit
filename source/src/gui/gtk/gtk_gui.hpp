#ifndef _GTK_GUI_H_
#define _GTK_GUI_H_

#include <boost/asio.hpp>

#include "../gui.hpp"
#include "../../util.hpp"

#include <gtk/gtk.h>
#include <Scintilla.h>
#include <ScintillaWidget.h>

class GTKGui: public Gui
{
public:
  GTKGui(int argc, char** argv, boost::asio::io_service& io_service);
  ~GTKGui();

  void run();
  void stop();
  void exit();

  ScintillaSender scintillaSender();

  void setMinibufferMessage(const char* message);
  void clearMinibufferMessage();
  
  void setStatusBar(const char* text);

  bool registerKeyEventCallback(KeyEventCallback );
  bool registerSCNotificationCallback(SCNotificationCallback );

private:
  sptr_t sendMessage(unsigned int, uptr_t, sptr_t);

  static int handleExit( GtkWidget* w, GdkEventAny* e, gpointer p );
  static int handleKey( GtkWidget* w, GdkEvent* e, gpointer p );
  static int handleScintillaMessage( GtkWidget* w, gint, SCNotification* n, gpointer p );

  void postExit();
  void postKey(KeyEvent ke);
  void postScintillaMessage(SCNotification* n);

private:
  struct Pimpl;
  PimplHolder<Pimpl> pimpl_;
};

#endif /* _GTK_GUI_H_ */
