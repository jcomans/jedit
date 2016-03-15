#include "app.hpp"

#include <gtk/gtk.h>

#include <ScintillaWidget.h>

namespace
{
int handleExit( GtkWidget* w, GdkEventAny* e, gpointer p );
int handleKey( GtkWidget* w, GdkEvent* e, gpointer p );
int handleScintillaMessage( GtkWidget*, gint, SCNotification* notification,
                            gpointer userData );
}

App::App(int argc, char** argv):
  app_(nullptr),

  editor_widget_(nullptr),
  status_bar_widget_(nullptr),

  script_engine_(),

  editor_(),
  buffers_(editor_),
  mini_buffer_(),

  key_handler_(script_engine_)
{
  gtk_init(&argc, &argv);

  createGUI();
  connectSignals();

  editor_.init(SCINTILLA(editor_widget_));
  buffers_.init();
  script_engine_.set_app(this);

  mini_buffer_.init(status_bar_widget_);

  script_engine_.load("../data/init.py");
}

void App::run()
{
  gtk_main();
}

void App::exit()
{
  gtk_main_quit();
}

SCEditor& App::editor() 
{
  return editor_; 
}

KeyHandler& App::key_handler() 
{
  return key_handler_; 
}

BufferList& App::buffer_list() 
{
  return buffers_; 
}

MiniBuffer& App::mini_buffer() 
{
  return mini_buffer_; 
}

void App::createGUI()
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

void App::connectSignals()
{
  gtk_signal_connect(GTK_OBJECT(app_), "delete_event",
                     GTK_SIGNAL_FUNC(&handleExit), this);

  gtk_signal_connect(GTK_OBJECT(app_), "key_press_event",
                     GTK_SIGNAL_FUNC(&handleKey), this);

  gtk_signal_connect(GTK_OBJECT(editor_widget_), "sci-notify",
                     GTK_SIGNAL_FUNC(&handleScintillaMessage), this);
}

namespace
{
  int handleExit(GtkWidget*w, GdkEventAny*e, gpointer p) 
  {
    App* the_app = reinterpret_cast<App*>(p);
    the_app->exit();
    return 1;
  }

  int handleKey(GtkWidget*w, GdkEvent* e, gpointer p)
  {
    GdkEventKey* keyevent = reinterpret_cast<GdkEventKey*>(e);
    
    App* the_app = reinterpret_cast<App*>(p);
    return the_app->key_handler().handle(keyevent->keyval, keyevent->state, keyevent->is_modifier);
  }

  int handleScintillaMessage(GtkWidget *, gint, SCNotification *notification, gpointer userData)
  {
    switch(notification->nmhdr.code)
    {
    case(SCN_SAVEPOINTLEFT):
      return 1;            
    case(SCN_SAVEPOINTREACHED):
      return 1;
    }

    return 0;
  }
}
