#include <chrono>
#include <iostream>
#include <functional>
#include <thread>

#include <gtk/gtk.h>

#include <boost/asio.hpp>
#include <boost/asio/basic_waitable_timer.hpp>

GtkWidget* label;

boost::asio::io_service*       the_io_service;
boost::asio::io_service::work* gtk_work;

typedef boost::asio::basic_waitable_timer<std::chrono::system_clock> chrono_timer;
chrono_timer* timer;

using Callback = std::function<void()>;

void start()
{
  gdk_threads_enter();
  gtk_main();
  gdk_threads_leave();
}

void quit()
{
  gdk_threads_enter();
  gtk_main_quit();
  gdk_threads_leave();

  delete gtk_work;
}

void timer_handler(const boost::system::error_code& error);

void hello()
{
  gdk_threads_enter();
  gtk_label_set_text(GTK_LABEL(label), "Hello, world!");
  gdk_threads_leave();

  timer->expires_from_now(std::chrono::seconds(2));
  timer->async_wait(timer_handler);
}

void clear()
{
  gdk_threads_enter();
  gtk_label_set_text(GTK_LABEL(label), "");
  gdk_threads_leave();
}

void timer_handler(const boost::system::error_code& error)
{
  if(!error) clear();
}

void button_clicked(GtkButton* b, gpointer p)
{
  Callback cb = *reinterpret_cast<Callback*>(p);
  the_io_service->post(cb);
}

void handle_exit(GtkWidget*w, GdkEventAny*e, gpointer p)
{
  Callback cb = *reinterpret_cast<Callback*>(p);
  the_io_service->post(cb);
}

int main(int argc, char** argv) 
{
  gdk_threads_init();
  gtk_init(&argc, &argv); 

  auto gtk_app = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  auto box_main = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(gtk_app), box_main);

  auto button = gtk_button_new_with_label("Hello");
  gtk_box_pack_start(GTK_BOX(box_main), button, TRUE, TRUE, 0);

  label = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(box_main), label, FALSE, FALSE, 0);

  gtk_widget_show_all(gtk_app);

  auto exit_callback  = Callback{&quit};
  auto click_callback = Callback{&hello};

  gtk_signal_connect(GTK_OBJECT(gtk_app), "delete_event",
                     GTK_SIGNAL_FUNC(&handle_exit), &exit_callback);

  gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(&button_clicked), &click_callback);

  
  the_io_service = new boost::asio::io_service();
  timer          = new chrono_timer(*the_io_service);
  gtk_work       = new boost::asio::io_service::work(*the_io_service);

  auto gtk_thread = std::thread(&start);

  the_io_service->run();
  
  gtk_thread.join();

  delete the_io_service;
}
