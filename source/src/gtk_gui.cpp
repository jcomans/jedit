#include "gtk_gui.hpp"

#include "gui_factory.hpp"

#include <gtk/gtk.h>
#include <Scintilla.h>
#include <ScintillaWidget.h>

namespace
{
int handleExit( GtkWidget* w, GdkEventAny* e, gpointer p );
int handleKey( GtkWidget* w, GdkEvent* e, gpointer p );
int handleScintillaMessage( GtkWidget*, gint, SCNotification* notification,
                            gpointer userData );
}

struct GTKContext
{
  GTKContext(int argc, char** argv) { gtk_init(&argc, &argv); }
};

struct GTKGui::Pimpl
{
  GTKContext context;
  GtkWidget* app_widget;
  GtkWidget* editor_widget;
  GtkWidget* status_bar_widget;
  KeyEventCallback       key_event_callback;
  SCNotificationCallback scnotification_callback;

  Pimpl(int argc, char** argv, GtkWidget* app, GtkWidget* edit, GtkWidget* status):
    context(argc, argv), 
    app_widget(app), editor_widget(edit), status_bar_widget(status),
    key_event_callback(), scnotification_callback()
  {
  }
};

GTKGui::GTKGui(int argc, char** argv):
  pimpl_(new Pimpl(argc, argv, nullptr, nullptr, nullptr))
                   
{
  pimpl_->app_widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  auto boxMain = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pimpl_->app_widget), boxMain);

  pimpl_->editor_widget     = scintilla_new();
  pimpl_->status_bar_widget = gtk_statusbar_new();

  gtk_box_pack_start(GTK_BOX(boxMain), pimpl_->editor_widget,     TRUE,  TRUE,  0);
  gtk_box_pack_start(GTK_BOX(boxMain), pimpl_->status_bar_widget, FALSE, FALSE, 0);

  scintilla_set_id(reinterpret_cast<ScintillaObject*>(pimpl_->editor_widget), 0);

  gtk_widget_show_all(pimpl_->app_widget);

  gtk_signal_connect(GTK_OBJECT(pimpl_->app_widget), "delete_event",
                     GTK_SIGNAL_FUNC(&handleExit), this);

  gtk_signal_connect(GTK_OBJECT(pimpl_->app_widget), "key_press_event",
                     GTK_SIGNAL_FUNC(&handleKey), &pimpl_->key_event_callback);

  gtk_signal_connect(GTK_OBJECT(pimpl_->editor_widget), "sci-notify",
                     GTK_SIGNAL_FUNC(&handleScintillaMessage), &pimpl_->scnotification_callback);
}

GTKGui::~GTKGui()
{
}

void GTKGui::run()
{
  gtk_main();
}

void GTKGui::exit()
{
  gtk_main_quit();
}

sptr_t GTKGui::sendEditor(unsigned int message, uptr_t wParam, sptr_t lParam)
{
  return scintilla_send_message(reinterpret_cast<ScintillaObject*>(pimpl_->editor_widget), message, wParam, lParam);
}

void GTKGui::setMinibufferMessage(const char* message)
{
  clearMinibufferMessage();
  gtk_statusbar_push(reinterpret_cast<GtkStatusbar*>(pimpl_->status_bar_widget), 0, message);
}

void GTKGui::clearMinibufferMessage()
{
  gtk_statusbar_remove_all(reinterpret_cast<GtkStatusbar*>(pimpl_->status_bar_widget), 0);
}  

bool GTKGui::registerKeyEventCallback(KeyEventCallback kecb)
{
  if(!pimpl_->key_event_callback)
  {
    pimpl_->key_event_callback = kecb;
    return true;
  }

  return false;
}

bool GTKGui::registerSCNotificationCallback(SCNotificationCallback scncb)
{
  if(!pimpl_->scnotification_callback)
  {
    pimpl_->scnotification_callback = scncb;
  }

  return false;
}

namespace
{
  int handleExit(GtkWidget*w, GdkEventAny*e, gpointer p) 
  {
    auto the_gui = reinterpret_cast<GTKGui*>(p);
    the_gui->exit();
    return 1;
  }

  int handleKey(GtkWidget*w, GdkEvent* e, gpointer p)
  {
    auto gtkkeyevent = reinterpret_cast<GdkEventKey*>(e);
    
    auto kecb = *(reinterpret_cast<Gui::KeyEventCallback*>(p));

    KeyEvent key_event;
    key_event.val    = gtkkeyevent->keyval;
    key_event.state  = gtkkeyevent->state;
    key_event.is_mod = gtkkeyevent->is_modifier;

    return kecb(key_event);
  }

  int handleScintillaMessage(GtkWidget *, gint, SCNotification *notification, gpointer p)
  {
    auto scncb = *(reinterpret_cast<Gui::SCNotificationCallback*>(p));

    if(scncb)
      return scncb(notification);
    else
      return 0;
  }
}

namespace
{
  auto reg = RegisterGUI<GTKGui>{"gtk"};
}
