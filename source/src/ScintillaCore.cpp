#include "ScintillaCore.hpp"

#include <gtk/gtk.h>

#include <Scintilla.h>
#include <ScintillaWidget.h>

ScintillaCore::ScintillaCore():
  gtk_widget_(scintilla_new()), 
  scintilla_(SCINTILLA(gtk_widget_))
{
  scintilla_set_id(scintilla_, 0);
}

sptr_t ScintillaCore::sendMessage(unsigned int message, uptr_t wParam, sptr_t lParam)
{
  return scintilla_send_message(scintilla_, message, wParam, lParam);
}

GtkWidget* ScintillaCore::widget() const
{
  return gtk_widget_;
}
