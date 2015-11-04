#include <gtk/gtk.h>

#include <Scintilla.h>
#include <ScintillaWidget.h>

#include "editor.hpp"

class App
{
public:
  App(int argc, char** argv):
    app_(nullptr),
    editor_widget_(nullptr),
    status_bar_widget_(nullptr)
  {
    gtk_init(&argc, &argv);

    createGUI();
    connectSignals();

    editor_.init(SCINTILLA(editor_widget_));
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
  }

private:
  GtkWidget* app_;

  GtkWidget* editor_widget_;
  GtkWidget* status_bar_widget_;

  SCEditor editor_;  
};

int main(int argc, char** argv)
{  
  App the_app(argc, argv);
  the_app.run();
}
