#include <iostream>
#include <sstream>

#include <gtk/gtk.h>

#include <Scintilla.h>
#include <ScintillaWidget.h>
#include <SciLexer.h>

#include "ScintillaCore.hpp"

using namespace std;

GtkWidget* foo = 0;

int exit_app(GtkWidget*w, GdkEventAny*e, gpointer p) {
   gtk_main_quit();
   return w||e||p||1;	// Avoid warnings
}

int keypress(GtkWidget*w, GdkEvent* e, gpointer p) {
  cout << "Keypress" << endl;
  
  return gtk_widget_event(foo, e);
}

class GTKWindow
{
public:
  GTKWindow(int argc, char** argv): app_(nullptr)
  {
    gtk_init(&argc, &argv);
    app_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_signal_connect(GTK_OBJECT(app_), "delete_event",
                       GTK_SIGNAL_FUNC(exit_app), 0);

    gtk_signal_connect(GTK_OBJECT(app_), "key_press_event",
                       GTK_SIGNAL_FUNC(keypress), 0);

  }

  void add(GtkWidget* widget)
  {
    gtk_container_add(GTK_CONTAINER(app_), widget);
  }

  void main()
  {
    gtk_widget_show_all(app_);
    gtk_main();
  }

private:
  GtkWidget* app_;
};

class ScintillaEditor
{
public:
  ScintillaEditor(): core_()
  {
  }


  void insertText(int pos, const char* text)
  {
    core_.sendMessage(SCI_INSERTTEXT, pos, (sptr_t)text);
  }

  GtkWidget* widget() const { return core_.widget(); }

private:
  ScintillaCore core_;
};


int main(int argc, char** argv)
{
  GTKWindow gtk_window(argc, argv);

  ScintillaEditor editor;
  
  gtk_window.add(editor.widget());

  foo = editor.widget();

  const char* text = 
    "int main(int argc, char **argv) {\n"
    "    // Start up the gnome\n"
    "    gnome_init(\"stest\", \"1.0\", argc, argv);\n}";
  
  editor.insertText(0, text);

  gtk_window.main();
}

















