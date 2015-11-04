#ifndef _SCINTILLACORE_H_
#define _SCINTILLACORE_H_

#include <gtk/gtk.h>

#include <Scintilla.h>
#include <ScintillaWidget.h>

class ScintillaCore
{
public:
  ScintillaCore();

  sptr_t sendMessage(unsigned int message, uptr_t wParam=0, sptr_t lParam=0);

  GtkWidget* widget() const;

private:
  GtkWidget*       gtk_widget_;
  ScintillaObject* scintilla_;
};

#endif /* _SCINTILLACORE_H_ */
