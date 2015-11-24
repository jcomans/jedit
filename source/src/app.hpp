#ifndef _APP_H_
#define _APP_H_

#include <iostream>

struct _GtkWidget;
struct _GdkEventAny;
union _GdkEvent;

typedef _GtkWidget GtkWidget;
typedef _GdkEventAny GdkEventAny;
typedef _GdkEvent GdkEvent;

typedef void* gpointer;
typedef int   gint;

struct SCNotification;

#include "script_engine.hpp"

#include "editor.hpp"
#include "buffer.hpp"
#include "minibuffer.hpp"

#include "key_handler.hpp"


using namespace std;

class App
{
public:
  App(int argc=0, char** argv=0);

  void run();

  static int handleExit(GtkWidget*w, GdkEventAny*e, gpointer p);

  static int handleKey(GtkWidget*w, GdkEvent* e, gpointer p);

  static int handleScintillaMessage(GtkWidget *, gint, SCNotification *notification, gpointer userData);

  SCEditor& editor();
  KeyHandler& key_handler();
  BufferList& buffer_list();
  MiniBuffer& mini_buffer();

private:
  void createGUI();

  void connectSignals();

private:
  GtkWidget* app_;

  GtkWidget* editor_widget_;
  GtkWidget* status_bar_widget_;

  ScriptEngine script_engine_;

  SCEditor   editor_;
  BufferList buffers_;
  MiniBuffer mini_buffer_;

  KeyHandler key_handler_;
  
};

#endif /* _APP_H_ */
