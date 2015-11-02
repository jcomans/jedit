#include <iostream>
#include <sstream>

#include <gtk/gtk.h>

#include <Scintilla.h>
#include <ScintillaWidget.h>
#include <SciLexer.h>

static int exit_app(GtkWidget*w, GdkEventAny*e, gpointer p) {
   gtk_main_quit();
   return w||e||p||1;	// Avoid warnings
}

static int scintilla_callback(GtkWidget *, gint, SCNotification *notification, gpointer userData)
{
  if(notification->nmhdr.code == SCN_STYLENEEDED)
  {
    std::cout << "Style needed (" << notification->position << ")" << std::endl;
  }
  return 0;
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

  }

  void add(GtkWidget* widget)
  {
    gtk_container_add(GTK_CONTAINER(app_), widget);
    
    // Only for scintilla :)
    // gtk_signal_connect(GTK_OBJECT(widget), "sci-notify",
    //                    GTK_SIGNAL_FUNC(scintilla_callback), 0);
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
  ScintillaEditor(): gtk_widget_(scintilla_new()), scintilla_(SCINTILLA(gtk_widget_))
  {
    scintilla_set_id(scintilla_, 0);

    gtk_signal_connect(GTK_OBJECT(gtk_widget_), "sci-notify",
                       GTK_SIGNAL_FUNC(&ScintillaEditor::scintilla_callback), this);
  }

  sptr_t sendMessage(unsigned int message, uptr_t wParam=0, sptr_t lParam=0)
  {
    return scintilla_send_message(scintilla_, message, wParam, lParam);
  }

  void insertText(int pos, const char* text)
  {
    sendMessage(SCI_INSERTTEXT, pos, (sptr_t)text);
  }

  void styleRegion(SCNotification *notification)
  {
    const int line_number = sendMessage(SCI_LINEFROMPOSITION, sendMessage(SCI_GETENDSTYLED));
    const int start_pos = sendMessage(SCI_POSITIONFROMLINE, line_number);
    const int end_pos = notification->position;
    std::cout << "Style needed (" << start_pos << "," << end_pos << ")" << std::endl;
    const int line_length = sendMessage(SCI_LINELENGTH, line_number);

    sendMessage(SCI_SETSTYLING, line_length, 13);
  }

  static int scintilla_callback(GtkWidget *, gint, SCNotification *notification, gpointer userData)
  {
    if(notification->nmhdr.code == SCN_STYLENEEDED)
    {
      ScintillaEditor* foo = reinterpret_cast<ScintillaEditor*>(userData);
      foo->styleRegion(notification);        
    }
    return 0;
  }

  GtkWidget* widget() const { return gtk_widget_; }

private:
  GtkWidget*       gtk_widget_;
  ScintillaObject* scintilla_;
};


int main(int argc, char** argv)
{
  GTKWindow gtk_window(argc, argv);

  ScintillaEditor editor;
  
  gtk_window.add(editor.widget());

  editor.sendMessage(SCI_SETLEXER, SCLEX_CONTAINER);

  const int SCE_STYLE_BLACK  = 10;
  const int SCE_STYLE_PURPLE = 12;
  const int SCE_STYLE_BLUE   = 13;

  const int black   = 0x000000;
  const int blue    = 0x0000ff;
  const int purple  = 0xff00ff;

  editor.sendMessage(SCI_STYLESETFORE, SCE_STYLE_BLACK,  black);
  editor.sendMessage(SCI_STYLESETFORE, SCE_STYLE_PURPLE, purple);
  editor.sendMessage(SCI_STYLESETFORE, SCE_STYLE_BLUE,   blue);
  

  const char* text = 
    "int main(int argc, char **argv) {\n"
    "    // Start up the gnome\n"
    "    gnome_init(\"stest\", \"1.0\", argc, argv);\n}";
  
  editor.insertText(0, text);

  gtk_window.main();
}

















