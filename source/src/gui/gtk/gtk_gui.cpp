#include "gtk_gui.hpp"

#include <memory>
#include <utility>

#include "../gui_factory.hpp"

#include <thread>
#include <iostream>
using namespace std;


struct GTKContext
{
  GTKContext(int argc, char** argv) 
  { 
    gdk_threads_init();
    gtk_init(&argc, &argv); 
  }
};

struct GDKThreadLocker
{
  GDKThreadLocker() { gdk_threads_enter(); }
  ~GDKThreadLocker(){ gdk_threads_leave(); }
};

struct GTKGui::Pimpl
{
  GTKContext context;

  boost::asio::io_service& io_service;
  std::unique_ptr<boost::asio::io_service::work> gui_work;

  GtkWidget* app_widget;
  GtkWidget* editor_widget;
  GtkWidget* status_bar_widget;
  GtkWidget* mini_buffer_widget;

  KeyEventCallback       key_event_callback;
  SCNotificationCallback scnotification_callback;


  Pimpl(int argc, char** argv, boost::asio::io_service& the_io_service,
        GtkWidget* app, GtkWidget* edit, GtkWidget* status, GtkWidget* mini):
    context(argc, argv), 
    io_service(the_io_service), gui_work(new boost::asio::io_service::work(io_service)),
    app_widget(app), editor_widget(edit), status_bar_widget(status), mini_buffer_widget(mini),
    key_event_callback(), scnotification_callback()
  {
  }
};

GTKGui::GTKGui(int argc, char** argv, boost::asio::io_service& io_service):
  pimpl_(new Pimpl(argc, argv, io_service, nullptr, nullptr, nullptr, nullptr))
                   
{
  pimpl_->app_widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  auto boxMain = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pimpl_->app_widget), boxMain);

  pimpl_->editor_widget     = scintilla_new();
  pimpl_->status_bar_widget  = gtk_label_new("");
  pimpl_->mini_buffer_widget = gtk_statusbar_new();

  gtk_box_pack_start(GTK_BOX(boxMain), pimpl_->editor_widget,     TRUE,  TRUE,  0);
  gtk_box_pack_start(GTK_BOX(boxMain), pimpl_->status_bar_widget,  FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(boxMain), pimpl_->mini_buffer_widget, FALSE, FALSE, 0);

  scintilla_set_id(reinterpret_cast<ScintillaObject*>(pimpl_->editor_widget), 0);

  gtk_widget_show_all(pimpl_->app_widget);

  gtk_signal_connect(GTK_OBJECT(pimpl_->app_widget), "delete_event",
                     GTK_SIGNAL_FUNC(&handleExit), this);

  gtk_signal_connect(GTK_OBJECT(pimpl_->app_widget), "key_press_event",
                     GTK_SIGNAL_FUNC(&handleKey), this);

  gtk_signal_connect(GTK_OBJECT(pimpl_->editor_widget), "sci-notify",
                     GTK_SIGNAL_FUNC(&handleScintillaMessage), this);
}

GTKGui::~GTKGui()
{
}

void GTKGui::run()
{
  {
    auto lock = GDKThreadLocker();
    gtk_main();  
  }
  pimpl_->gui_work.reset();
}

void GTKGui::exit()
{
  auto lock = GDKThreadLocker();
  gtk_main_quit();
}

Gui::ScintillaSender GTKGui::scintillaSender()
{
  return std::bind(&GTKGui::sendMessage, this,
                   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

}

sptr_t GTKGui::sendMessage(unsigned int msg, uptr_t arg1, sptr_t arg2)
{
  auto lock = GDKThreadLocker();
  return scintilla_send_message(reinterpret_cast<ScintillaObject*>(pimpl_->editor_widget), msg, arg1, arg2);
}

void GTKGui::setMinibufferMessage(const char* message)
{
  auto lock = GDKThreadLocker();
  gtk_statusbar_remove_all(reinterpret_cast<GtkStatusbar*>(pimpl_->mini_buffer_widget), 0);
  gtk_statusbar_push(reinterpret_cast<GtkStatusbar*>(pimpl_->mini_buffer_widget), 0, message);
}

void GTKGui::clearMinibufferMessage()
{
  auto lock = GDKThreadLocker();
  gtk_statusbar_remove_all(reinterpret_cast<GtkStatusbar*>(pimpl_->mini_buffer_widget), 0);
}  

void GTKGui::setStatusBar(const char* text)
{
  auto lock = GDKThreadLocker();
  gtk_label_set_text(reinterpret_cast<GtkLabel*>(pimpl_->status_bar_widget), text);
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

int GTKGui::handleExit(GtkWidget*w, GdkEventAny*e, gpointer p) 
{
  auto the_gui = reinterpret_cast<GTKGui*>(p);
  the_gui->postExit();
  return 1;
}

int GTKGui::handleKey(GtkWidget*w, GdkEvent* e, gpointer p)
{
  auto gtkkeyevent = reinterpret_cast<GdkEventKey*>(e);
  auto the_gui     = reinterpret_cast<GTKGui*>(p);

  the_gui->postKey(KeyEvent{gtkkeyevent->keyval, gtkkeyevent->state, (gtkkeyevent->is_modifier > 0)});

  return 1;
}

int GTKGui::handleScintillaMessage(GtkWidget *, gint, SCNotification *notification, gpointer p)
{
  auto the_gui = reinterpret_cast<GTKGui*>(p);

  the_gui->postScintillaMessage(notification);

  return 1;
}

void GTKGui::postExit()
{
  pimpl_->io_service.post(std::bind(&GTKGui::exit, this));
}

void GTKGui::postKey(KeyEvent ke)
{
  if(pimpl_->key_event_callback)
    pimpl_->io_service.post(std::bind(pimpl_->key_event_callback, ke));
}

void GTKGui::postScintillaMessage(SCNotification* n)
{

  if(pimpl_->scnotification_callback)
    pimpl_->io_service.post(std::bind(pimpl_->scnotification_callback, n));
}

namespace
{
  auto reg = RegisterGUI<GTKGui>{"gtk"};
}
