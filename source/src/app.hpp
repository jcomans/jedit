#ifndef _APP_H_
#define _APP_H_

#include <iostream>

#include <gtk/gtk.h>

#include <Scintilla.h>
#include <ScintillaWidget.h>

#include "editor.hpp"
#include "buffer.hpp"

#include "script_engine.hpp"

using namespace std;

class App
{
public:
  App(int argc=0, char** argv=0):
    app_(nullptr),
    editor_widget_(nullptr),
    status_bar_widget_(nullptr),
    editor_(),
    buffers_(editor_),
    script_engine_()
  {
    gtk_init(&argc, &argv);

    createGUI();
    connectSignals();

    editor_.init(SCINTILLA(editor_widget_));
    buffers_.init();
    script_engine_.set_app(this);

    script_engine_.load("../data/init.py");
  }

  void run()
  {
    gtk_main();
  }

  static int handleExit(GtkWidget*w, GdkEventAny*e, gpointer p) 
  {
    gtk_main_quit();
    return 1;
  }

  static int handleKey(GtkWidget*w, GdkEvent* e, gpointer p)
  {
    GdkEventKey* keyevent = reinterpret_cast<GdkEventKey*>(e);
    
    cout << "Keypress: " << keyevent->keyval << "(" << keyevent->state << ")" 
         << (keyevent->is_modifier>0?"*":"") << endl;
  
    return gtk_widget_event(static_cast<GtkWidget*>(p), e);
  }

  SCEditor& editor() { return editor_; }

private:
  void createGUI()
  {
    app_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget* boxMain = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(app_), boxMain);

    editor_widget_ = scintilla_new();
    status_bar_widget_ = gtk_statusbar_new();

    gtk_box_pack_start(GTK_BOX(boxMain), editor_widget_, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(boxMain), status_bar_widget_, FALSE, FALSE, 0);

    gtk_widget_show_all(app_);
  }

  void connectSignals()
  {
    gtk_signal_connect(GTK_OBJECT(app_), "delete_event",
                       GTK_SIGNAL_FUNC(&App::handleExit), 0);

    gtk_signal_connect(GTK_OBJECT(app_), "key_press_event",
                       GTK_SIGNAL_FUNC(&App::handleKey), editor_widget_);
  }

private:
  GtkWidget* app_;

  GtkWidget* editor_widget_;
  GtkWidget* status_bar_widget_;

  SCEditor   editor_;
  BufferList buffers_;

  ScriptEngine script_engine_;
};

#endif /* _APP_H_ */
